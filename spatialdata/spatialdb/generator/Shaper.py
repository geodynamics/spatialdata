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

# @file spatialdata/spatialdb/generator/Shaper.py
#
# @brief Python manager for shaping spatial distribution of data
# while generating database.
#
# Factory: shaper

from pyre.components.Component import Component

import numpy


class Shaper(Component):
    """
    Python manager for shaping spatial distribution of data while
    generating database.

    Factory: shaper

    INVENTORY

    Properties
      - *db_value* Name of value in spatial database.
      - *operand* Operand to use in adjusting spatial distribution of value.

    Facilities
      - *db* Database containing value for adjustment (shaping).
    """

    import pyre.inventory

    defaultValue = pyre.inventory.float("default", default=0.0)
    defaultValue.meta['tip'] = "Default value for shaper."

    dbValue = pyre.inventory.str("db_value", default="")
    dbValue.meta['tip'] = "Name of value supplied in spatial database."

    operand = pyre.inventory.str("operand", default="multiply")
    operand.validator = pyre.inventory.choice(["add", "subtract", "multiply", "divide"])
    operand.meta['tip'] = "Operand to use in applying shaper."

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = pyre.inventory.facility("db", family="spatial_database", factory=SimpleDB)
    db.meta['tip'] = "Database containing value defining shaper."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="shaper"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="shaper")

    def initialize(self, locs, cs):
        """
        Initialize shaper.
        """
        if self.dbValue == "":
            raise ValueError("Name of value in spatial database must be set for shaper '%s'." % self.name)
        self.db.open()

        nlocs = locs.shape[0]
        self.db.queryVals([self.dbValue])
        v = numpy.zeros((1,), dtype=numpy.float64)
        vals = numpy.zeros((nlocs, 1), dtype=numpy.float64)
        err = numpy.ones((nlocs,), dtype=numpy.int32)
        self.db.multiquery(vals, err, locs, cs)
        vals = numpy.reshape(numpy.array(vals), -1)
        default = self.defaultValue * numpy.ones(vals.shape, dtype=numpy.float64)
        mask = numpy.zeros(vals.shape, dtype=numpy.float64)
        mask[err[:] != 0] = 1.0
        vals[:] += default[:] * mask[:]

        self.db.close()

        self.values = vals

    def finalize(self):
        """
        Deallocate values.
        """
        del self.values

    def apply(self, value):
        """
        Shape value.
        """
        if self.operand == "add":
            value[:] += self.values[:]
        elif self.operand == "subtract":
            value[:] -= self.values[:]
        elif self.operand == "multiply":
            value[:] *= self.values[:]
        elif self.operand == "divide":
            value[:] /= self.values[:]
        else:
            raise ValueError("Unknown operand setting '%s'." % self.operand)


# FACTORIES ////////////////////////////////////////////////////////////

def shaper():
    """
    Factory associated with Shaper.
    """
    return Shaper()


# End of file
