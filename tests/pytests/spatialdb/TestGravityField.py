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


class TestGravityField(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.GravityField import GravityField
    db = GravityField()
    db._configure()
    db.initialize()
    self._db = db
    return

  def test_database(self):
    locs = numpy.array( [[1.0, 2.0, 3.0],
                         [5.6, 4.2, 8.6]],
                        numpy.float64)
    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    gacc = 9.80665
    dataE = numpy.array([[0.0, 0.0, -gacc],
                         [0.0, 0.0, -gacc]], numpy.float64)
    errE = numpy.array( [0]*2, numpy.int32)
    
    self._db.open()
    (data, err) = self._db.query(locs, cs, numvals=3)
    data = numpy.array(data)
    err = numpy.array(err)

    self.assertEqual(len(errE.shape), len(err.shape))
    for dE, d in zip(errE.shape, err.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(errE, -1), numpy.reshape(err, -1)):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)

    self._db.close()    
    return


# End of file 
