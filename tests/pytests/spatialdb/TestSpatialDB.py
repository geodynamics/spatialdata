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
from spatialdata.geocoords.CSCart import CSCart

class TestSpatialDB(unittest.TestCase):

  def setUp(self):
    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    iohandler = SimpleIOAscii()
    iohandler.filename = "data/spatialdb.dat"

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = SimpleDB()
    db.label = "test"
    db.queryType = "Nearest"
    db.iohandler = iohandler
    db.initialize()
    self._db = db
    return

  def test_database(self):
    self._db.open()
    self._db.queryVals(["two", "one"])

    locs = numpy.array( [[1.0, 2.0, 3.0],
                         [5.6, 4.2, 8.6]],
                        numpy.Float64)
    cs = CSCart()
    cs.toMeters = 1.0
    
    valsE = numpy.array( [[4.7, 6.3]]*2, numpy.Float64)
    vals = numpy.array(self._db.query(locs, cs, 2))
    self.assertEqual(2, len(vals.shape))
    for dE, d in zip(valsE.shape, vals.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(valsE, -1), numpy.reshape(vals, -1)):
      self.assertAlmostEqual(vE, v, 6)

    self._db.close()    
    return


# End of file 
