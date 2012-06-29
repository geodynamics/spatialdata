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

## @file spatialdata/spatialdb/SimpleGridDB.py
##
## @brief Python manager for simple spatial database.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import SimpleGridDB as ModuleSimpleGridDB

# Validator for filename
def validateFilename(value):
  """
  Validate filename.
  """
  if 0 == len(value):
    raise ValueError("Name of SimpleGridDB file must be specified.")
  return value


# SimpleGridDB class
class SimpleGridDB(SpatialDBObj, ModuleSimpleGridDB):
  """
  Python manager for simple spatial database.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing SimpleGridDB facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SimpleGridDB facilities and properties.
    ##
    ## \b Properties
    ## @li \b filename Name for data file.
    ## @li \b query_type Type of query to perform
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Name for data file."

    queryType = pyre.inventory.str("query_type", default="nearest")
    queryType.validator = pyre.inventory.choice(["nearest", "linear"])
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
    ModuleSimpleGridDB.filename(self, self.inventory.filename)
    ModuleSimpleGridDB.queryType(self, self._parseQueryString(self.inventory.queryType))
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleSimpleGridDB.__init__(self)
    return


  def _parseQueryString(self, label):
    if label.lower() == "nearest":
      value = ModuleSimpleGridDB.NEAREST
    elif label.lower() == "linear":
      value = ModuleSimpleGridDB.LINEAR
    else:
      raise ValueError("Unknown value for query type '%s'." % label)
    return value


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with SimpleGridDB.
  """
  return SimpleGridDB()


# End of file 
