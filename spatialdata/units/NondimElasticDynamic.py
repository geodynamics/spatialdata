# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------

from .Nondimensional import Nondimensional


class NondimElasticDynamic(Nondimensional):
    """
    Convenience object for nondimensionalizing dynamic elasticity problems.

    Implements `Nondimensional`.
    """
    DOC_CONFIG = {
        "cfg": """
            [normalizer]
            shear_wave_speed = 3.0*km/s
            mass_density = 3.0*kg/m**3
            wave_period = 2.0*s
            """,
    }

    import pythia.pyre.inventory

    from pythia.pyre.units.length import meter
    from pythia.pyre.units.time import second
    from pythia.pyre.units.mass import kg
    shearWaveSpeed = pythia.pyre.inventory.dimensional("shear_wave_speed", default=3.0e+3 * meter / second)
    shearWaveSpeed.validator = pythia.pyre.inventory.greater(0.0 * meter / second)
    shearWaveSpeed.meta['tip'] = "Shear wave speed to nondimensionalize problem."

    massDensity = pythia.pyre.inventory.dimensional("mass_density", default=3.0e+3 * kg / meter**3)
    massDensity.validator = pythia.pyre.inventory.greater(0.0 * kg / meter**3)
    massDensity.meta['tip'] = "Mass density to nondimensionalize problem"

    wavePeriod = pythia.pyre.inventory.dimensional("wave_period", default=1.0 * second)
    wavePeriod.validator = pythia.pyre.inventory.greater(0.0 * second)
    wavePeriod.meta['tip'] = "Period of wave to nondimensionalize problem."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="nondimelasticdynamic"):
        """
        Constructor.
        """
        Nondimensional.__init__(self, name)

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Setup members using inventory.
        """
        Nondimensional._configure(self)
        vs = self.inventory.shearWaveSpeed
        period = self.inventory.wavePeriod
        density = self.inventory.massDensity
        self.setLengthScale(vs * period)
        self.setTimeScale(period)
        self.setDensityScale(density)
        self.computePressureScale()


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
    """
    Factory associated with NondimElasticDynamic.
    """
    return NondimElasticDynamic()


# End of file
