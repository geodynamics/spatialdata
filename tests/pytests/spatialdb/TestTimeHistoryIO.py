#!/usr/bin/env nemesis
#
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


# ----------------------------------------------------------------------------------------------------------------------
class TestTimeHistoryIO(unittest.TestCase):

    def test_write(self):
        """
        Test write().
        """
        filename = "data/test.timedb"
        time = numpy.array([0.0, 2.0, 6.0, 7.0, 10.0], dtype=numpy.float64)
        amplitude = numpy.array([0.0, 0.2, 0.1, -0.1, 2.0], dtype=numpy.float64)
        units = "year"

        # Write database
        from spatialdata.spatialdb.TimeHistoryIO import write
        write(time, amplitude, units, filename)

        # Test write
        filenameE = "data/test_okay.timedb"

        fin = open(filenameE, "r")
        linesE = fin.readlines()
        fin.close()

        fin = open(filename, "r")
        lines = fin.readlines()
        fin.close()

        self.assertEqual(len(linesE), len(lines))
        iline = 0
        for (lineE, line) in zip(linesE, lines):
            if lineE != line:
                print("Error found in line %d in file '%s' is incorrect." % (iline, filename))
                self.assertTrue(False)
            iline += 1


# ----------------------------------------------------------------------------------------------------------------------
if __name__ == '__main__':
    suite = unittest.TestSuite()
    suite.addTest(unittest.makeSuite(TestSimpleDB))
    unittest.TextTestRunner(verbosity=2).run(suite)


# End of file
