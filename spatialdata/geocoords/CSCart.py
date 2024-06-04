# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .CoordSys import CoordSys
from .geocoords import CSCart as ModuleCSCart


class CSCart(CoordSys, ModuleCSCart):
    """
    Python manager for Cartesian coordinate systems.

    Implements `CoordSys`.
    """
    DOC_CONFIG = {
        "cfg": """
            [coordsys]
            units = meter
            space_dim = 3
            """,
    }

    import pythia.pyre.inventory

    units = pythia.pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    spaceDim = pythia.pyre.inventory.int("space_dim", default=3)
    spaceDim.meta['tip'] = "Number of dimensions for coordinate system."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="cscart"):
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

        import pythia.pyre.units
        uparser = pythia.pyre.units.parser()
        coordUnits = uparser.parse(self.inventory.units)
        ModuleCSCart.setToMeters(self, coordUnits.value)
        ModuleCSCart.setSpaceDim(self, self.spaceDim)
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleCSCart.__init__(self)
        return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
    """
    Factory associated with CoordSys.
    """
    return CSCart()


# End of file
