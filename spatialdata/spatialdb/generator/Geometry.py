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

from pythia.pyre.components.Component import Component


class Dummy(Component):
    def __init__(self):
        Component.__init__(self, name="dummy", facility="dummy")
        return


class Geometry(Component):
    """
    Geometry used in generating database.
    """
    DOC_CONFIG = {
      "cfg": """
          [gensimplebd.geometry]
          data_dim = 2
          reader = read_geometry
          coordsys = spatialdata.geocoords.CSCart
          """
    }

    import pythia.pyre.inventory

    dataDim = pythia.pyre.inventory.int("data_dim", default=2)
    dataDim.validator = pythia.pyre.inventory.choice([0, 1, 2, 3])
    dataDim.meta['tip'] = "Spatial dimension of database locations."

    reader = pythia.pyre.inventory.facility("reader", family="reader", factory=Dummy)
    reader.meta['tip'] = "Object to read geometry."

    from spatialdata.geocoords.CSCart import CSCart
    coordsys = pythia.pyre.inventory.facility("coordsys", family="coordsys", factory=CSCart)
    coordsys.meta['tip'] = "Coordinate system for database."

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
