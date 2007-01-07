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

## @file tests/libtests/data/SimpleDBDataLine3D.odb

## @brief Python data generator for tests of C++ SimpleDB using
## data with linear 3-D spatial distribution.

import numpy

from SimpleDBApp import SimpleDBApp

# SimpleDBDataLine3D class
class SimpleDBDataLine3D(SimpleDBApp):
  """
  Python data generator for tests of C++ SimpleDB using
  data with linear 3-D spatial distribution.
  """

  def _compute(self):
    """
    Compute query data.
    """
    # Database information
    self.numLocs = 5
    self.numVals = 2
    self.spaceDim = 3
    self.names = [ "One", "Two" ]
    self.units = [ "m", "m" ]
    self.dataDim = 1
    self.dbData = None

    # Query information
    self.numQueries = 4

    self.queryNearest = numpy.array( [[4.5, 2.3, 4.0, 6.3, 7.4],
                                      [3.2, 7.4, 5.8, 6.3, 7.4],
                                      [4.0, 9.8, 5.7, 6.3, 7.4]],
                                     dtype=numpy.float64)
    self.queryLinear = numpy.array( [[2.9, 3.4, 8.7, 6.3, 7.4],
                                     [2.2, 9.0, 8.5, 6.3, 7.4],
                                     [0.2, 5.8, 6.6, 6.3, 7.4]],
                                    dtype=numpy.float64)
    self.errFlags = numpy.array( [ 0, 0, 1, 0  ], dtype=numpy.int32)

    tdata = [ {'t': 0.0, 'one': 0.1, 'two': 1.1},
                    {'t': 1.0, 'one': 0.3, 'two': 3.3},
                    {'t': 1.5, 'one': 0.2, 'two': 2.2},
                    {'t': 2.0, 'one': 0.1, 'two': 1.1},
                    {'t': 5.0, 'one': -0.4, 'two': -4.4} ]
    qtdata = [ {'t': 1.0, 'ni': 1, 'wts': [{'i': 1, 'w': 1.0}] },
               {'t': 4.0, 'ni': 4, 'wts': [{'i': 3, 'w': 1.0/3.0},
                                           {'i': 4, 'w': 2.0/3.0} ] },
               {'t': 6.0, 'ni': 4, 'wts': [{'i': 3, 'w': 0.0},
                                           {'i': 4, 'w': 0.0} ] },
               {'t': 1.2, 'ni': 1, 'wts': [{'i': 1, 'w': 0.6},
                                           {'i': 2, 'w': 0.4}]} ]

    o = numpy.array([3.4, 9.5, 8.7], dtype=numpy.float64)
    a = numpy.array([2.3, 0.4, 9.8], dtype=numpy.float64)
    self.dbData = numpy.zeros( (self.numLocs, self.spaceDim+self.numVals),
                               dtype=numpy.float64)
    iLoc = 0
    for loc in tdata:
      xyz = o + a*loc['t']
      self.dbData[iLoc, :] = numpy.array([xyz[0], xyz[1], xyz[2],
                                          loc['one'], loc['two']],
                                         dtype=numpy.float64)
      iLoc += 1
    
    self.queryNearest = numpy.zeros( (self.numQueries,
                                      self.spaceDim+self.numVals),
                                     dtype=numpy.float64)
    self.queryLinear = numpy.zeros( (self.numQueries,
                                     self.spaceDim+self.numVals),
                                    dtype=numpy.float64)
    iLoc = 0
    for qloc in qtdata:
      xyz = o + a*qloc['t']
      v1 = 0
      v2 = 0
      for wt in qloc['wts']:
        v1 += tdata[wt['i']]['one']*wt['w']
        v2 += tdata[wt['i']]['two']*wt['w']
      self.queryLinear[iLoc,:] = numpy.array([xyz[0], xyz[1], xyz[2], v1, v2],
                                             dtype=numpy.float64)
      v1 = tdata[qloc['ni']]['one']
      v2 = tdata[qloc['ni']]['two']
      self.queryNearest[iLoc,:] = numpy.array([xyz[0], xyz[1], xyz[2], v1, v2],
                                              dtype=numpy.float64)
      iLoc += 1
    return


  def __init__(self):
    """
    Constructor.
    """
    SimpleDBApp.__init__(self, name="simpledbdataline3D")
    return


# MAIN /////////////////////////////////////////////////////////////////
if __name__ == "__main__":

  app = SimpleDBDataLine3D()
  app.run()


# End of file 
