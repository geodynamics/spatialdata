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

## @file geocoords/pyre/CSGeo.py
## @brief Python manager for geographic coordinate systems.

from CoordSys import CoordSys

# CSGeo class
class CSGeo(CoordSys):
  """Python manager for geographic coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CoordSys.Inventory):
    """Python object for managing CSGeo facilities and properties."""

    ## @class Inventory
    ## Python object for managing CSGeo facilities and properties.
    ##
    ## \b Properties
    ## @li \b ellipsoid Name of ellipsoid
    ## @li \b datum-horiz Name of horizontal datum
    ## @li \b datum-vert Name of vertical datum
    ## @li \b is-geocentric True if geocentric, false if lon/lat
    ## @li \b units Name of units
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    ellipsoid = pyre.inventory.str("ellipsoid", default="WGS84")
    ellipsoid.meta['tip'] = "Name of ellipsoid."

    datumHoriz = pyre.inventory.str("datum-horiz", default="WGS84")
    datumHoriz.meta['tip'] = "Name of horizontal datum."

    datumVert = pyre.inventory.str("datum-vert", default="ellipsoid")
    datumVert.meta['tip'] = "Name of vertical datum."

    isGeocentric = pyre.inventory.bool("is-geocentric", default=False)
    isGeocentric.meta['tip'] = "Flag indicating geocentric coordinate system."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize coordinate system."""
    import spatialdata.geocoords.geocoords as bindings
    bindings.CppCSGeo_ellipsoid(self._cppCoordSys, self.ellipsoid)
    bindings.CppCSGeo_datumHoriz(self._cppCoordSys, self.datumHoriz)
    bindings.CppCSGeo_datumVert(self._cppCoordSys, self.datumVert)
    bindings.CppCSGeo_isGeocentric(self._cppCoordSys, self.isGeocentric)

    import pyre.units
    uparser = pyre.units.parser()
    coordUnits = uparser.parse(self.units)
    bindings.CppCSGeo_toMeters(self._cppCoordSys, coordUnits.value)

    CoordSys.initialize(self)
    return


  def __init__(self, name="csgeo"):
    """Constructor."""
    CoordSys.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self._cppCoordSys = bindings.CppCSGeo()
    self.ellipsoid = "WGS84"
    self.datumHoriz = "WGS84"
    self.datumVert = "ellipsoid"
    self.isGeocentric = False
    self.units = "m"
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.ellipsoid = self.inventory.ellipsoid
    self.datumHoriz = self.inventory.datumHoriz
    self.datumVert = self.inventory.datumVert
    self.isGeocentric = self.inventory.isGeocentric
    self.units = self.inventory.units
    return


# version
__id__ = "$Id$"

# End of file 
