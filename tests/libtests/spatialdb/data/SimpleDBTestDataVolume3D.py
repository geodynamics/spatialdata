#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

## @file tests/libtests/data/SimpleDBDataVolume3D.odb

## @brief Python data generator for tests of C++ SimpleDB using
## data with volumetric 3-D spatial distribution.

import numpy

from SimpleDBApp import SimpleDBApp

# SimpleDBDataVolume3D class
class SimpleDBDataVolume3D(SimpleDBApp):
  """
  Python data generator for tests of C++ SimpleDB using
  data with volumetric 3-D spatial distribution.
  """

  def _compute(self):
    """
    Compute query data.
    """
    # Database information
    self.numLocs = 8
    self.numVals = 2
    self.spaceDim = 3
    self.names = [ "One", "Two" ]
    self.units = [ "m", "m" ]
    self.dataDim = 3
    self.dbCoords = None
    self.dbData = None

    # Query information
    self.numQueries = 5
    self.queryNearest = None
    self.queryLinear = None
    self.errFlags = numpy.array( [ 0, 0, 1, 0, 0  ], dtype=numpy.int32)

    tdata = [ {'r': 1.0, 's':-1.0, 't':-1.0, 'one': 0.1, 'two': 1.1},
              {'r':-1.0, 's':-1.0, 't':-1.0, 'one': 0.3, 'two': 3.3},
              {'r': 1.0, 's': 1.0, 't':-1.0, 'one': 0.2, 'two': 2.2},
              {'r':-1.0, 's': 1.0, 't':-1.0, 'one': 0.1, 'two': 1.1},
              {'r': 1.0, 's':-1.0, 't': 1.0, 'one': 0.4, 'two': 4.6},
              {'r':-1.0, 's':-1.0, 't': 1.0, 'one': 0.3, 'two': 3.2},
              {'r': 1.0, 's': 1.0, 't': 1.0, 'one': 0.7, 'two': 5.2},
              {'r':-1.0, 's': 1.0, 't': 1.0, 'one': 0.5, 'two': 4.6}]
    qtdata = [ {'r': 0.9, 's':-0.8, 't':-0.9, 'ni': 0,
                'wts': [{'i': 0, 'w': 0.80},
                        {'i': 2, 'w': 0.10},
                        {'i': 4, 'w': 0.05},
                        {'i': 1, 'w': 0.05}] },
               {'r': -0.8, 's': 0.1, 't': 0.9, 'ni': 7,
                'wts': [{'i': 7, 'w': 0.40},
                        {'i': 5, 'w': 0.45},
                        {'i': 6, 'w': 0.10},
                        {'i': 3, 'w': 0.05}] },
               {'r': 0.9, 's': 0.8, 't': 1.2, 'ni': 6,
                'wts': [{'i': 6, 'w': 0.0},
                        {'i': 4, 'w': 0.0},
                        {'i': 7, 'w': 0.0},
                        {'i': 2, 'w': 0.0}] },
               {'r': 0.6, 's': 0.8, 't': 0.6, 'ni': 6,
                'wts': [{'i': 6, 'w': 0.50},
                        {'i': 2, 'w': 0.20},
                        {'i': 7, 'w': 0.20},
                        {'i': 4, 'w': 0.10}] },
               {'r':-0.3, 's':-0.7, 't':-0.1, 'ni': 1,
                'wts': [{'i': 1, 'w': 0.05},
                        {'i': 5, 'w': 0.45},
                        {'i': 0, 'w': 0.35},
                        {'i': 3, 'w': 0.15}]} ]

    o = numpy.array([3.4, 9.5, 8.7], dtype=numpy.float64)
    sqrt5 = 5**0.5
    sqrt21 = 21**0.5    
    sqrt105 = 105**0.5
    a = numpy.array([2.0/sqrt5, 0, 1.0/sqrt5], dtype=numpy.float64)
    b = numpy.array([1.0/sqrt21, 4.0/sqrt21, -2.0/sqrt21], dtype=numpy.float64)
    c = numpy.array([-4.0/sqrt105, 5.0/sqrt105, 8.0/sqrt105],
                    dtype=numpy.float64)
    self.dbCoords = numpy.zeros( (self.numLocs, self.spaceDim),
                               dtype=numpy.float64)
    self.dbData = numpy.zeros( (self.numLocs, self.numVals),
                               dtype=numpy.float64)
    iLoc = 0
    for loc in tdata:
      xyz = o + a*loc['r'] + b*loc['s'] + c*loc['t']
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
      xyz = o + a*qloc['r'] + b*qloc['s'] + c*qloc['t']
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
    SimpleDBApp.__init__(self, name="simpledbdatavolume3D")
    return


# MAIN /////////////////////////////////////////////////////////////////
if __name__ == "__main__":

  app = SimpleDBDataVolume3D()
  app.run()


# End of file 
