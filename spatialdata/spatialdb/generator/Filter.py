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

## @file spatialdata/spatialdb/generator/Filter.py
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
    ## @li \b db_value Name of value in supplied in filter spatial database
    ## @li \b operand Operand to use in applying filter
    ##
    ## \b Facilities
    ## @li \b db Database containing value defining filter

    import pyre.inventory

    default = pyre.inventory.float("default", default=0.0)
    default.meta['tip'] = "Default value for filter."

    dbValue = pyre.inventory.str("db_value", default="")
    dbValue.meta['tip'] = "Name of value supplied in filter spatial database."
    
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
    import spatialdata.spatialdb.generator.generator as bindings
    self.db.queryVals([self.dbValue])
    bindings.applyFilter(cppVals, valueCount, locs, locCount,
                         cs.cppHandle, self.db.cppHandle,
                         self.operand, self.defaultValue)
    return

  def __init__(self, name="filter"):
    """Constructor."""
    Component.__init__(self, name, facility="filter")
    return


  def _configure(self):
    Component._configure(self)
    if self.inventory.dbValue == "":
      raise ValueError, \
            "Name of value in spatial database must be set for Filter '%s'." %\
            self.name
    self.dbValue = self.inventory.dbValue
    self.operand = self.inventory.operand
    self.db = self.inventory.db
    self.defaultValue = self.inventory.default
    return


# End of file 
