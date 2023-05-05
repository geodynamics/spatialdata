# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------

from pythia.pyre.components.Component import Component


class CoordSys(Component):
    """
    Python abstract base class for coordinate systems.
    """

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="coordsys"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="coordsys")
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Setup members using inventory.
        """
        Component._configure(self)
        self._createModuleObj()
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        raise NotImplementedError("_createModuleObj() not implemented.")
        return


# End of file
