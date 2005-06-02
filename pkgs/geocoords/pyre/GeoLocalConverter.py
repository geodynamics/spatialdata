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

## @file pyre/SpatialDB.py
## @brief Python manager for converting from geographic coordinates to
## local cartesian coordinates.

from pyre.components.Component import Component

# GeoLocalConverter class
class GeoLocalConverter(Component):
  """Python manager for converting from geographic coordinates to
  local cartesian coordinates."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing GeoLocalConverter facilities
    and properties."""

    ## @class Inventory
    ## Python object for managing GeoLocalConverter facilities and properties.
    ##
    ## \b Properties
    ## @li \b origin-lon Longitude of local origin
    ## @li \b origin-lat Latitude of local origin
    ## @li \b origin-elev Elevation of local origin
    ## @li \b invert Invert conversion for local to geo conversion
    ##
    ## \b Facilities
    ## @li \b geo-coord-sys Geographic coordinate system

    import pyre.inventory

    originLon = pyre.inventory.float("origin-lon", default=0.0)
    originLon.meta['tip'] = "Longitude of local origin"
    
    originLat = pyre.inventory.float("origin-lat", default=0.0)
    originLat.meta['tip'] = "Latitude of local origin"

    originElev = pyre.inventory.float("origin-elev", default=0.0)
    originElev.meta['tip'] = "Elevation of local origin"

    invert = pyre.inventory.bool("invert", default=False)
    invert.meta['tip'] = "Invert conversion for local to geo conversion"

    from GeoCoordSys import GeoCoordSys
    geoCoordSys = pyre.inventory.facility("geo-coord-sys", factory=GeoCoordSys)
    geoCoordSys.meta['tip'] = "Geographic coordinate system"

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    self.geoCoordSys.initialize()

    import spatialdata.geocoords.geocoords as bindings
    self._cppConverter = bindings.CppGeoLocalConverter(self.geoCoordSys.handle())
    bindings.CppGeoLocalConverter_localOrigin(self._cppConverter,
                                              self.originLon,
                                              self.originLat,
                                              self.originElev)
    return


  def convert(self, handle, numLocs, numCoords):
    """Convert geographic coordinates to local cartesian coordinates."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppGeoLocalConverter_localOrigin(self._cppConverter,
                                              self.originLon,
                                              self.originLat,
                                              self.originElev)
    bindings.CppGeoLocalConverter_convert(self._cppConverter,
                                          handle(), numLocs, numCoords,
                                          self.invert)
    return

  def __init__(self, name="geolocalconverter"):
    """Constructor."""
    Component.__init__(self, name, facility="geolocalconverter")
    self._cppConverter = None
    self.originLon = None
    self.originLat = None
    self.originElev = None
    self.invert = None
    self.geoCoordSys = None
    return

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""
    self.originLon = self.inventory.originLon
    self.originLat = self.inventory.originLat
    self.originElev = self.inventory.originElev
    self.invert = self.inventory.invert
    self.geoCoordSys = self.inventory.geoCoordSys
    return

# version
__id__ = "$Id: GeoLocalConverter.py,v 1.2 2005/06/01 23:55:48 baagaard Exp $"

# End of file 
