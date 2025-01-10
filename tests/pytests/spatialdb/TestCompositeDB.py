# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

import numpy
from spatialdata.testing.TestCases import make_suite
from pythia.pyre.units.length import m


class TestCompositeDB(unittest.TestCase):

    def setUp(self):
        from spatialdata.spatialdb.UniformDB import UniformDB
        dbA = UniformDB()
        dbA.inventory.label = "db A"
        dbA.inventory.values = ["one", "two", "three"]
        dbA.inventory.data = [1.1 * m, 2.2 * m, 3.3 * m]
        dbA._configure()

        dbB = UniformDB()
        dbB.inventory.label = "db B"
        dbB.inventory.values = ["two", "three", "four", "five"]
        dbB.inventory.data = [2.1 * m, 3.1 * m, 4.1 * m, 5.1 * m]
        dbB._configure()

        from spatialdata.spatialdb.CompositeDB import CompositeDB
        db = CompositeDB()
        db.inventory.label = "composite db"
        db.inventory.dbA = dbA
        db.inventory.namesA = ["two", "one"]
        db.inventory.dbB = dbB
        db.inventory.namesB = ["three", "five"]
        db._configure()

        self._db = db

    def test_database(self):
        locs = numpy.array([[1.0, 2.0, 3.0],
                            [5.6, 4.2, 8.6]],
                           numpy.float64)
        from spatialdata.geocoords.CSCart import CSCart
        cs = CSCart()
        cs._configure()
        queryVals = ["three", "one", "five"]
        dataE = numpy.array([[3.1, 1.1, 5.1],
                             [3.1, 1.1, 5.1]], numpy.float64)
        errE = [0, 0]

        db = self._db
        db.open()
        db.setQueryValues(queryVals)
        data = numpy.zeros(dataE.shape, dtype=numpy.float64)
        err = []
        nlocs = locs.shape[0]
        for i in range(nlocs):
            e = db.query(data[i, :], locs[i, :], cs)
            err.append(e)
        db.close()

        self.assertEqual(len(errE), len(err))
        for vE, v in zip(errE, err):
            self.assertEqual(vE, v)

        self.assertEqual(len(dataE.shape), len(data.shape))
        for dE, d in zip(dataE.shape, data.shape):
            self.assertEqual(dE, d)
        for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
            self.assertAlmostEqual(vE, v, 6)


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestCompositeDB]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
