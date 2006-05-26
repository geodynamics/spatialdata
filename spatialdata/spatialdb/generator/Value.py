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

## @file spatialdata/spatialdb/generator/Value.py
## @brief Python manager for generating value in database.

from pyre.components.Component import Component

# Value class
class Value(Component):
  """Python manager for generating value in database."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Value facilities and properties."""

    ## @class Inventory
    ## Python object for managing Value facilities and properties.
    ##
    ## \b Properties
    ## @li \b name Name of value
    ## @li \b units Units for value
    ##
    ## \b Facilities
    ## @li \b filters Filters used to construct spatial distribution

    import pyre.inventory

    name = pyre.inventory.str("name", default="")
    name.meta['tip'] = "Name of value."

    units = pyre.inventory.str("units", default="none")
    units.meta['tip'] = "Units associated with value."

    from Filters import Filters
    filters = pyre.inventory.facility("filters", factory=Filters)
    filters.meta['tip'] = "Filter used to construct spatial distribution"
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def handle(self):
    return self._cppVal

  def applyFilters(self, locs, locCount, locDim, cs):
    self.locCount = locCount
    self.locDim = locDim
    import spatialdata.spatialdb.generator.generator as bindings
    self._cppVal = bindings.createValue(locCount)    
    for filter in self.filters.filters:
      filter.initialize()
      filter.apply(self._cppVal, locCount, locs, locCount, cs)
      filter.cleanup()
    return


  def setDB(self, cppDB, index):
    import spatialdata.spatialdb.generator.generator as bindings
    bindings.setValue(cppDB, index,
                                  self._cppVal, self.locCount,
                                  self.name, self.units)
    return

  
  def __init__(self, name="value"):
    """Constructor."""
    Component.__init__(self, name, facility="value")
    self._cppVal = None
    return


  def _configure(self):
    Component._configure(self)
    self.name = self.inventory.name
    self.units = self.inventory.units
    self.filters = self.inventory.filters
    return


# version
__id__ = "$Id$"

# End of file 
