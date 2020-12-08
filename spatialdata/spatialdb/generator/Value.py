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
# @file spatialdata/spatialdb/generator/Value.py
#
# @brief Python manager for generating value in database.
#
# Factory: database_value

import numpy

from pyre.components.Component import Component

from .Shaper import Shaper


# ----------------------------------------------------------------------------------------------------------------------
def shaperFactory(name):
    """
    Factory for shapers.
    """
    from pyre.inventory import facility
    return facility(name, family="shaper", factory=Shaper)


# ----------------------------------------------------------------------------------------------------------------------
class SingleShaper(Component):
    """
    Python container with one shaper.

    INVENTORY

    Properties
      - None

    Facilities
      - *shaper* Shaper for database value.
    """

    import pyre.inventory
    valueShaper = pyre.inventory.facility("shaper", family="shaper", factory=Shaper)
    valueShaper.meta['tip'] = "Shaper for database value."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="sigleshaper"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="shaper")


# ----------------------------------------------------------------------------------------------------------------------
class Value(Component):
    """
    Python manager for generating value in database.

    Factory: database_value

    INVENTORY

    Properties
      - *name* Name of value.
      - *units* Units for value.

    Facilities
      - *shapers* Shapers/filters used to construct spatial distribution.
    """

    import pyre.inventory

    vname = pyre.inventory.str("name", default="")
    vname.meta['tip'] = "Name of value."

    units = pyre.inventory.str("units", default="none")
    units.meta['tip'] = "Units associated with value."

    shapers = pyre.inventory.facilityArray("shapers", itemFactory=shaperFactory, factory=SingleShaper)
    shapers.meta['tip'] = "Shapers/filters used to construct spatial distribution."

    # PUBLIC METHODS /////////////////////////////////////////////////////

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
