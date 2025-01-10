# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .SpatialDBObj import SpatialDBObj
from .spatialdb import SimpleDB as ModuleSimpleDB


class SimpleDB(SpatialDBObj, ModuleSimpleDB):
    """
    Simple spatial database for points with arbitrary layout.
    Use SimpleGridDB for points on a logically rectangular grid aligned with the coordinate axes.

    Implements `SpatialDB`.
    """
    DOC_CONFIG = {
        "cfg": """
            [db]
            description = Material properties
            query_type = linear
            iohandler.filename = mat_elastic.spatialdb
            """,
    }

    import pythia.pyre.inventory

    queryType = pythia.pyre.inventory.str("query_type", default="nearest")
    queryType.validator = pythia.pyre.inventory.choice(["nearest", "linear"])
    queryType.meta['tip'] = "Type of query to perform."

    from .SimpleIOAscii import SimpleIOAscii
    iohandler = pythia.pyre.inventory.facility("iohandler", family="simpledb_io", factory=SimpleIOAscii)
    iohandler.meta['tip'] = "I/O handler for database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="simpledb"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        ModuleSimpleDB.setIOHandler(self, self.iohandler)
        ModuleSimpleDB.setQueryType(self, self._parseQueryString(self.queryType))

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleSimpleDB.__init__(self)

    def _parseQueryString(self, label):
        if label.lower() == "nearest":
            value = ModuleSimpleDB.NEAREST
        elif label.lower() == "linear":
            value = ModuleSimpleDB.LINEAR
        else:
            raise ValueError("Unknown value for query type '%s'." % label)
        return value


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with SimpleDB.
    """
    return SimpleDB()


# End of file
