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

# @file spatialdata/spatialdb/GravityField.py
#
# @brief Python manager for spatial database with gravity field information.
#
# Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import GravityField as ModuleGravityField


class GravityField(SpatialDBObj, ModuleGravityField):
    """
    Python manager for spatial database with gravity field information.

    Factory: spatial_database

    INVENTORY

    Properties
      - *gravity_dir* Direction of gravitational body force (only used with Cartesian coordinate system).
      - *acceleration* Gravitational acceleration.
      - *label* Descriptive label for gravity field spatial database.

    Facilities
      - None
    """

    import pyre.inventory

    gravityDir = pyre.inventory.list("gravity_dir", default=[0.0, 0.0, -1.0])
    gravityDir.meta['tip'] = "Direction of gravitational body force. " \
                             "(used only with a Cartesian coordinate system."

    from pyre.units.length import meter
    from pyre.units.time import second
    acceleration = pyre.inventory.dimensional("acceleration",
                                              default=9.80665 * meter / second**2)
    acceleration.meta['tip'] = "Gravitational acceleration."

    label = pyre.inventory.str("label", default="Gravity field")
    label.meta['tip'] = "Descriptive label for gravity field."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="gravityfield"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        self._validateParameters(self.inventory)
        dir = map(float, self.gravityDir)
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
            dirFloat = map(float, params.gravityDir)
        except:
            raise ValueError("Gravity direction must contain floating point values.")


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with GravityField.
    """
    return GravityField()


# End of file
