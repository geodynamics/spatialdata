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

# @file spatialdata/spatialdb/CompositeDB.py
#
# @brief Python manager for spatial database with uniform values.
#
# Factory: spatial_database

from .SpatialDBObj import SpatialDBObj
from .spatialdb import CompositeDB as ModuleCompositeDB


class CompositeDB(SpatialDBObj, ModuleCompositeDB):
    """
    Python manager for spatial database with uniform values.

    Factory: spatial_database

    INVENTORY

    Properties
      - *values_A* Names of values to query with database A.
      - *values_B* Names of values to query with databsae B.

    Facilities
      - *db_A* Spatial database A.
      - *db_B* Spatial database B.
    """

    import pythia.pyre.inventory

    namesA = pythia.pyre.inventory.list("values_A", default=[])
    namesA.meta['tip'] = "Names of values to query with database A."

    namesB = pythia.pyre.inventory.list("values_B", default=[])
    namesB.meta['tip'] = "Names of values to query with database B."

    from .UniformDB import UniformDB
    dbA = pythia.pyre.inventory.facility("db_A", factory=UniformDB, family="spatial_database")
    dbA.meta['tip'] = "Spatial database A."

    dbB = pythia.pyre.inventory.facility("db_B", factory=UniformDB, family="spatial_database")
    dbB.meta['tip'] = "Spatial database B."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="compositedb"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        self._validateParameters(self.inventory)
        ModuleCompositeDB.setDBA(self, self.dbA, self.namesA)
        ModuleCompositeDB.setDBB(self, self.dbB, self.namesB)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleCompositeDB.__init__(self)
        return

    def _validateParameters(self, data):
        """
        Validate parameters.
        """
        if (0 == len(data.namesA)):
            raise ValueError("Error in spatial database '%s'\n"
                             "Names of values to query in database A not set." % self.label)
        if (0 == len(data.namesB)):
            raise ValueError("Error in spatial database '%s'\n"
                             "Names of values to query in database B not set." % self.label)
        return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with CompositeDB.
    """
    return CompositeDB()


# End of file
