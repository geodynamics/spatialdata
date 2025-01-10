# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================


from pythia.pyre.components.Component import Component
from .spatialdb import SpatialDB as ModuleSpatialDB


def validateDescription(value):
    """
    Validate description for spatial database.
    """
    if 0 == len(value):
        raise ValueError("Description for spatial database not specified.")
    return value


class SpatialDBObj(Component, ModuleSpatialDB):
    """
    Python abstract base class for spatial database.
    """

    import pythia.pyre.inventory

    description = pythia.pyre.inventory.str("description", default="", validator=validateDescription)
    description.meta['tip'] = "Description for database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="spatialdb"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="spatial_database")
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set attributes based on inventory.
        """
        Component._configure(self)
        self._createModuleObj()
        ModuleSpatialDB.setDescription(self, self.description)
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        raise NotImplementedError("_createModuleObj() not implemented.")


# End of file
