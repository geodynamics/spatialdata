#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2016 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/generator/Value.py
##
## @brief Python manager for generating value in database.
##
## Factory: database_value

from pyre.components.Component import Component

import numpy

# Value class
class Value(Component):
  """
  Python manager for generating value in database.

  Factory: database_value
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
    ## @li \b shapers Shapers used to construct spatial distribution

    import pyre.inventory

    name = pyre.inventory.str("name", default="")
    name.meta['tip'] = "Name of value."

    units = pyre.inventory.str("units", default="none")
    units.meta['tip'] = "Units associated with value."

    from Shapers import Shapers
    shapers = pyre.inventory.facility("shapers", family="shapers",
                                      factory=Shapers)
    shapers.meta['tip'] = "Filter used to construct spatial distribution"
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="value"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="database_value")
    return


  def calculate(self, locs, cs):
    """
    Calculate spatial distribution for value using shapers.
    """
    (numLocs, spaceDim) = locs.shape
    value = numpy.zeros( (numLocs,), dtype=numpy.float64)
    for filter in self.shapers.shapers:
      filter.initialize(locs, cs)
      filter.apply(value)
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
    self.shapers = self.inventory.shapers
    return


# FACTORIES ////////////////////////////////////////////////////////////

def database_value():
  """
  Factory associated with Value.
  """
  return Value()


# End of file 
