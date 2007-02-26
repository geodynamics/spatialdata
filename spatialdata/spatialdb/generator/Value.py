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

import numpy

# Value class
class Value(Component):
  """
  Python manager for generating value in database.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing Value facilities and properties.
    """

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

  def __init__(self, name="value"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="value")
    return


  def calculate(self, locs, cs):
    """
    Calculate spatial distribution for value using filters.
    """
    (numLocs, spaceDim) = locs.shape
    value = numpy.zeros( (numLocs,), dtype=numpy.float64)
    for filter in self.filters.filters:
      filter.initialize()
      filter.apply(value, locs, cs)
      filter.finalize()
    return value


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    self.name = self.inventory.name
    self.units = self.inventory.units
    self.filters = self.inventory.filters
    return


# End of file 
