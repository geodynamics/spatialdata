#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2016 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/units/NondimElasticQuasistatic.py
##
## @brief Python manager for nondimensionalizing quasi-static
## elasticity problems.
##
## Factory: nondimensional

from Nondimensional import Nondimensional

# NondimElasticQuasistatic class
class NondimElasticQuasistatic(Nondimensional):
  """
  Python manager for nondimensionalizing quasi-static elasticity problems.

  Factory: nondimensional
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Nondimensional.Inventory):
    """
    Python object for managing NondimElasticQuasistatic facilities and
    properties.
    """

    ## @class Inventory
    ## Python object for managing NondimElasticQuasistatic facilities and
    ## properties.
    ##
    ## \b Properties
    ## @li \b shear_modulus Shear modulus to nondimensionalize pressure.
    ## @li \b length_scale Value to nondimensionalize length scale.
    ## @li \b relaxation_time Relaxation time to nondimensionalize time.
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    from pyre.units.length import meter
    lengthScale = pyre.inventory.dimensional("length_scale",
                                              default=1.0e+3*meter,
                            validator=pyre.inventory.greater(0.0*meter))
    lengthScale.meta['tip'] = "Value to nondimensionalize length scale."

    from pyre.units.pressure import pascal
    shearModulus = pyre.inventory.dimensional("shear_modulus",
                                              default=3.0e+10*pascal,
                            validator=pyre.inventory.greater(0.0*pascal))
    shearModulus.meta['tip'] = "Shear modulus to nondimensionalize pressure."

    from pyre.units.time import year
    relaxationTime = pyre.inventory.dimensional("relaxation_time",
                                                default=1.0*year,
                            validator=pyre.inventory.greater(0.0*year))
    relaxationTime.meta['tip'] = "Relaxation time to nondimensionalize time."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="nondimelasticquasistatic"):
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
    self.setLengthScale(self.inventory.lengthScale)
    self.setPressureScale(self.inventory.shearModulus)
    self.setTimeScale(self.inventory.relaxationTime)

    # Compute implicit density scale.
    vs = self.inventory.lengthScale / self.inventory.relaxationTime
    self.setDensityScale(self.inventory.shearModulus / vs**2)

    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with NondimElasticQuasistatic.
  """
  return NondimElasticQuasistatic()


# End of file 
