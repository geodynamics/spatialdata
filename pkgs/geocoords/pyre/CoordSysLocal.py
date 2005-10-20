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

## @file geocoords/pyre/CoordSysLocal.py
## @brief Python manager for local coordinate systems.

from CoordSys import CoordSys

# CoordSys class
class CoordSysLocal(CoordSys):
  """Python manager for local coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CoordSys.Inventory):
    """Python object for managing CoordSysLocal facilities and properties."""

    ## @class Inventory
    ## Python object for managing CoordSysLocal facilities and properties.
    ##
    ## \b Properties
    ## @li \b origin-lon Lontitude of origin of degrees
    ## @li \b origin-lat Latitude of origin of degrees
    ## @li \b origin-elev Elevation (wrt vertical datum) of origin
    ## @li \b ellipsoid Name of reference ellipsoid
    ## @li \b datum-horiz Name of horizontal datum
    ## @li \b datum-vert Name of vertical datum
    ## @li \b units Name of units
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

    ellipsoid = pyre.inventory.str("ellipsoid", default="WGS84")
    ellipsoid.meta['tip'] = "Name of ellipsoid."

    datumHoriz = pyre.inventory.str("datum-horiz", default="WGS84")
    datumHoriz.meta['tip'] = "Name of horizontal datum."

    datumVert = pyre.inventory.str("datum-vert", default="WGS84 ellipsoid")
    datumVert.meta['tip'] = "Name of vertical datum."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize coordinate system."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppCoordSysLocal_localOrigin(self._cppCoordSys,
                                          self.originLon,
                                          self.originLat,
                                          self.originElev,
                                          self.ellipsoid,
                                          self.datumHoriz,
                                          self.datumVert)

    import pyre.units
    uparser = pyre.units.parser()
    xyzUnits = uparser.parse(self.units)
    bindings.CppCoordSysLocal_xyzToMeters(self._cppCoordSys, xyzUnits.value)

    CoordSys.initialize(self)
    return


  def __init__(self, name="coordsyslocal"):
    """Constructor."""
    CoordSys.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self._cppCoordSys = bindings.CppCoordSysLocal()

    self.originLon = 0.0
    self.originLat = 0.0
    self.originElev = 0.0
    self.ellipsoid = "WGS84"
    self.datumHoriz = "WGS84"
    self.datumVert = "WGS84 ellipsoid"
    self.units = "m"
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.originLon = self.inventory.originLon
    self.originLat = self.inventory.originLat
    self.originElev = self.inventory.originElev
    self.ellipsoid = self.inventory.ellipsoid
    self.datumHoriz = self.inventory.datumHoriz
    self.datumVert = self.inventory.datumVert
    self.units = self.inventory.units
    return


# version
__id__ = "$Id$"

# End of file 
