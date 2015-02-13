#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2015 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @brief Python object associated with the C++ UniformVelModel
## object. This objects provides a Pyre interface to the C++ object. 
##
## Factory: spatial_database

from spatialdata.spatialdb.SpatialDBObj import SpatialDBObj
from spatialdbcontrib import UniformVelModel as ModuleUniformVelModel

# UniformVelModel class
class UniformVelModel(SpatialDBObj, ModuleUniformVelModel):
  """
  Python object associated with the C++ UniformVelModel object. This
  objects provides a Pyre interface to the C++ object. It inherits
  from the generic SpatialDBObj and the UniformVelModel SWIG module
  object. This insures that this object has all of the SpatialDBObj
  Pyre properties and facilities and functions and calls to the
  underlying C++ code are passed onto the SWIG Python module.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing UniformVelModel Pyre facilities and properties.

    ## \b Properties
    ## @li \b vs S wave speed.
    ## @li \b vp P wave speed.
    ## @li \b density Density.
    ##
    ## \b Facilities
    ## @li none
    """

    import pyre.inventory

    # Units used in properties
    from pyre.units.time import s
    from pyre.units.length import km,m
    from pyre.units.mass import kg

    # Pyre properties have the form
    #
    # VARIABLE = pyre.inventory.TYPE("CFG_NAME", default=DEFAULT_VALUE)
    # VARIABLE.meta['tip'] = "HELP STRING"
    #
    # where VARIABLE is a variable used to refer to the Pyre property,
    # TYPE of the type of property (dimensional, str, float, int,
    # etc), CFG_NAME is the name used in the Pyre .cfg files and the
    # command line, and DEFAULT_VALUE is the default value.
    #
    # When a Pyre property is a dimensional scalar quantity, use the
    # dimensional type for properties and Pyre will automatically
    # check to make sure user-specified quantities have compatible
    # units and convert the value to SI units.
    #
    # The help string will be printed when the user uses the command
    # line arugments --FULL_COMPONENT_NAME.help-properties or
    # --FULL_COMPONENT.help-components. See the PyLith manual chapter
    # "Running PyLith" for more information regarding getting help
    # using command line arguments.
    #
    # Create a Pyre property named vs with a default value of 2.6 km/s.
    vs = pyre.inventory.dimensional("vs", default=2.6*km/s)
    vs.meta['tip'] = "S wave speed."

    # Create a Pyre property named vp with a default value of 4.5 km/s.
    vp = pyre.inventory.dimensional("vp", default=4.5*km/s)
    vp.meta['tip'] = "P wave speed."

    # Create a Pyre property named density with a default value of 2500 kg/m**3.
    density = pyre.inventory.dimensional("density", default=2.5e+3*kg/m**3)
    density.meta['tip'] = "Density."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="uniformvelmodel"):
    """
    Constructor. This function is called automatically when the Python
    UniformVelModel object is created.
    """
    SpatialDBObj.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory. This function is called
    automatically when the component is setup.
    """
    SpatialDBObj._configure(self) # Call parent function.
    
    # Transfer inventory to C++ object
    ModuleUniformVelModel.vs(self, self.inventory.vs.value)
    ModuleUniformVelModel.vp(self, self.inventory.vp.value)
    ModuleUniformVelModel.density(self, self.inventory.density.value)
    return


  def _createModuleObj(self):
    """
    Create handle to C++ object. This function is called by the
    generic SpatialDBObj constructor. The name cannot be changed and
    no arguments can be added.
    """
    # Create the SWIG module object to provide access to the C++ object.
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
