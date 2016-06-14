#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2016 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/geocoords/CSGeoProj.py
##
## @brief Python manager for geographic coordinate systems.
##
## Factory: CSGeoProj

from CSGeo import CSGeo
from geocoords import CSGeoProj as ModuleCSGeoProj

# CoordSysGeo class
class CSGeoProj(CSGeo, ModuleCSGeoProj):
  """
  Python manager for projected geographic coordinate systems.

  Factory: CSGeoProj
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """
    Python object for managing CSGeoProj facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CSGeoProj facilities and properties.
    ##
    ## \b Properties
    ## @li origin_lon Longitude of local origin in degrees (WGS84).
    ## @li origin_lat Latitude of local origin in degrees (WGS84).
    ## @li rotation_angle Rotation angle in degrees CCW of local x-axis from east.
    ##
    ## \b Facilities
    ## @li \b projector Geographic coordinate projector

    import pyre.inventory

    originLon = pyre.inventory.float("origin_lon", default=0.0)
    originLon.meta['tip'] = "Longitude of local origin in degrees (WGS84)."

    originLat = pyre.inventory.float("origin_lat", default=0.0)
    originLat.meta['tip'] = "Latitude of local origin in degrees (WGS84)."

    rotAngle = pyre.inventory.float("rotation_angle", default=0.0)
    rotAngle.meta['tip'] = "Rotation angle in degrees CCW of local x-axis from east."

    from Projector import Projector
    projector = pyre.inventory.facility("projector", family="projector",
                                        factory=Projector)
    projector.meta['tip'] = "Geographic coordinate projector."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="csgeoproj"):
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
    ModuleCSGeoProj.origin(self, 
                           self.inventory.originLon,
                           self.inventory.originLat)
    ModuleCSGeoProj.rotationAngle(self, self.inventory.rotAngle)
    ModuleCSGeoProj.projector(self, self.inventory.projector)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCSGeoProj.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeoProj()


# End of file 
