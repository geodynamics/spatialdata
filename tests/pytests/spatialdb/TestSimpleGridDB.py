#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

import unittest

import numpy
from spatialdata.geocoords.CSCart import CSCart
from spatialdata.spatialdb.SimpleGridAscii import SimpleGridAscii
from spatialdata.spatialdb.SimpleGridDB import SimpleGridDB

class TestSimpleGridDB(unittest.TestCase):

  def setUp(self):
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


  def test_io(self):
    from spatialdata.spatialdb.SimpleGridAscii import SimpleGridAscii

    filename = "data/gridio.spatialdb"
    x = numpy.array([-2.0, 0.0, 3.0], dtype=numpy.float64)
    y = numpy.array([0.0, 1.0], dtype=numpy.float64)
    z = numpy.array([-2.0, -1.0, 2.0], dtype=numpy.float64)

    points = numpy.array([
        [-2.0,  0.0, -2.0],
        [-2.0,  1.0, -2.0],
        [-2.0,  0.0, -1.0],
        [-2.0,  1.0, -1.0],
        [-2.0,  0.0,  2.0],
        [-2.0,  1.0,  2.0],
        [ 0.0,  0.0, -2.0],
        [ 0.0,  1.0, -2.0], # query (5.7, 8.2)
        [ 0.0,  0.0, -1.0],
        [ 0.0,  1.0, -1.0],
        [ 0.0,  0.0,  2.0],
        [ 0.0,  1.0,  2.0],
        [ 3.0,  0.0, -2.0],
        [ 3.0,  1.0, -2.0],
        [ 3.0,  0.0, -1.0],
        [ 3.0,  1.0, -1.0],
        [ 3.0,  0.0,  2.0],
        [ 3.0,  1.0,  2.0],
        ], dtype=numpy.float64)
    one = numpy.array([6.6, 5.5, 2.3, 5.7, 6.3, 3.4, 7.2, 5.7, 3.4, 5.7, 9.4, 7.2, 4.8, 9.2, 5.8, 4.7, 7.8, 2.9], dtype=numpy.float64)
    two = numpy.array([3.4, 6.7, 4.1, 2.0, 6.7, 6.4, 6.8, 8.2, 9.8, 2.3, 8.5, 9.3, 7.5, 8.3, 8.5, 8.9, 6.2, 8.3], dtype=numpy.float64)

    cs = CSCart()
    cs.initialize()

    writer = SimpleGridAscii()
    writer.inventory.filename = filename
    writer._configure()
    writer.write({'points': points,
                  'x': x,
                  'y': y,
                  'z': z,
                  'coordsys': cs,
                  'data_dim': 3,
                  'values': [{'name': "one",
                              'units': "m",
                              'data': one},
                             {'name': "two",
                              'units': "m",
                              'data': two},
                             ]})

    db = SimpleGridDB()
    db.inventory.label = "test"
    db.inventory.queryType = "nearest"
    db.inventory.filename = filename
    db._configure()
    self._db = db

    locs = numpy.array( [[0.1, 0.95, -1.8]], numpy.float64)
    cs = CSCart()
    cs._configure()
    queryVals = ["two", "one"]
    dataE = numpy.array( [[8.2, 5.7]], numpy.float64)
    errE = [0]

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

# End of file 
