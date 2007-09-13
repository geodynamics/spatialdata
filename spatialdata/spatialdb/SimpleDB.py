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

## @file spatialdata/spatialdb/SimpleDB.py
##
## @brief Python manager for simple spatial database.
##
## Factory: spatial_database

from SpatialDB import SpatialDB

# SimpleDB class
class SimpleDB(SpatialDB):
  """
  Python manager for simple spatial database.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
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
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.SimpleDB()
    return


  def initialize(self):
    """
    Initialize database.
    """
    self.iohandler.initialize()
    SpatialDB.initialize(self)
    self.cppHandle.ioHandler(self.iohandler.cppHandle)
    self.cppHandle.queryType(self.queryType)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self.iohandler = self.inventory.iohandler
    self.queryType = self.inventory.queryType
    return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with SimpleDB.
  """
  return SimpleDB()


# End of file 
