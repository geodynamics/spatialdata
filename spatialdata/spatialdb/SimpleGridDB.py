# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import pathlib

from .SpatialDBObj import SpatialDBObj
from .spatialdb import SimpleGridDB as ModuleSimpleGridDB


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Name of SimpleGridDB file must be specified.")
    if not pathlib.Path(value).is_file():
        raise IOError(f"Spatial database file '{value}' not found.")
    return value


class SimpleGridDB(SpatialDBObj, ModuleSimpleGridDB):
    """
    Simple spatial database on a logically rectangular grid aligned with the coordinate axes.
    Points along the coordinate axes do not have to be uniformly spaced.

    Implements `SpatialDB`.
    """
    DOC_CONFIG = {
        "cfg": """
            [db]
            description = Material properties
            filename = mat_elastic.spatialdb
            query_type = linear
            """,
    }

    import pythia.pyre.inventory

    filename = pythia.pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Name for data file."

    queryType = pythia.pyre.inventory.str("query_type", default="nearest")
    queryType.validator = pythia.pyre.inventory.choice(["nearest", "linear"])
    queryType.meta['tip'] = "Type of query to perform."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="simplegriddb"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        ModuleSimpleGridDB.setFilename(self, self.filename)
        ModuleSimpleGridDB.setQueryType(self, self._parseQueryString(self.queryType))

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleSimpleGridDB.__init__(self)

    def _parseQueryString(self, label):
        if label.lower() == "nearest":
            value = ModuleSimpleGridDB.NEAREST
        elif label.lower() == "linear":
            value = ModuleSimpleGridDB.LINEAR
        else:
            raise ValueError("Unknown value for query type '%s' in spatial database %s." % (label, self.description))
        return value


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with SimpleGridDB.
    """
    return SimpleGridDB()


# End of file
