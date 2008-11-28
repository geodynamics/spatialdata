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

# Nondimensional class
class Nondimensional(Component):
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


  def lengthScale(self):
    """
    Get length scale.
    """
    return self._length


  def pressureScale(self):
    """
    Get pressure scale.
    """
    return self._pressure


  def timeScale(self):
    """
    Get time scale.
    """
    return self._time


  def densityScale(self):
    """
    Get density scale.
    """
    return self._density


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


  def _createCppHandle(self):
    """
    Create handle to C++ object.
    """
    if None == self.cppHandle:
      import spatialdata.units.units as bindings
      self.cppHandle = bindings.Nondimensional()
    return


# FACTORIES ////////////////////////////////////////////////////////////

def nondimensional():
  """
  Factory associated with Nondimensional.
  """
  return Nondimensional()


# End of file 
