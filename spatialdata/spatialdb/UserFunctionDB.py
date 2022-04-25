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

from .SpatialDBObj import SpatialDBObj
from .spatialdb import UserFunctionDB as ModuleUserFunctionDB


class UserFunctionDB(SpatialDBObj, ModuleUserFunctionDB):
    """
    Analytical function spatial database.
    The analytical function must be provided in C++.
    This spatial database is intended for use in tests using the Method of Manufactured Solutions.

    Implements `SpatialDB`.
    """
    DOC_CONFIG = {
        "cfg": """
            [db]
            label = Linear function
            cs = spatialdata.geocoords.CSCart
            cs.space_dim = 2
            """,
    }

    import pythia.pyre.inventory

    from spatialdata.geocoords.CSCart import CSCart
    cs = pythia.pyre.inventory.facility("coordsys", factory=CSCart)
    cs.meta['tip'] = "Coordinate system."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="userfunctiondb"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)

        # This data member should be initialized in derived classes.
        #
        # self.functions = [(name, pointer_to_queryfn, units)]
        self.functions = []
        return

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        ModuleUserFunctionDB.setCoordSys(self, self.cs)
        for (name, fn, units,) in self.functions:
            ModuleUserFunctionDB.addValue(self, name, fn, units)
        return

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleUserFunctionDB.__init__(self)
        return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with UserFunctionDB.
    """
    return UserFunctionDB()


# End of file
