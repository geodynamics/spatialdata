#!/usr/bin/env python
#
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

## @file spatialdata/spatialdb/CompositeDB.py
##
## @brief Python manager for spatial database with uniform values.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import CompositeDB as ModuleCompositeDB

# CompositeDB class
class CompositeDB(SpatialDBObj, ModuleCompositeDB):
  """
  Python manager for spatial database with uniform values.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing CompositeDB facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CompositeDB facilities and properties.
    ##
    ## \b Properties
    ## @li \b values_A Names of values to query with database A
    ## @li \b values_B Names of values to query with database B
    ##
    ## \b Facilities
    ## @li \b db_A Spatial database A
    ## @li \b db_B Spatial database B

    import pyre.inventory

    namesA = pyre.inventory.list("values_A", default=[])
    namesA.meta['tip'] = "Names of values to query with database A."

    namesB = pyre.inventory.list("values_B", default=[])
    namesB.meta['tip'] = "Names of values to query with database B."

    from UniformDB import UniformDB
    dbA = pyre.inventory.facility("db_A", factory=UniformDB,
                                  family="spatial_database")
    dbA.meta['tip'] = "Spatial database A."

    dbB = pyre.inventory.facility("db_B", factory=UniformDB,
                                  family="spatial_database")
    dbB.meta['tip'] = "Spatial database B."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="compositedb"):
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
    self._validateParameters(self.inventory)
    self.dbA(self.inventory.dbA, self.inventory.namesA)
    self.dbB(self.inventory.dbB, self.inventory.namesB)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCompositeDB.__init__(self)
    return


  def _validateParameters(self, data):
    """
    Validate parameters.
    """
    if (0 == len(data.namesA)):
      raise ValueError, \
            "Error in spatial database '%s'\n" \
            "Names of values to query in database A not set." \
            % self.label
    if (0 == len(data.namesB)):
      raise ValueError, \
            "Error in spatial database '%s'\n" \
            "Names of values to query in database B not set." \
            % self.label
    return
  

# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with CompositeDB.
  """
  return CompositeDB()


# End of file 
