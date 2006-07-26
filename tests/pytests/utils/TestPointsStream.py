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

import unittest

import numpy
from spatialdata.utils.PointsStream import PointsStream

class TestPointsStream(unittest.TestCase):


  def test_filename(self):
    filename = "one"
    s = PointsStream()
    s.filename = filename
    self.assertEqual(filename, s.filename)
    return


  def test_commentFlag(self):
    flag = "%"
    s = PointsStream()
    s.commentFlag = flag
    self.assertEqual(flag, s.commentFlag)
    return


  def test_fieldWidth(self):
    fieldWidth = 6
    s = PointsStream()
    s.fieldWidth = fieldWidth
    self.assertEqual(fieldWidth, s.fieldWidth)
    return


  def test_precision(self):
    precision = 3
    s = PointsStream()
    s.precision = precision
    self.assertEqual(precision, s.precision)
    return

  
  def test_writeread(self):
    pointsE = numpy.array([ [1.0, 2.0, 3.0],
                            [1.1, 2.1, 3.1],
                            [1.2, 2.2, 3.2] ],
                          numpy.Float64)

    filename = "tmp.txt"
    s = PointsStream()
    print "AA"
    s.write(pointsE)
    print "BB"
    
    points = s.read()
    print "CC"
    self.assertEqual(len(pointsE.shape), len(points.shape))
    for dE,d in zip(pointsE.shape, points.shape):
      self.assertEqual(dE, d)
    for vE,v in zip(numpy.reshape(pointsE, -1), numpy.reshape(points, -1)):
      self.assertAlmostEqual(vE, v, 6)
    return


# End of file 
