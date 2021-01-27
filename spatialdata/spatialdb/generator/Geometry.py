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

# @file spatialdata/spatialdb/generator/Geometry.py
#
# @brief Python manager for geometry used in generating database.
#
# Factory: geometry.

from pythia.pyre.components.Component import Component


class Dummy(Component):
    def __init__(self):
        Component.__init__(self, name="dummy", facility="dummy")
        return


class Geometry(Component):
    """
    Python manager for geometry used in generating database.

    Factory: geometry.

    INVENTORY

    Properties
      - *data_dim* Spatial dimension of database region.

    Facilities
      - *reader* Geometry reader.
      - *coordsys* Coordinate system associated with geometry.
    """

    import pythia.pyre.inventory

    dataDim = pythia.pyre.inventory.int("data_dim", default=2)
    dataDim.validator = pythia.pyre.inventory.choice([0, 1, 2, 3])
    dataDim.meta['tip'] = "Spatial dimension of database locations."

    reader = pythia.pyre.inventory.facility("reader", family="reader", factory=Dummy)
    reader.meta['tip'] = "Object to read geometry."

    from spatialdata.geocoords.CSCart import CSCart
    coordsys = pythia.pyre.inventory.facility("coordsys", family="coordsys", factory=CSCart)
    coordsys.meta['tip'] = "Coordinate system for database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="geometry"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="geometry")
        self.vertices = None

    def read(self):
        """
        Read geometry.
        """
        self.vertices = self.reader.read()


# FACTORIES ////////////////////////////////////////////////////////////
def geometry():
    """
    Factory associated with Geometry.
    """
    return Geometry()


# End of file
