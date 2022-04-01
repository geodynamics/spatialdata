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
from .spatialdb import TimeHistory as ModuleTimeHistory


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Name of TimeHistoryDB file must be specified.")
    try:
        fin = open(value, "r")
    except IOError:
        raise IOError("Temporal database file '{}' not found.".format(value))
    return value


class TimeHistory(Component, ModuleTimeHistory):
    """
    Time history object for specifying temporal variation in a field.
    """
    DOC_CONFIG = {
        "cfg": """
            [timehistory]
            label = Time history for Dirichlet boundary condition
            filename = displacement.timedb
            """,
    }

    import pythia.pyre.inventory

    label = pythia.pyre.inventory.str("label", default="temporal database")
    label.meta['tip'] = "Label for time history."

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
        ModuleTimeHistory.setLabel(self, self.label)
        ModuleTimeHistory.setFilename(self, self.filename)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleTimeHistory.__init__(self)


# FACTORIES ////////////////////////////////////////////////////////////

def createWriter(filename, label="Time history writer"):
    writer = TimeHistory()
    writer.setLabel(label)
    writer.setFilename(filename)
    return writer


def temporal_database():
    """
    Factory associated with TimeHistory.
    """
    return TimeHistory()


# End of file
