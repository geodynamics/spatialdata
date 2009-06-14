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

## @brief Python object associated with the C++ UniformVelModel
## object. This objects provides a Pyre interface to the C++ object. 
##
## Factory: spatial_database

from spatialdata.spatialdb.SpatialDBObj import SpatialDBObj
from spatialdatacontrib import UniformVelModel as ModuleUniformVelModel

# UniformVelModel class
class UniformVelModel(SpatialDBObj, ModuleUniformVelModel):
  """
  Python object associated with the C++ UniformVelModel object. This
  objects provides a Pyre interface to the C++ object.  Python manager
  for spatial database to a new velocity model.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing UniformVelModel facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing UniformVelModel facilities and properties.
    ##
    ## \b Properties
    ## @li \b vs S wave speed.
    ## @li \b vp P wave speed.
    ## @li \b density Density.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    from pyre.units.time import s
    from pyre.units.length import km,m
    from pyre.units.mass import kg

    vs = pyre.inventory.dimensional("vs", default=2.6*km/s)
    vs.meta['tip'] = "S wave speed."

    vp = pyre.inventory.dimensional("vp", default=4.5*km/s)
    vp.meta['tip'] = "P wave speed."

    density = pyre.inventory.dimensional("density", default=2.5e+3*kg/m**3)
    density.meta['tip'] = "Density."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="uniformvelmodel"):
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
    SpatialDBObj._configure(self) # Call parent function.
    
    # Transfer inventory to C++ object
    ModuleUniformVelModel.vs(self, self.inventory.vs.value)
    ModuleUniformVelModel.vp(self, self.inventory.vp.value)
    ModuleUniformVelModel.density(self, self.inventory.density.value)
    return


  def _createModuleObj(self):
    """
    Create handle to C++ object.
    """
    ModuleUniformVelModel.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

# Factory used when setting UniformVelModel to a Pyre 'spatial_database' facility.
def spatial_database():
  """
  Factory associated with UniformVelModel.
  """
  return UniformVelModel()


# End of file 
