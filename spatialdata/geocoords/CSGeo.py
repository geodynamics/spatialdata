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

# @file spatialdata/geocoords/CSGeo.py
#
# @brief Python manager for geographic coordinate systems.
#
# Factory: coordsys.

from CoordSys import CoordSys
from geocoords import CSGeo as ModuleCSGeo


class CSGeo(CoordSys, ModuleCSGeo):
    """
    Python manager for geographic coordinate systems.

    Factory: coordsys.

    INVENTORY

    Properties
      - *specification* String specifying coordinate system.
      - *space_dim* Number of dimensions of coordinate system.

    Facilities
      - None
    """

    import pyre.inventory

    specification = pyre.inventory.str("specification", default="EPSG:4326")
    specification.meta['tip'] = "String specifying coordinate system (PROJ parameters, EPSG, or WKT). Default is WGS84."

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
        ModuleCSGeo.setString(self, self.specification)
        ModuleCSGeo.setSpaceDim(self, self.spaceDim)
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
