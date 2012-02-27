#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/geocoords/CSGeoLocalCart.py
##
## @brief Python manager for local coordinate systems.
##
## Factory: coordsys

from CSGeo import CSGeo
from geocoords import CSGeoLocalCart as ModuleCSGeoLocalCart

# CSGeoLocalCart class
class CSGeoLocalCart(CSGeo, ModuleCSGeoLocalCart):
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
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CSGeo._configure(self)
    self.origin(self.inventory.originLon, self.inventory.originLat,
                self.inventory.originElev.value)
    self.isGeocentric(True)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCSGeoLocalCart.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeoLocalCart()


# End of file 
