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
import spatialdata.utils.simplearray as simplearray

class TestSimpleArray(unittest.TestCase):


  def test_frompy(self):
    vals = [1.1, 2.1, 3.1, 1.2, 2.2, 3.2]
    x = numpy.array(vals, numpy.float64)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numpy.array(y)
    for vE, v in zip(vals, z):
      self.assertAlmostEqual(vE, v, 6)

    vals = [ [1, 2, 3],
             [4, 5, 6] ]
    x = numpy.array(vals, numpy.int32)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numpy.array(y)
    for vE,v in zip(numpy.reshape(vals, -1), numpy.reshape(z, -1)):
      self.assertEqual(vE, v)

    vals = [ [ [1.1, 2.1, 3.1] ],
             [ [2.1, 2.2, 3.2] ] ]
    x = numpy.array(vals, numpy.float32)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numpy.array(y)
    for vE,v in zip(numpy.reshape(vals, -1), numpy.reshape(z, -1)):
      self.assertAlmostEqual(vE, v, 4)
    return


  def test_fromcpp(self):
    vals = [ [1.1, 2.1, 3.1],
             [1.2, 2.2, 3.2] ]
    x = numpy.array(vals, numpy.float64)
    import spatialdata.utils.testcpp as testcpp
    y = testcpp.cpparray()
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numpy.array(y)
    for vE,v in zip(numpy.reshape(vals, -1), numpy.reshape(z, -1)):
      self.assertAlmostEqual(vE, v, 4)
    return


  def test_tocpp(self):
    vals = [ [1.1, 2.1],
             [1.2, 2.2],
             [1.3, 2.3] ]
    x = numpy.array(vals, numpy.float64)
    import spatialdata.utils.testcpp as testcpp
    try:
      testcpp.test(simplearray.SimplePyArray(x))
    except ValueError, er:
      print er
      self.assertEqual(1, 0)
    return


# version
__id__ = "$Id$"

# End of file 
