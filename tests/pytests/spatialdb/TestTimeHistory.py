#!/usr/bin/env nemesis
#
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

        for i in range(nlocs):
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


def load_tests(loader, tests, pattern):
    TEST_CLASSES = [TestTimeHistory]
    return make_suite(TEST_CLASSES, loader)


if __name__ == "__main__":
    unittest.main(verbosity=2)


# End of file
