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

import numpy

from pythia.pyre.components.Component import Component

from .Shaper import Shaper


def shaperFactory(name):
    """
    Factory for shapers.
    """
    from pythia.pyre.inventory import facility
    return facility(name, family="shaper", factory=Shaper)


class SingleShaper(Component):
    """
    Container with one shaper.
    """

    import pythia.pyre.inventory
    valueShaper = pythia.pyre.inventory.facility("shaper", family="shaper", factory=Shaper)
    valueShaper.meta['tip'] = "Shaper for database value."

    def __init__(self, name="sigleshaper"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="shaper")


class Value(Component):
    """
    Value generated in spatial database.
    """
    DOC_CONFIG = {
      "cfg": """
        [gensimpledb]
        values = [vp, vs]

        [gensimpledb.values.vp]
        name = Vp
        units = m/s
        shapers = [bg, perturbation]
        """
    }

    import pythia.pyre.inventory

    vname = pythia.pyre.inventory.str("name", default="")
    vname.meta['tip'] = "Name of value."

    units = pythia.pyre.inventory.str("units", default="none")
    units.meta['tip'] = "Units associated with value."

    shapers = pythia.pyre.inventory.facilityArray("shapers", itemFactory=shaperFactory, factory=SingleShaper)
    shapers.meta['tip'] = "Shapers/filters used to construct spatial distribution."

    def __init__(self, name="value"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="database_value")

    def calculate(self, locs, cs):
        """
        Calculate spatial distribution for value using shapers.
        """
        (numLocs, spaceDim) = locs.shape
        value = numpy.zeros((numLocs,), dtype=numpy.float64)
        for shaper in self.shapers.components():
            shaper.initialize(locs, cs)
            shaper.apply(value)
            shaper.finalize()
        return value


# FACTORIES ////////////////////////////////////////////////////////////
def database_value():
    """
    Factory associated with Value.
    """
    return Value()


# End of file
