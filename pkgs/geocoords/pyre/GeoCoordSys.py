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

## @file geocoords/pyre/GeoCoordSys.py
## @brief Python manager for geographic coordinate systems.

from pyre.components.Component import Component

# GeoCoordSys class
class GeoCoordSys(Component):
  """Python manager for geographic coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing GeoCoordSys facilities and properties."""

    ## @class Inventory
    ## Python object for managing GeoCoordSys facilities and properties.
    ##
    ## \b Properties
    ## @li \b projection Name of projection
    ## @li \b ellipsoid Name of ellipsoid
    ## @li \b datum Name of datum
    ## @li \b units Name of units
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    projection = pyre.inventory.str("projection", default="aea")
    projection.meta['tip'] = "Name of projection."
    
    ellipsoid = pyre.inventory.str("ellipsoid", default="WGS84")
    ellipsoid.meta['tip'] = "Name of ellipsoid."

    datum = pyre.inventory.str("datum", default="WGS84")
    datum.meta['tip'] = "Name of datum."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of projected coordinates."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def handle(self):
    """Get handle to C++ geographic coordinate system."""
    return self._cppCoordSys


  def initialize(self):
    """Initialize geographic coordinate system."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppGeoCoordSys_projection(self._cppCoordSys, self.projection)
    bindings.CppGeoCoordSys_ellipsoid(self._cppCoordSys, self.ellipsoid)
    bindings.CppGeoCoordSys_datum(self._cppCoordSys, self.datum)
    bindings.CppGeoCoordSys_units(self._cppCoordSys, self.units)
    bindings.CppGeoCoordSys_initialize(self._cppCoordSys)
    return


  def __init__(self, name="geocoordsys"):
    """Constructor."""
    Component.__init__(self, name, facility="geocoordsys")

    import spatialdata.geocoords.geocoords as bindings
    self._cppCoordSys = bindings.CppGeoCoordSys()
    
    return

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.projection = self.inventory.projection
    self.ellipsoid = self.inventory.ellipsoid
    self.datum = self.inventory.datum
    self.units = self.inventory.units
    return


# version
__id__ = "$Id: GeoCoordSys.py,v 1.2 2005/06/02 21:33:39 baagaard Exp $"

# End of file 
