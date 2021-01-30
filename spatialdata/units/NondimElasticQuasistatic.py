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
# @file spatialdata/units/NondimElasticQuasistatic.py
#
# @brief Python manager for nondimensionalizing quasi-static
# elasticity problems.
#
# Factory: nondimensional

from .Nondimensional import Nondimensional


class NondimElasticQuasistatic(Nondimensional):
    """
    Python manager for nondimensionalizing quasi-static elasticity problems.

    Factory: nondimensional

    INVENTORY

    Properties
      - *shear_modulus* Shear modules for pressure scale of problem.
      - *length_scale* Discretization size for length scale of problem.
      - *relaxation_time* Viscoelastic relaxation time for time scale of problem.

    Facilities
      - None
    """

    import pythia.pyre.inventory

    from pythia.pyre.units.length import meter
    lengthScale = pythia.pyre.inventory.dimensional("length_scale", default=1.0e+3 * meter,
                                             validator=pythia.pyre.inventory.greater(0.0 * meter))
    lengthScale.meta['tip'] = "Value to nondimensionalize length scale."

    from pythia.pyre.units.pressure import pascal
    shearModulus = pythia.pyre.inventory.dimensional("shear_modulus", default=3.0e+10 * pascal,
                                              validator=pythia.pyre.inventory.greater(0.0 * pascal))
    shearModulus.meta['tip'] = "Shear modulus to nondimensionalize pressure."

    from pythia.pyre.units.time import year
    relaxationTime = pythia.pyre.inventory.dimensional("relaxation_time", default=100.0 * year,
                                                validator=pythia.pyre.inventory.greater(0.0 * year))
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
