# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .Nondimensional import Nondimensional


class NondimElasticQuasistatic(Nondimensional):
    """
    Convenience object for nondimensionalizing quasi-static elasticity problems.

    Implements `Nondimensional`.
    """
    DOC_CONFIG = {
        "cfg": """
            [normalizer]
            length_scale = 5.0*km
            shear_modulus = 30.0*GPa
            relaxation_time = 200.0*year
            """,
    }

    import pythia.pyre.inventory

    from pythia.pyre.units.length import meter
    lengthScale = pythia.pyre.inventory.dimensional("length_scale", default=1.0e+3 * meter)
    lengthScale.validator = pythia.pyre.inventory.greater(0.0 * meter)
    lengthScale.meta['tip'] = "Value to nondimensionalize length scale."

    from pythia.pyre.units.pressure import pascal
    shearModulus = pythia.pyre.inventory.dimensional("shear_modulus", default=3.0e+10 * pascal)
    shearModulus.validator = pythia.pyre.inventory.greater(0.0 * pascal)
    shearModulus.meta['tip'] = "Shear modulus to nondimensionalize pressure."

    from pythia.pyre.units.time import year
    relaxationTime = pythia.pyre.inventory.dimensional("relaxation_time", default=100.0 * year)
    relaxationTime.validator = pythia.pyre.inventory.greater(0.0 * year)
    relaxationTime.meta['tip'] = "Relaxation time to nondimensionalize time."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="nondimelasticquasistatic"):
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
        self.setLengthScale(self.inventory.lengthScale)
        self.setPressureScale(self.inventory.shearModulus)
        self.setTimeScale(self.inventory.relaxationTime)
        self.computeDensityScale()


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
    """
    Factory associated with NondimElasticQuasistatic.
    """
    return NondimElasticQuasistatic()


# End of file
