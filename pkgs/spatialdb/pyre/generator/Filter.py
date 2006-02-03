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

## @file pyre/Filter.py
## @brief Python manager for shaping spatial distribution of data
##   while generating database.

from pyre.components.Component import Component

# Filter class
class Filter(Component):
  """Python manager for shaping spatial distribution of data while
  generating database."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Filter facilities and properties."""

    ## @class Inventory
    ## Python object for managing Filter facilities and properties.
    ##
    ## \b Properties
    ## @li \b name Name of value in supplied in filter spatial database
    ## @li \b operand Operand to use in applying filter
    ##
    ## \b Facilities
    ## @li \b db Database containing value defining filter

    import pyre.inventory

    name = pyre.inventory.str("name", default="")
    name.meta['tip'] = "Name of value supplied in filter spatial database."
    
    operand = pyre.inventory.str("operand", default="multiply")
    operand.validator = pyre.inventory.choice(["add", "subtract", 
                                               "multiply", "divide"])
    operand.meta['tip'] = "Operand to use in applying filter."

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = pyre.inventory.facility("db", factory=SimpleDB)
    db.meta['tip'] = "Database containing value defining filter."
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize filter."""
    self.db.initialize()
    self.db.open()
    return


  def cleanup(self):
    """Cleanup."""
    self.db.close()
    return


  def apply(self, cppVals, valueCount, locs, locCount, cs):
    """Apply filter to data."""
    import spatialdata.spatialdb.spatialdb as bindings
    self.db.queryVals([self.name])
    bindings.CppGenSimpleDB_applyFilter(cppVals, valueCount, locs, locCount,
                                        cs.handle(), self.db.handle(),
                                        self.operand)
    return

  def __init__(self, name="filter"):
    """Constructor."""
    Component.__init__(self, name, facility="filter")
    return


  def _configure(self):
    Component._configure(self)
    self.name = self.inventory.name
    self.operand = self.inventory.operand
    self.db = self.inventory.db
    return


# version
__id__ = "$Id$"

# End of file 
