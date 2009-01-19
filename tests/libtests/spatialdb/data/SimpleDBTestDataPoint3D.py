#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

## @file tests/libtests/spatialdb/data/SimpleDBDataPoint3D.py

## @brief Python data generator for tests of C++ SimpleDB using
## data with point 3-D spatial distribution.

import numpy

from SimpleDBApp import SimpleDBApp

# SimpleDBDataPoint3D class
class SimpleDBDataPoint3D(SimpleDBApp):
  """
  Python data generator for tests of C++ SimpleDB using
  data with point 3-D spatial distribution.
  """

  def _compute(self):
    """
    Compute query data.
    """
    # Database information
    self.numLocs = 1
    self.numVals = 2
    self.spaceDim = 3
    self.names = [ "One", "Two" ]
    self.units = [ "m", "m" ]
    self.dataDim = 0
    self.dbCoords = numpy.array( [0.1, 0.2, 0.3],
                               dtype=numpy.float64)
    self.dbData = numpy.array( [6.3, 7.4],
                               dtype=numpy.float64)

    # Query information
    self.numQueries = 3
    self.queryNearest = numpy.array( [[4.5, 2.3, 4.0, 6.3, 7.4],
                                      [3.2, 7.4, 5.8, 6.3, 7.4],
                                      [4.0, 9.8, 5.7, 6.3, 7.4]],
                                     dtype=numpy.float64)
    self.queryLinear = numpy.array( [[2.9, 3.4, 8.7, 6.3, 7.4],
                                     [2.2, 9.0, 8.5, 6.3, 7.4],
                                     [0.2, 5.8, 6.6, 6.3, 7.4]],
                                    dtype=numpy.float64)
    self.errFlags = numpy.array( [ 0, 0, 0 ], dtype=numpy.int32)
    return


  def __init__(self):
    """
    Constructor.
    """
    SimpleDBApp.__init__(self, name="simpledbdatapoint")
    return


# MAIN /////////////////////////////////////////////////////////////////
if __name__ == "__main__":

  app = SimpleDBDataPoint3D()
  app.run()


# End of file 
