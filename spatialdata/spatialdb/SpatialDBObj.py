# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------


from pythia.pyre.components.Component import Component
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
    """

    import pythia.pyre.inventory

    label = pythia.pyre.inventory.str("label", default="", validator=validateLabel)
    label.meta['tip'] = "Descriptive label for database."

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
        ModuleSpatialDB.setLabel(self, self.label)
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        raise NotImplementedError("_createModuleObj() not implemented.")


# End of file
