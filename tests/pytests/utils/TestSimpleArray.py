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

import numpy as numeric
import spatialdata.utils.utils as simplearray

class TestSimpleArray(unittest.TestCase):


  def test_frompy(self):
    vals = [1.1, 2.1, 3.1, 1.2, 2.2, 3.2]
    x = numeric.array(vals, numeric.Float64)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numeric.array(y)
    for vE, v in zip(vals, z):
      self.assertAlmostEqual(vE, v, 6)

    vals = [ [1, 2, 3],
             [4, 5, 6] ]
    x = numeric.array(vals, numeric.Int32)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numeric.array(y)
    for vE,v in zip(numeric.reshape(vals, -1), numeric.reshape(z, -1)):
      self.assertEqual(vE, v)

    vals = [ [ [1.1, 2.1, 3.1] ],
             [ [2.1, 2.2, 3.2] ] ]
    x = numeric.array(vals, numeric.Float32)
    y = simplearray.SimplePyArray(x)
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numeric.array(y)
    for vE,v in zip(numeric.reshape(vals, -1), numeric.reshape(z, -1)):
      self.assertAlmostEqual(vE, v, 4)
    return


  def test_fromcpp(self):
    vals = [ [1.1, 2.1, 3.1],
             [1.2, 2.2, 3.2] ]
    x = numeric.array(vals, numeric.Float64)
    import spatialdata.utils.testcpp as testcpp
    y = testcpp.cpparray()
    self.assertEqual(len(x.shape), y.nd)
    self.assertEqual(len(x.shape), len(y.shape))
    for dE,d in zip(x.shape, y.shape):
      self.assertEqual(dE, d)
    z = numeric.array(y)
    for vE,v in zip(numeric.reshape(vals, -1), numeric.reshape(z, -1)):
      self.assertAlmostEqual(vE, v, 4)
    return


  def test_tocpp(self):
    vals = [ [1.1, 2.1],
             [1.2, 2.2],
             [1.3, 2.3] ]
    x = numeric.array(vals, numeric.Float64)
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
