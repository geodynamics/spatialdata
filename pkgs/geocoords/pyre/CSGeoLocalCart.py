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

## @file geocoords/pyre/CSGeoLocalCart.py
## @brief Python manager for local coordinate systems.

from CSGeo import CSGeo

# CSGeoLocalCart class
class CSGeoLocalCart(CSGeo):
  """Python manager for local coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """Python object for managing CSGeoLocalCart facilities and properties."""

    ## @class Inventory
    ## Python object for managing CSGeoLocalCart facilities and properties.
    ##
    ## \b Properties
    ## @li \b origin-lon Lontitude of origin of degrees
    ## @li \b origin-lat Latitude of origin of degrees
    ## @li \b origin-elev Elevation (wrt vertical datum) of origin
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    originLon = pyre.inventory.str("origin-lon", default="0.0")
    originLon.meta['tip'] = "Longitude of origin in degrees."

    originLat = pyre.inventory.str("origin-lat", default="0.0")
    originLat.meta['tip'] = "Latitude of origin in degrees."

    originElev = pyre.inventory.str("origin-elev", default="0.0")
    originElev.meta['tip'] = "Elevation of origin."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize coordinate system."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppCSGeoLocalCart_origin(self._cppCoordSys,
                                      self.originLon,
                                      self.originLat,
                                      self.originElev)

    CSGeo.initialize(self)
    return


  def __init__(self, name="csgeolocalcart"):
    """Constructor."""
    CSGeo.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self._cppCoordSys = bindings.CppCSGeoLocalCart()

    self.originLon = 0.0
    self.originLat = 0.0
    self.originElev = 0.0
    self.isGeocentric = True
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.originLon = self.inventory.originLon
    self.originLat = self.inventory.originLat
    self.originElev = self.inventory.originElev
    self.isGeocentric = True
    return


# version
__id__ = "$Id$"

# End of file 
