#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/CompositeDB.py
##
## @brief Python manager for spatial database with uniform values.
##
## Factory: spatial_database

from SpatialDB import SpatialDB

# CompositeDB class
class CompositeDB(SpatialDB):
  """
  Python manager for spatial database with uniform values.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
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

    from SimpleDB import SimpleDB
    dbA = pyre.inventory.facility("db_A", factory=SimpleDB,
                                  family="spatial_database")
    dbA.meta['tip'] = "Spatial database A."

    dbB = pyre.inventory.facility("db_B", factory=SimpleDB,
                                  family="spatial_database")
    dbB.meta['tip'] = "Spatial database B."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="compositedb"):
    """
    Constructor.
    """
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.CompositeDB()
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self)
    self.dbA.initialize()
    self.dbB.initialize()
    self.cppHandle.dbA(self.dbA.cppHandle, self.namesA)
    self.cppHandle.dbB(self.dbB.cppHandle, self.namesB)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self._validateParameters(self.inventory)
    self.namesA = self.inventory.namesA
    self.dbA = self.inventory.dbA
    self.namesB = self.inventory.namesB
    self.dbB = self.inventory.dbB
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
