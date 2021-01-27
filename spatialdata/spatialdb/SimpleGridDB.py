# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

# @file spatialdata/spatialdb/SimpleGridDB.py
#
# @brief Python manager for simple spatial database.
#
# Factory: spatial_database

from .SpatialDBObj import SpatialDBObj
from .spatialdb import SimpleGridDB as ModuleSimpleGridDB


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Name of SimpleGridDB file must be specified.")
    try:
        fin = open(value, "r")
    except IOError:
        raise IOError("Spatial database file '{}' not found.".format(value))
    return value


class SimpleGridDB(SpatialDBObj, ModuleSimpleGridDB):
    """
    Python manager for simple spatial database.

    Factory: spatial_database

    INVENTORY

    Properties
      - *filename* Name of spatial database file.
      - *query_type* Type of query to perform.

    Facilities
      - None
    """

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
            raise ValueError("Unknown value for query type '%s' in spatial database %s." % (label, self.label))
        return value


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with SimpleGridDB.
    """
    return SimpleGridDB()


# End of file
