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

# @file spatialdata/spatialdb/SimpleDB.py
#
# @brief Python manager for simple spatial database.
#
# Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import SimpleDB as ModuleSimpleDB


class SimpleDB(SpatialDBObj, ModuleSimpleDB):
    """
    Python manager for simple spatial database.

    Factory: spatial_database

    INVENTORY

    Properties
      - *query_type* Type of query to perform [nearest, linear].

    Facilities
      - *iohandler* I/O handler for database.
    """

    import pyre.inventory

    queryType = pyre.inventory.str("query_type", default="nearest")
    queryType.validator = pyre.inventory.choice(["nearest", "linear"])
    queryType.meta['tip'] = "Type of query to perform."

    from SimpleIOAscii import SimpleIOAscii
    iohandler = pyre.inventory.facility("iohandler", family="simpledb_io",
                                        factory=SimpleIOAscii)
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
