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

## @file spatialdata/spatialdb/GravityField.py
##
## @brief Python manager for spatial database with gravity field information.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import GravityField as ModuleGravityField

# GravityField class
class GravityField(SpatialDBObj, ModuleGravityField):
  """
  Python manager for spatial database with gravity field information.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing GravityField facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing GravityField facilities and properties.
    ##
    ## \b Properties
    ## @li \b gravity_dir Direction of gravitational body force
    ##   (used only with a Cartesian coordinate system).
    ## @li \b acceleration Gravitational acceleration.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    gravityDir = pyre.inventory.list("gravity_dir", default=[0.0,0.0,-1.0])
    gravityDir.meta['tip'] = "Direction of gravitational body force. " \
                             "(used only with a Cartesian coordinate system."

    from pyre.units.length import meter
    from pyre.units.time import second
    acceleration = pyre.inventory.dimensional("acceleration",
                                              default=9.80665*meter/second**2)
    acceleration.meta['tip'] = "Gravitational acceleration."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="gravityfield"):
    """
    Constructor.
    """
    SpatialDBObj.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDBObj._configure(self)
    self._validateParameters(self.inventory)
    dir = map(float, self.inventory.gravityDir)
    self.gravityDir(dir[0], dir[1], dir[2])
    self.gravAcceleration(self.inventory.acceleration.value)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleGravityField.__init__(self)
    return


  def _validateParameters(self, params):
    """
    Validate parameters.
    """
    if (len(params.gravityDir) != 3):
      raise ValueError, \
            "Gravity direction must be a 3 component list or tuple."
    try:
      dirFloat = map(float, params.gravityDir)
    except:
        raise ValueError, \
              "'gravityDir' must contain floating point values."
    return
  

# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with GravityField.
  """
  return GravityField()


# End of file 
