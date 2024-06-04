#!/usr/bin/env python
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

# @brief Python object associated with the C++ UniformVelModel
# object. This objects provides a pythia.pyre interface to the C++ object.
##
# Factory: spatial_database

from spatialdata.spatialdb.SpatialDBObj import SpatialDBObj
from .spatialdbcontrib import UniformVelModel as ModuleUniformVelModel

# UniformVelModel class


class UniformVelModel(SpatialDBObj, ModuleUniformVelModel):
    """
    Python object associated with the C++ UniformVelModel object. This
    objects provides a pythia.pyre interface to the C++ object. It inherits
    from the generic SpatialDBObj and the UniformVelModel SWIG module
    object. This insures that this object has all of the SpatialDBObj
    pythia.pyre properties and facilities and functions and calls to the
    underlying C++ code are passed onto the SWIG Python module.

    Factory: spatial_database
    """

    # INVENTORY //////////////////////////////////////////////////////////

    class Inventory(SpatialDBObj.Inventory):
        """
        Python object for managing UniformVelModel pythia.pyre facilities and properties.

        ## \b Properties
        ## @li \b vs S wave speed.
        ## @li \b vp P wave speed.
        ## @li \b density Density.
        ##
        ## \b Facilities
        ## @li none
        """

        import pythia.pyre.inventory

        # Units used in properties
        from pythia.pyre.units.time import s
        from pythia.pyre.units.length import km, m
        from pythia.pyre.units.mass import kg

        # pythia.pyre properties have the form
        #
        # VARIABLE = pythia.pyre.inventory.TYPE("CFG_NAME", default=DEFAULT_VALUE)
        # VARIABLE.meta['tip'] = "HELP STRING"
        #
        # where VARIABLE is a variable used to refer to the pythia.pyre property,
        # TYPE of the type of property (dimensional, str, float, int,
        # etc), CFG_NAME is the name used in the pythia.pyre .cfg files and the
        # command line, and DEFAULT_VALUE is the default value.
        #
        # When a pythia.pyre property is a dimensional scalar quantity, use the
        # dimensional type for properties and pythia.pyre will automatically
        # check to make sure user-specified quantities have compatible
        # units and convert the value to SI units.
        #
        # The help string will be printed when the user uses the command
        # line arugments --FULL_COMPONENT_NAME.help-properties or
        # --FULL_COMPONENT.help-components. See the PyLith manual chapter
        # "Running PyLith" for more information regarding getting help
        # using command line arguments.
        #
        # Create a pythia.pyre property named vs with a default value of 2.6 km/s.
        vs = pythia.pyre.inventory.dimensional("vs", default=2.6 * km / s)
        vs.meta['tip'] = "S wave speed."

        # Create a pythia.pyre property named vp with a default value of 4.5 km/s.
        vp = pythia.pyre.inventory.dimensional("vp", default=4.5 * km / s)
        vp.meta['tip'] = "P wave speed."

        # Create a pythia.pyre property named density with a default value of 2500 kg/m**3.
        density = pythia.pyre.inventory.dimensional("density", default=2.5e+3 * kg / m**3)
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
        SpatialDBObj._configure(self)  # Call parent function.

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

# Factory used when setting UniformVelModel to a pythia.pyre 'spatial_database' facility.
def spatial_database():
    """
    Factory associated with UniformVelModel.
    """
    return UniformVelModel()


# End of file
