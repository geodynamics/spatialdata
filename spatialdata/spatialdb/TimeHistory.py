# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import pathlib

from pythia.pyre.components.Component import Component
from .spatialdb import TimeHistory as ModuleTimeHistory


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Name of TimeHistoryDB file must be specified.")
    if not pathlib.Path(value).is_file():
        raise IOError(f"Temporal database file '{value}' not found.")
    return value


class TimeHistory(Component, ModuleTimeHistory):
    """
    Time history object for specifying temporal variation in a field.
    """
    DOC_CONFIG = {
        "cfg": """
            [timehistory]
            description = Time history for Dirichlet boundary condition
            filename = displacement.timedb
            """,
    }

    import pythia.pyre.inventory

    description = pythia.pyre.inventory.str("description", default="temporal database")
    description.meta['tip'] = "Description for time history."

    filename = pythia.pyre.inventory.str("filename", default="timehistory.timedb", validator=validateFilename)
    filename.meta['tip'] = "Name of file for time history."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="timehistory"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="temporal_database")

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set attributes based on inventory.
        """
        Component._configure(self)
        self._createModuleObj()
        ModuleTimeHistory.setDescription(self, self.description)
        ModuleTimeHistory.setFilename(self, self.filename)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleTimeHistory.__init__(self)


# FACTORIES ////////////////////////////////////////////////////////////

def createWriter(filename, description="Time history writer"):
    writer = TimeHistory()
    writer.setDescription(description)
    writer.setFilename(filename)
    return writer


def temporal_database():
    """
    Factory associated with TimeHistory.
    """
    return TimeHistory()


# End of file
