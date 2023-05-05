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

import numpy


class Shaper(Component):
    """
    Object for shaping spatial distribution of data while generating database.
    """
    DOC_CONFIG = {
        "cfg": """
            [gensimpledb.values.density]
            shapers = [bg, add]

            [gensimpledb.values.one.shapers.bg]
            default = 0.0
            db_value = density
            operand = add
            db = spatialdata.spatialdb.UniformDB
            db.value = [density]
            db.data = [2500*kg/m**3]

            [gensimpledb.values.one.shapers.add]
            default = 0.0
            db_value = density
            operand = add
            db = spatialdata.spatialdb.SimpleGridDB
            db.filename = density_perturbation.spatialdb
            """
    }

    import pythia.pyre.inventory

    defaultValue = pythia.pyre.inventory.float("default", default=0.0)
    defaultValue.meta['tip'] = "Default value for shaper."

    dbValue = pythia.pyre.inventory.str("db_value", default="")
    dbValue.meta['tip'] = "Name of value supplied in spatial database."

    operand = pythia.pyre.inventory.str("operand", default="multiply")
    operand.validator = pythia.pyre.inventory.choice(["add", "subtract", "multiply", "divide"])
    operand.meta['tip'] = "Operand to use in applying shaper."

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = pythia.pyre.inventory.facility("db", family="spatial_database", factory=SimpleDB)
    db.meta['tip'] = "Database containing value defining shaper."

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
        self.db.setQueryValues([self.dbValue])
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
