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
    ## @li \b up_dir Direction opposite of gravity ("up").
    ## @li \b acceleration Gravitational acceleration.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    upDir = pyre.inventory.list("up_dir", default=[0,0,1])
    upDir.meta['tip'] = "Direction opposite of gravity ('up')."

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
    self.cppHandle.upDir(self.upDir)
    self.cppHandle.gravAcceleration(self.acceleration.value)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self._validate(self.inventory)
    self.upDir = self.inventory.upDir
    self.acceleration = self.inventory.acceleration
    return


  def _validate(self, data):
    """
    Validate parameters.
    """
    if (len(data.upDir) != 3):
      raise ValueError("Up direction must be a 3 component list or tuple.")
    try:
      dataFloat = map(float, data.upDir)
    except:
        raise ValueError, \
              "'upDir' must contain floating point values."
    return
  

# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with GravityField.
  """
  return GravityField()


# End of file 
