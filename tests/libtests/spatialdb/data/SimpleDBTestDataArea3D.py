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

## @file tests/libtests/data/SimpleDBDataArea3D.odb

## @brief Python data generator for tests of C++ SimpleDB using
## data with areal 3-D spatial distribution.

import numpy

from SimpleDBApp import SimpleDBApp

# SimpleDBDataArea3D class
class SimpleDBDataArea3D(SimpleDBApp):
  """
  Python data generator for tests of C++ SimpleDB using
  data with areal 3-D spatial distribution.
  """

  def _compute(self):
    """
    Compute query data.
    """
    # Database information
    self.numLocs = 6
    self.numVals = 2
    self.spaceDim = 3
    self.names = [ "One", "Two" ]
    self.units = [ "m", "m" ]
    self.dataDim = 2
    self.dbData = None

    # Query information
    self.numQueries = 4
    self.queryNearest = None
    self.queryLinear = None
    self.errFlags = numpy.array( [ 0, 0, 1, 0  ], dtype=numpy.int32)

    tdata = [ {'s': 0.0, 't': 0.0, 'one': 0.1, 'two': 1.1},
              {'s': 1.0, 't': 0.0, 'one': 0.3, 'two': 3.3},
              {'s': 4.0, 't': 0.0, 'one': 0.2, 'two': 2.2},
              {'s': 4.0, 't': 3.0, 'one': 0.1, 'two': 1.1},
              {'s': 0.0, 't': 2.0, 'one': -0.4, 'two': -4.4},
              {'s': 0.0, 't': 3.0, 'one': -0.3, 'two': -3.2} ]
    qtdata = [ {'s': 3.0, 't': 1.0, 'ni': 2,
                'wts': [{'i': 1, 'w': 1.0/3.0},
                        {'i': 2, 'w': 1.0/3.0},
                        {'i': 3, 'w': 1.0/3.0}] },
               {'s': 0.25, 't': 0.75, 'ni': 0,
                'wts': [{'i': 0, 'w': 0.375},
                        {'i': 1, 'w': 0.250},
                        {'i': 4, 'w': 0.375}] },
               {'s': 3.0, 't': 4.0, 'ni': 3,
                'wts': [{'i': 3, 'w': 0.0},
                        {'i': 5, 'w': 0.0},
                        {'i': 4, 'w': 0.0}] },
               {'s': 1.0, 't': 2.75, 'ni': 5,
                'wts': [{'i': 5, 'w': 0.50},
                        {'i': 4, 'w': 0.25},
                        {'i': 3, 'w': 0.25}]} ]

    o = numpy.array([3.4, 9.5, 8.7], dtype=numpy.float64)
    sqrt5 = 5**0.5
    sqrt21 = 21**0.5    
    a = numpy.array([2.0/sqrt5, 0, 1.0/sqrt5], dtype=numpy.float64)
    b = numpy.array([1.0/sqrt21, 4/sqrt21, -2/sqrt21], dtype=numpy.float64)
    self.dbCoords = numpy.zeros( (self.numLocs, self.spaceDim),
                               dtype=numpy.float64)
    self.dbData = numpy.zeros( (self.numLocs, self.numVals),
                               dtype=numpy.float64)
    iLoc = 0
    for loc in tdata:
      xyz = o + a*loc['s'] + b*loc['t']
      self.dbCoords[iLoc, :] = numpy.array([xyz[0], xyz[1], xyz[2]],
                                         dtype=numpy.float64)
      self.dbData[iLoc, :] = numpy.array([loc['one'], loc['two']],
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
      xyz = o + a*qloc['s'] + b*qloc['t']
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
    SimpleDBApp.__init__(self, name="simpledbdataarea3D")
    return


# MAIN /////////////////////////////////////////////////////////////////
if __name__ == "__main__":

  app = SimpleDBDataArea3D()
  app.run()


# End of file 
