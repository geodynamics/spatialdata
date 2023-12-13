# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from pythia.pyre.components.Component import Component
from .units import Nondimensional as ModuleNondimensional


class Nondimensional(Component, ModuleNondimensional):
    """
    Abstract base class for nondimensionalizing problems.
    """

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="nondimensional"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="nondimensional")

    def _configure(self):
        Component._configure(self)
        self._createModuleObj()

    def setLengthScale(self, value):
        """
        Get length scale.
        """
        return ModuleNondimensional.setLengthScale(self, value.value)

    def getLengthScale(self):
        """
        Get length scale.
        """
        from pythia.pyre.units.length import meter
        return ModuleNondimensional.getLengthScale(self) * meter

    def setPressureScale(self, value):
        """
        Get length scale.
        """
        return ModuleNondimensional.setPressureScale(self, value.value)

    def getPressureScale(self):
        """
        Get pressure scale.
        """
        from pythia.pyre.units.pressure import pascal
        return ModuleNondimensional.getPressureScale(self) * pascal

    def setTimeScale(self, value):
        """
        Get time scale.
        """
        return ModuleNondimensional.setTimeScale(self, value.value)

    def getTimeScale(self):
        """
        Get time scale.
        """
        from pythia.pyre.units.time import second
        return ModuleNondimensional.getTimeScale(self) * second

    def setDensityScale(self, value):
        """
        Get density scale.
        """
        return ModuleNondimensional.setDensityScale(self, value.value)

    def getDensityScale(self):
        """
        Get density scale.
        """
        from pythia.pyre.units.length import meter
        from pythia.pyre.units.mass import kilogram
        return ModuleNondimensional.getDensityScale(self) * kilogram / meter**3

    def setTemperatureScale(self, value):
        """
        Get temperature scale.
        """
        return ModuleNondimensional.setTemperatureScale(self, value.value)

    def getTemperatureScale(self):
        """
        Get temperature scale.
        """
        from pythia.pyre.units.temperature import kelvin
        return ModuleNondimensional.getTemperatureScale(self) * kelvin

    def nondimensionalize(self, value, scale):
        """
        Make value dimensionless.
        """
        return value / scale

    def dimensionalize(self, value, scale):
        """
        Make value dimensional.
        """
        return value * scale

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleNondimensional.__init__(self)


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
    """
    Factory associated with Nondimensional.
    """
    return Nondimensional()


# End of file
