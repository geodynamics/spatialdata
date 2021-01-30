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
# @file spatialdata/units/Nondimensional.py
#
# @brief Python manager for nondimensionalizing problems.
#
# Factory: nondimensional

from pythia.pyre.components.Component import Component
from .units import Nondimensional as ModuleNondimensional


class Nondimensional(Component, ModuleNondimensional):
    """
    Python manager for nondimensionalizing problems.

    Factory: nondimensional

    INVENTORY

    Properties
      - None

    Facilities
      - None
    """

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="nondimensional"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="nondimensional")
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
