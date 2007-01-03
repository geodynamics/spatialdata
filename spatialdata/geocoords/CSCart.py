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

## @file spatialdata/geocoords/CSCart.py
## @brief Python manager for Cartesian coordinate systems.

from CoordSys import CoordSys

# CSCart class
class CSCart(CoordSys):
  """Python manager for Cartesian coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CoordSys.Inventory):
    """Python object for managing CSCart facilities and properties."""

    ## @class Inventory
    ## Python object for managing CSCart facilities and properties.
    ##
    ## \b Properties
    ## @li \b units Name of units
    ## @li \b space_dim Number of dimensions for coordinate system
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    spaceDim = pyre.inventory.int("space_dim", default=3)
    spaceDim.meta['tip'] = "Number of dimensions for coordinate system."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize coordinate system."""

    import pyre.units
    uparser = pyre.units.parser()
    coordUnits = uparser.parse(self.units)
    self.cppHandle.toMeters = coordUnits.value

    self.cppHandle.spaceDim = self.spaceDim

    CoordSys.initialize(self)
    return


  def __init__(self, name="cscart"):
    """Constructor."""
    CoordSys.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self.cppHandle = bindings.CSCart()
    self.units = "m"
    self.spaceDim = 3
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.units = self.inventory.units
    self.spaceDim = self.inventory.spaceDim
    return


# End of file 
