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
from spatialdata.geocoords.CSCart import CSCart


class TestSimpleIOAscii(unittest.TestCase):

    def test_write(self):
        """
        Test write().
        """
        # Database info
        cs = CSCart()
        cs._configure()

        filename = "data/test.spatialdb"
        data = {'points': numpy.array([[1.0, 2.0, 3.0],
                                       [0.5, 3.0, -3.0]], numpy.float64),
                'coordsys': cs,
                'data_dim': 1,
                'values': [{'name': "One",
                            'units': "m",
                            'data': numpy.array([2.0, 8.0], numpy.float64)},
                           {'name': "Two",
                            'units': "m",
                            'data': numpy.array([-2.0, 3.0], numpy.float64)}]}
        dataDim = 1

        qlocs = numpy.array([[0.875, 2.25, 1.5],
                             [0.6, 2.8, -1.8],
                             [1.0, 2.0, 3.0]],
                            numpy.float64)
        valsE = numpy.array([[-0.75, 3.5],
                             [2.0, 6.8],
                             [-2.0, 2.0]], numpy.float64)
        errE = [0, 0, 0]

        # Write database
        from spatialdata.spatialdb.SimpleIOAscii import createWriter
        writer = createWriter(filename)
        writer.write(data)

        # Test write using query
        from spatialdata.spatialdb.SimpleDB import SimpleDB
        db = SimpleDB()
        db.inventory.label = "test"
        db.inventory.queryType = "linear"
        db.inventory.iohandler.inventory.filename = filename
        db.inventory.iohandler._configure()
        db._configure()

        db.open()
        db.setQueryValues(["two", "one"])
        vals = numpy.zeros(valsE.shape, dtype=numpy.float64)
        err = []
        nlocs = qlocs.shape[0]
        for i in range(nlocs):
            e = db.query(vals[i, :], qlocs[i, :], cs)
            err.append(e)
        db.close()

        self.assertEqual(len(valsE.shape), len(vals.shape))
        for dE, d in zip(valsE.shape, vals.shape):
            self.assertEqual(dE, d)
        for vE, v in zip(numpy.reshape(valsE, -1), numpy.reshape(vals, -1)):
            self.assertAlmostEqual(vE, v, 6)


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestSimpleIOAscii]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
