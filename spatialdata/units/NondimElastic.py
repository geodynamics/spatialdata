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

## @file spatialdata/units/NondimElastic.py
##
## @brief Python manager for nondimensionalizing elasticity problems.
##
## Factory: nondimensional

from pyre.components.Component import Component

# NondimElastic class
class NondimElastic(Component):
  """
  Python manager for nondimensionalizing elasticity problems.

  Factory: nondimensional
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing NondimElastic facilities and properties."""

    ## @class Inventory
    ## Python object for managing NondimElastic facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li None

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="nondimelastic"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="nondimelastic")

    self.cppHandle = None
    from pyre.units.length import meter
    from pyre.units.pressure import pascal
    from pyre.units.time import second
    from pyre.units.mass import kilogram

    self._length = 1.0*meter
    self._pressure = 1.0*pascal
    self._time = 1.0*second
    self._density = 1.0*kilogram/meter**3
    return


  def initialize(self):
    """
    Initialize coordinate system.
    """
    self._createCppHandle()
    self.cppHandle.length = self._length.value
    self.cppHandle.pressure = self._pressure.value
    self.cppHandle.time = self._time.value
    self.cppHandle.density = self._density.value
    return


  def utonLength(self, value):
    """
    Make length scale dimensionless.
    """
    return value / self._length


  def ntouLength(self, value):
    """
    Add dimensions to length scale.
    """
    return value * self._length


  def utonPressure(self, value):
    """
    Make pressure scale dimensionless.
    """
    return value / self._pressure


  def ntouPressure(self, value):
    """
    Add dimensions to pressure scale.
    """
    return value * self._pressure


  def utonTime(self, value):
    """
    Make time scale dimensionless.
    """
    return value / self._time


  def ntouTime(self, value):
    """
    Add dimensions to time scale.
    """
    return value * self._time


  def utonDensity(self, value):
    """
    Make density scale dimensionless.
    """
    return value / self._density


  def ntouDensity(self, value):
    """
    Add dimensions to density scale.
    """
    return value * self._density


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    return


  def _createCppHandle(self):
    """
    Create handle to C++ object.
    """
    if None == self.cppHandle:
      import spatialdata.units.units as bindings
      self.cppHandle = bindings.NondimElastic()
    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with NondimElastic.
  """
  return NondimElastic()


# End of file 
