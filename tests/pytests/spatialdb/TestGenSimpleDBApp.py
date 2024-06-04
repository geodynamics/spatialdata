# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

import numpy
from spatialdata.testing.TestCases import make_suite


class TestGenSimpleDBApp(unittest.TestCase):

    def test(self):
        """
        Test GenSimpleDBApp with 1-D data in 2-D space.
        """
        from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp
        from spatialdata.geocoords.CSCart import CSCart
        from spatialdata.spatialdb.SimpleDB import SimpleDB

        app = GenSimpleDBApp()
        app.run()

        # Test write using query
        db = SimpleDB()
        db.inventory.iohandler.inventory.filename = "data/gen1Din2D.spatialdb"
        db.inventory.iohandler._configure()
        db.inventory.label = "test"
        db.inventory.queryType = "nearest"
        db._configure()

        qlocs = numpy.array([[-2.0,  2.0], [3.0, -4.0], [0.0,  0.7]], numpy.float64)

        dataE = numpy.array([[-0.15, 3.45], [2.4, 6.4], [-0.6, 3.45]], numpy.float64)
        errE = [0, 0, 0]

        from spatialdata.geocoords.CSCart import CSCart
        cs = CSCart()
        cs.inventory.spaceDim = 2
        cs._configure()

        db.open()
        db.setQueryValues(["two", "one"])
        data = numpy.zeros(dataE.shape, dtype=numpy.float64)
        err = []
        nlocs = qlocs.shape[0]
        for i in range(nlocs):
            e = db.query(data[i, :], qlocs[i, :], cs)
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
    TEST_CLASSES = [TestGenSimpleDBApp]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
