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

import spatialdata as bindings

# SimpleDB class
class SimpleDB(SpatialDB):
  """Python manager for simple spatial database."""

  def initialize(self):
    """Initialize database."""
    SpatialDB.initialize(self)
    bindings.CppSimpleDB_IOHandler(self._cppSpatialDB,
                                   self.inventory.iohandler.handle())
    return
  
  def open(self):
    """Open database and prepare for querying."""
    SpatialDB.open(self)
    bindings.CppSimpleDB_QueryType(self._cppSpatialDB,
                                   self.inventory.queryType)
    return

  def __init__(self, name="simpledb"):
    """Constructor."""
    SpatialDB.__init__(self, name)
    self._cppSpatialDB = bindings.CppSimpleDB()
    return

  class Inventory(SpatialDB.Inventory):
    """Python object for managing SimpleDB facilities and properties."""

    ## @class Inventory
    ## Python object for managing SimpleDB facilities and properties.
    ##
    ## \b Properties
    ## @li queryType Type of query to perform
    ##
    ## \b Facilities
    ## @li \b iohandler I/O handler for database

    import pyre.inventory

    queryType = pyre.inventory.str("query_type", default="Nearest")
    queryType.validator = pyre.inventory.choice(["Nearest", "Linear"])

    from SimpleIOAscii import SimpleIOAscii
    iohandler = pyre.inventory.facility("iohandler", factory=SimpleIOAscii)

# version
__id__ = "$Id: SimpleDB.py,v 1.2 2005/03/20 19:42:22 baagaard Exp $"

# End of file 
