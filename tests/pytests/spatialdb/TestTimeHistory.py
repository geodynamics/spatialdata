#!/usr/bin/env nemesis
#
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


# ----------------------------------------------------------------------------------------------------------------------
class TestTimeHistory(unittest.TestCase):

    def test_timehistory(self):
        timeQ = numpy.array([0.5, 0.0, 0.6, 2.0, 5.0, 20.0, 8.0], dtype=numpy.float64)
        amplitudeE = numpy.array([1.0, 0.0, 1.2, 4.0, 2.5, 0.0, 1.0], dtype=numpy.float64)
        errE = numpy.array([0, 0, 0, 0, 0, 1, 0], dtype=numpy.float64)

        from spatialdata.spatialdb.TimeHistory import TimeHistory
        th = TimeHistory()
        th.inventory.label = "test"
        th.inventory.filename = "data/timehistory.timedb"
        th._configure()

        th.open()
        nlocs = timeQ.shape[0]
        amplitude = numpy.zeros((nlocs,), dtype=numpy.float64)
        err = numpy.zeros((nlocs,), dtype=numpy.int32)

        for i in xrange(nlocs):
            (e, amplitude[i]) = th.query(timeQ[i])
            err[i] = e
        th.close()

        self.assertEqual(len(errE), len(err))
        for vE, v in zip(errE, err):
            self.assertEqual(vE, v)

        self.assertEqual(len(amplitudeE.shape), len(amplitude.shape))
        for dE, d in zip(amplitudeE.shape, amplitude.shape):
            self.assertEqual(dE, d)
        for vE, v in zip(numpy.reshape(amplitudeE, -1), numpy.reshape(amplitude, -1)):
            self.assertAlmostEqual(vE, v, 6)


# ----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestTimeHistory))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
