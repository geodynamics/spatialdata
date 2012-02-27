#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/SimpleDB.py
##
## @brief Python manager for simple spatial database.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import SimpleDB as ModuleSimpleDB

# SimpleDB class
class SimpleDB(SpatialDBObj, ModuleSimpleDB):
  """
  Python manager for simple spatial database.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing SimpleDB facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SimpleDB facilities and properties.
    ##
    ## \b Properties
    ## @li query-type Type of query to perform
    ##
    ## \b Facilities
    ## @li \b iohandler I/O handler for database

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
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDBObj._configure(self)
    self.ioHandler(self.inventory.iohandler)
    self.queryType(self._parseQueryString(self.inventory.queryType))
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleSimpleDB.__init__(self)
    return


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
