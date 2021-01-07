# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

# @file spatialdata/spatialdb/SpatialDBObj.py
#
# @brief Python abstract base class for spatial database.
#
# Factory: spatial_database

from pyre.components.Component import Component
from .spatialdb import SpatialDB as ModuleSpatialDB


def validateLabel(value):
    """
    Validate label for spatial database.
    """
    if 0 == len(value):
        raise ValueError("Descriptive label for spatial database not specified.")
    return value


class SpatialDBObj(Component, ModuleSpatialDB):
    """
    Python abstract base class for spatial database.

    Factory: spatial_database

    INVENTORY

    Properties
      - *label* Descriptive label for spatial database.

    Facilities
      - None
    """

    import pyre.inventory

    label = pyre.inventory.str("label", default="", validator=validateLabel)
    label.meta['tip'] = "Descriptive label for database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="spatialdb"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="spatial_database")
        self._createModuleObj()
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set attributes based on inventory.
        """
        Component._configure(self)
        ModuleSpatialDB.setLabel(self, self.label)
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        raise NotImplementedError("_createModuleObj() not implemented.")


# End of file
