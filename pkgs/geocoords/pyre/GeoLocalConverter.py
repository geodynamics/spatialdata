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

    from GeoCoordSys import GeoCoordSys
    geoCoordSys = pyre.inventory.facility("geo-coord-sys", factory=GeoCoordSys)
    geoCoordSys.meta['tip'] = "Geographic coordinate system"

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="geolocalconverter"):
    """Constructor."""
    Component.__init__(self, name, facility="geolocalconverter")
    return

# version
__id__ = "$Id: GeoLocalConverter.py,v 1.1 2005/05/28 00:31:04 baagaard Exp $"

# End of file 
