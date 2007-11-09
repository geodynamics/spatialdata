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

from SpatialDB import SpatialDB

# GravityField class
class GravityField(SpatialDB):
  """
  Python manager for spatial database with gravity field information.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """
    Python object for managing GravityField facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing GravityField facilities and properties.
    ##
    ## \b Properties
    ## @li \b up_dir Direction of gravitational body force
    ##   (used only with a Cartesian coordinate system).
    ## @li \b acceleration Gravitational acceleration.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    gravityDir = pyre.inventory.list("gravity_dir", default=[0,0,-1])
    gravityDir.meta['tip'] = "Direction of gravitational body force. " \
                             "(used only with a Cartesian coordinate system."

    from pyre.units.length import meter
    from pyre.units.time import second
    acceleration = pyre.inventory.dimensional("acceleration",
                                              default=9.80665*meter/second**2)
    acceleration.meta['tip'] = "Gravitational acceleration."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="uniformdb"):
    """
    Constructor.
    """
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.GravityField()
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self)
    self.cppHandle.gravityDir(self.gravityDir)
    self.cppHandle.gravAcceleration(self.acceleration.value)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self._validate(self.inventory)
    self.gravityDir = self.inventory.gravityDir
    self.acceleration = self.inventory.acceleration
    return


  def _validate(self, data):
    """
    Validate parameters.
    """
    if (len(data.gravityDir) != 3):
      raise ValueError, \
            "Gravity direction must be a 3 component list or tuple."
    try:
      dataFloat = map(float, data.gravityDir)
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
