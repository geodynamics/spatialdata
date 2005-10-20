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

## @file geocoords/pyre/CoordSys.py
## @brief Python manager for coordinate systems.

from pyre.components.Component import Component

# CoordSys class
class CoordSys(Component):
  """Python manager for coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing CoordSys facilities and properties."""

    ## @class Inventory
    ## Python object for managing CoordSys facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li None

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def handle(self):
    """Get handle to C++ coordinate system."""
    return self._cppCoordSys


  def initialize(self):
    """Initialize coordinate system."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppCoordSys_initialize(self._cppCoordSys)
    return


  def __init__(self, name="coordsys"):
    """Constructor."""
    Component.__init__(self, name, facility="coordsys")

    self._cppCoordSys = None
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""
    return


# version
__id__ = "$Id$"

# End of file 
