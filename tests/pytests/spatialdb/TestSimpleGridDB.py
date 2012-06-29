#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

import numpy
from spatialdata.geocoords.CSCart import CSCart

class TestSimpleGridDB(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.SimpleGridDB import SimpleGridDB
    db = SimpleGridDB()
    db.inventory.label = "test"
    db.inventory.queryType = "nearest"
    db.inventory.filename = "data/grid.spatialdb"
    db._configure()
    self._db = db
    return


  def test_database(self):
    locs = numpy.array( [[3.5, 0.1, 0.8],
                         [8.0, -0.4, 1.8]],
                        numpy.float64)
    cs = CSCart()
    cs._configure()
    queryVals = ["two", "one"]
    dataE = numpy.array( [[0.0220, 1.04],
                          [0.0222, 1.02]], numpy.float64)
    errE = [0, 0]

    db = self._db
    db.open()
    db.queryVals(queryVals)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = locs.shape[0]
    for i in xrange(nlocs):
      e = db.query(data[i,:], locs[i,:], cs)
      err.append(e)
    db.close()    

    self.assertEqual(len(errE), len(err))
    for vE, v in zip(errE, err):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)

    return


  def test_databasemulti(self):
    locs = numpy.array( [[2.3, -0.1, 1.8],
                         [2.0,  0.4, -2.0]],
                        numpy.float64)
    cs = CSCart()
    cs._configure()
    queryVals = ["two", "one"]
    dataE = numpy.array( [[0.0207, 1.17],
                          [0.0209, 1.15]], numpy.float64)
    errE = numpy.array([0, 0], numpy.int32)

    db = self._db
    db.open()
    db.queryVals(queryVals)
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = numpy.zeros(errE.shape, dtype=numpy.int32)
    db.multiquery(data, err, locs, cs)
    db.close()    

    self.assertEqual(len(errE), len(err))
    for vE, v in zip(errE, err):
      self.assertEqual(vE, v)

    self.assertEqual(len(dataE.shape), len(data.shape))
    for dE, d in zip(dataE.shape, data.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(dataE, -1), numpy.reshape(data, -1)):
      self.assertAlmostEqual(vE, v, 6)

    return


# End of file 
