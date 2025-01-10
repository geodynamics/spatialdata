# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .SpatialDBObj import SpatialDBObj
from .spatialdb import GravityField as ModuleGravityField


class GravityField(SpatialDBObj, ModuleGravityField):
    """
    Spatial database with gravity field information.

    Implements `SpatialDB`. 
    """
    DOC_CONFIG = {
        "cfg": """
            # Specify a gravity field in 2D with gravity in the -y direction.
            [gravity_field]
            gravity_dir = [0, -1]
            acceleration = 9.80665*meter/second**2
            """,
    }

    import pythia.pyre.inventory

    gravityDir = pythia.pyre.inventory.list("gravity_dir", default=[0.0, 0.0, -1.0])
    gravityDir.meta['tip'] = "Direction of gravitational body force. " \
                             "(used only with a Cartesian coordinate system."

    from pythia.pyre.units.length import meter
    from pythia.pyre.units.time import second
    acceleration = pythia.pyre.inventory.dimensional("acceleration",
                                              default=9.80665 * meter / second**2)
    acceleration.meta['tip'] = "Gravitational acceleration."

    def __init__(self, name="gravityfield"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)
        return

    def _defaults(self):
        self.description = "Gravity field"
    
    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        self._validateParameters(self.inventory)
        dir = list(map(float, self.gravityDir))
        ModuleGravityField.setGravityDir(self, dir[0], dir[1], dir[2])
        ModuleGravityField.setGravityAcc(self, self.acceleration.value)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleGravityField.__init__(self)

    def _validateParameters(self, params):
        """
        Validate parameters.
        """
        if (len(params.gravityDir) != 3):
            raise ValueError("Gravity direction must be a 3 component list or tuple.")
        try:
            dirFloat = list(map(float, params.gravityDir))
        except:
            raise ValueError("Gravity direction must contain floating point values.")


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with GravityField.
    """
    return GravityField()


# End of file
