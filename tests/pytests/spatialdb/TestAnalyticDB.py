# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

import numpy
from pythia.pyre.units.length import m, km, cm


# ----------------------------------------------------------------------------------------------------------------------
class TestAnalyticDB(unittest.TestCase):

    def setUp(self):
        from spatialdata.spatialdb.AnalyticDB import AnalyticDB
        db = AnalyticDB()
        db.inventory.label = "test"
        db.inventory.values = ["one", "two", "three"]
        db.inventory.units = ["none", "km", "cm"]
        db.inventory.expressions = ["1.0+2.0*x", "y/z", "1.0+2.0*x+4.0*y"]
        db._configure()
        self._db = db

    def test_database(self):
        locs = numpy.array([[1.0, 2.0, 3.0], [5.6, 4.2, 8.6]], numpy.float64)
        from spatialdata.geocoords.CSCart import CSCart
        cs = CSCart()
        cs._configure()
        queryVals = ["three", "one"]
        dataE = numpy.array([[(1.0+2.0*x+4.0*y)*0.01, (1.0+2.0*x)*1.0] for x,y,z in locs])
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


# ----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestAnalyticDB))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
