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

# @file spatialdata/spatialdb/UserFunctionDB.py
#
# @brief Python manager for user function spatial database.
#
# @WARNING This object is incomplete.
#
# Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import UserFunctionDB as ModuleUserFunctionDB


class UserFunctionDB(SpatialDBObj, ModuleUserFunctionDB):
    """
    Python manager for simple spatial database.

    Factory: spatial_database

    INVENTORY

    Properties
      - None

    Facilities
      - *coordsys* Coordinate system.
    """

    import pyre.inventory

    from spatialdata.geocoords.CSCart import CSCart
    cs = pyre.inventory.facility("coordsys", factory=CSCart)
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
        ModuleUserFunctionDB.coordsys(self, self.inventory.cs)
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
