#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
#
# ----------------------------------------------------------------------
#

## @file spatialdata/units/NondimElasticQuasistatic.py
##
## @brief Python manager for nondimensionalizing quasi-static
## elasticity problems.
##
## Factory: nondimensional

from NondimElastic import NondimElastic

# NondimElasticQuasistatic class
class NondimElasticQuasistatic(NondimElastic):
  """
  Python manager for nondimensionalizing quasi-static elasticity problems.

  Factory: nondimensional
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(NondimElastic.Inventory):
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
    relaxationTime.meta['tip'] = "Relaxatim time to nondimensionalize time."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="nondimelastic"):
    """
    Constructor.
    """
    NondimElastic.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    NondimElastic._configure(self)
    self._length = self.inventory.lengthScale
    self._pressure = self.inventory.shearModulus
    self._time = self.inventory.relaxationTime

    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with NondimElasticQuasistatic.
  """
  return NondimElasticQuasistatic()


# End of file 
