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

## @file spatialdata/units/Nondimensional.py
##
## @brief Python manager for nondimensionalizing problems.
##
## Factory: nondimensional

from pyre.components.Component import Component
from units import Nondimensional as ModuleNondimensional

# Nondimensional class
class Nondimensional(Component, ModuleNondimensional):
  """
  Python manager for nondimensionalizing problems.

  Factory: nondimensional
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Nondimensional facilities and properties."""

    ## @class Inventory
    ## Python object for managing Nondimensional facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li None


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="nondimensional"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="nondimensional")
    self._createModuleObj()
    return


  def setLengthScale(self, value):
    """
    Get length scale.
    """
    return ModuleNondimensional.lengthScale(self, value.value)


  def lengthScale(self):
    """
    Get length scale.
    """
    from pyre.units.length import meter
    return ModuleNondimensional.lengthScale(self) * meter


  def setPressureScale(self, value):
    """
    Get length scale.
    """
    return ModuleNondimensional.pressureScale(self, value.value)


  def pressureScale(self):
    """
    Get pressure scale.
    """
    from pyre.units.pressure import pascal
    return ModuleNondimensional.pressureScale(self) * pascal


  def setTimeScale(self, value):
    """
    Get time scale.
    """
    return ModuleNondimensional.timeScale(self, value.value)


  def timeScale(self):
    """
    Get time scale.
    """
    from pyre.units.time import second
    return ModuleNondimensional.timeScale(self) * second


  def setDensityScale(self, value):
    """
    Get density scale.
    """
    return ModuleNondimensional.densityScale(self, value.value)


  def densityScale(self):
    """
    Get density scale.
    """
    from pyre.units.length import meter
    from pyre.units.mass import kilogram
    return ModuleNondimensional.densityScale(self) * kilogram / meter**3


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

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleNondimensional.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with Nondimensional.
  """
  return Nondimensional()


# End of file 
