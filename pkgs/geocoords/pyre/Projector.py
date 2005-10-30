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

## @file geocoords/pyre/Projector.py
## @brief Python manager for projector.

from pyre.components.Component import Component

# Projector class
class Projector(Component):
  """Python manager for projector."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Projector facilities and properties."""

    ## @class Inventory
    ## Python object for managing Projector facilities and properties.
    ##
    ## \b Properties
    ## @li \b projection Name of projection
    ## @li \b units Name of units
    ## @li \b proj-options Additional proj options
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    projection = pyre.inventory.str("projection", default="aea")
    projection.meta['tip'] = "Name of projection."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    projOptions = pyre.inventory.str("proj-options", default="m")
    projOptions.meta['tip'] = "Additional proj options."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def handle(self):
    """Get handle to C++ Projector."""
    return self._cppProjector


  def initialize(self, coordSys):
    """Initialize projector."""
    
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppProjector_projection(self._cppProjector, self.projection)
    bindings.CppProjector_units(self._cppProjector, self.units)
    bindings.CppProjector_projOptions(self._cppProjector, self.projOptions)
    bindings.CppProjector_initialize(self._cppProjector, coordSys.handle())
    return


  def project(self, lonlat):
    """Project geographic coordinates."""

    import spatialdata.geocoords.geocoords as bindings
    xy = bindings.CppProjector_project(self._cppProjector, lonlat)
    return xy
  

  def invproject(self, xy):
    """Project geographic coordinates."""

    import spatialdata.geocoords.geocoords as bindings
    lonlat = bindings.CppProjector_invproject(self._cppProjector, xy)
    return lonlat
  

  def __init__(self, name="projector"):
    """Constructor."""
    Component.__init__(self, name, facility="projector")

    import spatialdata.geocoords.geocoords as bindings
    self._cppProjector = bindings.CppProjector()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.projection = self.inventory.projection
    self.units = self.inventory.units
    self.projOptions = self.inventory.projOptions
    return


# version
__id__ = "$Id$"

# End of file 
