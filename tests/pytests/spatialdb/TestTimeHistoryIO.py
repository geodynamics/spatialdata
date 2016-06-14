#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2016 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

import numpy

class TestTimeHistoryIO(unittest.TestCase):

  def test_write(self):
    """
    Test write().
    """
    filename = "data/test.timedb"
    time = numpy.array( [0.0, 2.0, 6.0, 7.0, 10.0], dtype=numpy.float64)
    amplitude = numpy.array( [0.0, 0.2, 0.1, -0.1, 2.0], dtype=numpy.float64)
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
        print "Error found in line %d in file '%s' is incorrect." % (iline, filename)
        self.failIf(True)
      iline += 1

    return


# End of file 
