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

## @file spatialdata/units/NondimElasticDynamic.py
##
## @brief Python manager for nondimensionalizing dynamic
## elasticity problems.
##
## Factory: nondimensional

from Nondimensional import Nondimensional

# NondimElasticDynamic class
class NondimElasticDynamic(Nondimensional):
  """
  Python manager for nondimensionalizing dynamic elasticity problems.

  Factory: nondimensional
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Nondimensional.Inventory):
    """
    Python object for managing NondimElasticDynamic facilities and
    properties.
    """

    ## @class Inventory
    ## Python object for managing NondimElasticDynamic facilities and
    ## properties.
    ##
    ## \b Properties
    ## @li \b shear_wave_speed Shear wave speed to nondimensionalize problem.
    ## @li \b mass_density Mass density to nondimensionalize problem.
    ## @li \b wave_period Period of wave to nondimensionalize problem.
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    from pyre.units.length import meter
    from pyre.units.time import second
    from pyre.units.mass import kg
    shearWaveSpeed = pyre.inventory.dimensional("shear_wave_speed",
                                                default=3.0e+3*meter/second,
                        validator=pyre.inventory.greater(0.0*meter/second))
    shearWaveSpeed.meta['tip'] = "Shear wave speed to nondimensionalize problem."

    massDensity = pyre.inventory.dimensional("mass_density",
                                             default=3.0e+3*kg/meter**3,
                            validator=pyre.inventory.greater(0.0*kg/meter**3))
    massDensity.meta['tip'] = "Mass density to nondimensionalize problem"

    wavePeriod = pyre.inventory.dimensional("wave_period",
                                            default=1.0*second,
                            validator=pyre.inventory.greater(0.0*second))
    wavePeriod.meta['tip'] = "Period of wave to nondimensionalize problem."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="nondimelasticdynamic"):
    """
    Constructor.
    """
    Nondimensional.__init__(self, name)
    return


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
    self.setPressureScale(vs**2 * density)
    self.setTimeScale(period)
    self.setDensityScale(density)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with NondimElasticDynamic.
  """
  return NondimElasticDynamic()


# End of file 
