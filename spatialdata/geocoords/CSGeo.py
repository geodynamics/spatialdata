#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/geocoords/CSGeo.py
##
## @brief Python manager for geographic coordinate systems.
##
## Factory: coordsys.

from CoordSys import CoordSys
from geocoords import CSGeo as ModuleCSGeo

# CSGeo class
class CSGeo(CoordSys, ModuleCSGeo):
  """
  Python manager for geographic coordinate systems.

  Factory: coordsys.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CoordSys.Inventory):
    """
    Python object for managing CSGeo facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CSGeo facilities and properties.
    ##
    ## \b Properties
    ## @li \b ellipsoid Name of ellipsoid
    ## @li \b datum_horiz Name of horizontal datum
    ## @li \b datum_vert Name of vertical datum
    ## @li \b is_geocentric True if geocentric, false if lon/lat
    ## @li \b units Name of units
    ## @li \b space_dim Number of dimensions for coordinate system
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    ellipsoid = pyre.inventory.str("ellipsoid", default="WGS84")
    ellipsoid.meta['tip'] = "Name of ellipsoid."

    datumHoriz = pyre.inventory.str("datum_horiz", default="WGS84")
    datumHoriz.meta['tip'] = "Name of horizontal datum."

    datumVert = pyre.inventory.str("datum_vert", default="ellipsoid")
    datumVert.meta['tip'] = "Name of vertical datum."

    isGeocentric = pyre.inventory.bool("is_geocentric", default=False)
    isGeocentric.meta['tip'] = "Flag indicating geocentric coordinate system."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    spaceDim = pyre.inventory.int("space_dim", default=3)
    spaceDim.meta['tip'] = "Number of dimensions for coordinate system."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="csgeo"):
    """
    Constructor.
    """
    CoordSys.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CoordSys._configure(self)
    self.ellipsoid(self.inventory.ellipsoid)
    self.datumHoriz(self.inventory.datumHoriz)
    self.datumVert(self.inventory.datumVert)
    self.isGeocentric(self.inventory.isGeocentric)
    self.setSpaceDim(self.inventory.spaceDim)

    import pyre.units
    uparser = pyre.units.parser()
    coordUnits = uparser.parse(self.inventory.units)
    self.toMeters(coordUnits.value)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCSGeo.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeo()


# End of file 
