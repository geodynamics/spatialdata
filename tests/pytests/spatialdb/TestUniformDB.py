# ======================================================================
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
# ======================================================================
#

import unittest

import numpy
from pyre.units.length import m, km, cm


# ----------------------------------------------------------------------------------------------------------------------
class TestUniformDB(unittest.TestCase):

    def setUp(self):
        from spatialdata.spatialdb.UniformDB import UniformDB
        db = UniformDB()
        db.inventory.label = "test"
        db.inventory.values = ["one", "two", "three"]
        db.inventory.data = [1.1, 2.2 * km, 3.3 * cm]
        db._configure()
        self._db = db

    def test_database(self):
        locs = numpy.array([[1.0, 2.0, 3.0], [5.6, 4.2, 8.6]], numpy.float64)
        from spatialdata.geocoords.CSCart import CSCart
        cs = CSCart()
        queryVals = ["three", "one"]
        dataE = numpy.array([[3.3e-2, 1.1], [3.3e-2, 1.1]], numpy.float64)
        errE = [0, 0]

        db = self._db
        db.open()
        db.setQueryValues(queryVals)
        data = numpy.zeros(dataE.shape, dtype=numpy.float64)
        err = []
        nlocs = locs.shape[0]
        for i in xrange(nlocs):
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


# ----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestUniformDB))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
