#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file tests/libtests/spatialdb/data/SimpleDBQueryData3D.py

## @brief Python application for generating C++ data files for testing
## C++ SimpleDBQuery objects.

import numpy
from numpy.linalg import det

from SimpleDBQueryApp import SimpleDBQueryApp

# SimpleDBQueryData3D class
class SimpleDBQueryData3D(SimpleDBQueryApp):
  """
  Python application for generating C++ data files for testing C++
  SimpleDBQuery objects.
  """
  
  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpledbquerydata3d"):
    """
    Constructor.
    """
    SimpleDBQueryApp.__init__(self, name)

    # Database information
    self.numLocs = 5
    self.spaceDim = 3
    self.numVals = 2
    self.dataDim = 3
    self.dbCoords = numpy.array([ [0.0, 0.0, 0.0],
                                  [1.0, 0.1, 0.3],
                                  [2.0, 0.2, 0.2],
                                  [3.0, 0.3, 0.1],
                                  [4.0, 0.4, 0.9] ],
                             dtype=numpy.float64)
    self.dbData = numpy.array([ [1.1, 5.5],
                                [2.2, 6.6],
                                [3.3, 7.7],
                                [4.4, 8.8],
                                [4.5, 9.9] ],
                             dtype=numpy.float64)
    self.names = [ "One", "Two" ]
    self.units = [ "m", "m" ]

    # Query information
    self.numPts = None
    self.coords = None
    self.dist2 = None
    self.area = None
    self.areaDir = None
    self.volume = None

    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _compute(self):
    """
    Compute query data.
    """
    self._transformCoords()
    self._calcDist2()
    self._calcArea()
    self._calcAreaDir()
    self._calcVolume()
    return


  def _transformCoords(self):
    """Transform coordinates."""
    pqr = numpy.array([ [0.1, 0.0, 0.0],
                         [0.4, 0.0, 0.0],
                         [0.3, 0.6, 0.0],
                         [0.3, 0.4, 0.5] ],
                       dtype=numpy.float64)
    self.numPts = pqr.shape[0]
    o = numpy.array([2.0, 4.2, 3.1], dtype=numpy.float64)
    a = numpy.array([9.5, 2.8, 3.4], dtype=numpy.float64)
    b = numpy.array([5.2, 9.3, 4.8], dtype=numpy.float64)
    c = numpy.array([2.9, 8.5, 6.6], dtype=numpy.float64)
    self.coords = numpy.zeros( (pqr.shape), dtype=numpy.float64)
    iPt = 0
    for xyz in pqr:
      self.coords[iPt,:] = o + a*xyz[0] + b*xyz[1] + c*xyz[2]
      iPt += 1
    return

  
  def _calcDist2(self):
    a = self.coords[0]
    b = self.coords[1]
    J = numpy.array( ( [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2] ] ),
                     dtype=numpy.float64)
    self.dist2 = numpy.dot(J, numpy.transpose(J))
    return


  def _calcArea(self):
    a = self.coords[0]
    b = self.coords[1]
    c = self.coords[2]
    J = numpy.array(( [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]],
                      [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]]),
                    dtype=numpy.float64)
    self.area = 0.5*numpy.sqrt(det(numpy.dot(J, numpy.transpose(J))))
    return


  def _calcAreaDir(self):
    a = self.coords[0]
    b = self.coords[1]
    c = self.coords[2]
    u = [-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]]
    v = [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]]
    self.areaDir = [ 0.5*(u[1]*v[2]-u[2]*v[1])/self.area,
                     0.5*(u[2]*v[0]-u[0]*v[2])/self.area,
                     0.5*(u[0]*v[1]-u[1]*v[0])/self.area]
    return


  def _calcVolume(self):
    a = self.coords[0]
    b = self.coords[1]
    c = self.coords[2]
    d = self.coords[3]
    J = numpy.array(([-a[0]+b[0], -a[1]+b[1], -a[2]+b[2]],
                     [-a[0]+c[0], -a[1]+c[1], -a[2]+c[2]],
                     [-a[0]+d[0], -a[1]+d[1], -a[2]+d[2]]),
                    dtype=numpy.float64)
    self.volume = det(J)/6.0
    return


# MAIN /////////////////////////////////////////////////////////////////
if __name__ == "__main__":

  app = SimpleDBQueryData3D()
  app.run()


# End of file
