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
from spatialdata.geocoords.CSCart import CSCart

class TestSimpleDB(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = SimpleDB()
    db.inventory.label = "test"
    db.inventory.queryType = "nearest"
    db.inventory.iohandler.inventory.filename = "data/spatialdb.dat"
    db.inventory.iohandler._configure()
    db._configure()
    self._db = db
    return


  def test_database(self):
    locs = numpy.array( [[1.0, 2.0, 3.0],
                         [5.6, 4.2, 8.6]],
                        numpy.float64)
    cs = CSCart()
    cs._configure()
    queryVals = ["two", "one"]
    dataE = numpy.array( [[4.7, 6.3]]*2, numpy.float64)
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


# End of file 