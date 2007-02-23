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
## @brief Python manager for simple spatial database.

from SpatialDB import SpatialDB

# SimpleDB class
class SimpleDB(SpatialDB):
  """Python manager for simple spatial database."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """Python object for managing SimpleDB facilities and properties."""

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
    iohandler = pyre.inventory.facility("iohandler", factory=SimpleIOAscii)
    iohandler.meta['tip'] = "I/O handler for database."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize database."""
    self.iohandler.initialize()
    SpatialDB.initialize(self)
    self.cppHandle.ioHandler(self.iohandler.cppHandle)
    return
  

  def open(self):
    """Open database and prepare for querying."""
    SpatialDB.open(self)
    self.cppHandle.queryType(self.queryType)
    return


  def __init__(self, name="simpledb"):
    """Constructor."""
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.SimpleDB()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    SpatialDB._configure(self)
    self.iohandler = self.inventory.iohandler
    self.queryType = self.inventory.queryType
    return


# End of file 
