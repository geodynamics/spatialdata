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

## @file spatialdata/geocoords/CSGeoLocalCart.py
##
## @brief Python manager for local coordinate systems.
##
## Factory: coordsys

from CSGeo import CSGeo

# CSGeoLocalCart class
class CSGeoLocalCart(CSGeo):
  """
  Python manager for local coordinate systems.

  Factory: coordsys
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """
    Python object for managing CSGeoLocalCart facilities and properties.
    """

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

    originLon = pyre.inventory.float("origin-lon", default=0.0)
    originLon.meta['tip'] = "Longitude of origin in degrees."

    originLat = pyre.inventory.float("origin-lat", default=0.0)
    originLat.meta['tip'] = "Latitude of origin in degrees."

    from pyre.units.length import m
    originElev = pyre.inventory.dimensional("origin-elev", default=0.0*m)
    originElev.meta['tip'] = "Elevation of origin."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="csgeolocalcart"):
    """
    Constructor.
    """
    CSGeo.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self.cppHandle = bindings.CSGeoLocalCart()

    self.originLon = 0.0
    self.originLat = 0.0
    self.originElev = 0.0
    self.isGeocentric = True
    return


  def initialize(self):
    """
    Initialize coordinate system.
    """
    self.cppHandle.origin(self.originLon, self.originLat,
                          self.originElev.value)
    CSGeo.initialize(self)

    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CSGeo._configure(self)
    self.originLon = self.inventory.originLon
    self.originLat = self.inventory.originLat
    self.originElev = self.inventory.originElev
    self.isGeocentric = True
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeoLocalCart()


# End of file 
