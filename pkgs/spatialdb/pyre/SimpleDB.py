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

## @file pyre/SimpleDB.py
## @brief Python manager for simple spatial database.

from SpatialDB import SpatialDB

import spatialdb as bindings

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

    queryType = pyre.inventory.str("query-type", default="nearest")
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
    bindings.CppSimpleDB_ioHandler(self._cppSpatialDB,
                                   self.iohandler.handle())
    return
  

  def open(self):
    """Open database and prepare for querying."""
    SpatialDB.open(self)
    bindings.CppSimpleDB_queryType(self._cppSpatialDB,
                                   self.inventory.queryType)
    return


  def __init__(self, name="simpledb"):
    """Constructor."""
    SpatialDB.__init__(self, name)
    self._cppSpatialDB = bindings.CppSimpleDB()
    return


  def _configure(self):
    self.iohandler = self.inventory.iohandler
    return

# version
__id__ = "$Id: SimpleDB.py,v 1.1 2005/05/25 18:43:00 baagaard Exp $"

# End of file 
