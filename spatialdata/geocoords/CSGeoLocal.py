# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .CSGeo import CSGeo
from .geocoords import CSGeoLocal as ModuleCSGeoLocal


class CSGeoLocal(CSGeo, ModuleCSGeoLocal):
    """
    Python manager for local, rotated geographic coordinate systems.

    Implements `CSGeo`.
    """
    DOC_CONFIG = {
        "cfg": """
            [coordsys]
            # Local, rotated UTM Zone 10 coordinate system
            crs_string = EPSG:29610
            space_dim = 2
            origin_x = 300000.0
            origin_y = 4000000.0
            y_azimuth = -25.0
            """,
    }

    import pythia.pyre.inventory

    crsString = pythia.pyre.inventory.str("crs_string", default="EPSG:4326")
    crsString.meta['tip'] = "String specifying coordinate system (PROJ parameters, EPSG, or WKT). Default is WGS84."

    spaceDim = pythia.pyre.inventory.int("space_dim", default=3)
    spaceDim.meta['tip'] = "Number of dimensions for coordinate system."

    originX = pythia.pyre.inventory.float("origin_x", default=0.0)
    originX.meta['tip'] = "X coordinate of local origin."

    originY = pythia.pyre.inventory.float("origin_y", default=0.0)
    originY.meta['tip'] = "Y coordinate of local origin."

    yAzimuth = pythia.pyre.inventory.float("y_azimuth", default=0.0)
    yAzimuth.meta['tip'] = "Azimuth (degrees) of local y axis."


    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="csgeoLocal"):
        """
        Constructor.
        """
        CSGeo.__init__(self, name)

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Setup members using inventory.
        """
        CSGeo._configure(self)
        ModuleCSGeoLocal.setString(self, self.crsString)
        ModuleCSGeoLocal.setSpaceDim(self, self.spaceDim)
        ModuleCSGeoLocal.setLocal(self, self.originX, self.originY, self.yAzimuth)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleCSGeoLocal.__init__(self)
        return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
    """
    Factory associated with CSGeo.
    """
    return CSGeoLocal()


# End of file
