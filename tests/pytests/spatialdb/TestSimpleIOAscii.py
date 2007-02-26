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

class TestSimpleIOAscii(unittest.TestCase):

  def test_write(self):
    """
    Test write().
    """
    # Database info
    filename = "data/test.spatialdb"
    cs = CSCart()
    data = {'locs': numpy.array( [ [1.0, 2.0, 3.0],
                                   [0.5, 3.0, -3.0]], numpy.float64),
            'coordsys': cs,
            'data_dim': 1,
            'values': [{'name': "One",
                        'units': "m",
                        'data': numpy.array( [2.0, 8.0], numpy.float64)},
                       {'name': "Two",
                        'units': "m",
                        'data': numpy.array( [-2.0, 3.0], numpy.float64)}]}
            
    dataDim = 1
            
    
    # Write database
    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    writer = SimpleIOAscii()
    writer.filename = filename
    writer.initialize()
    writer.write(data)

    # Test write using query
    from spatialdata.spatialdb.SimpleDB import SimpleDB
    iohandler = SimpleIOAscii()
    iohandler.filename = filename
    db = SimpleDB()
    db.label = "test"
    db.queryType = "Linear"
    db.iohandler = iohandler
    db.initialize()

    db.open()
    db.queryVals(["two", "one"])

    qlocs = numpy.array( [[0.875, 2.25, 1.5],
                          [0.6, 2.8, -1.8],
                          [1.0, 2.0, 3.0]],
                         numpy.float64)
    
    valsE = numpy.array( [[-0.75, 3.5],
                          [2.0, 6.8],
                          [-2.0, 2.0]], numpy.float64)
    
    (vals, err) = db.query(qlocs, cs, 2)
    vals = numpy.array(vals)

    self.assertEqual(len(valsE.shape), len(vals.shape))
    for dE, d in zip(valsE.shape, vals.shape):
      self.assertEqual(dE, d)
    for vE, v in zip(numpy.reshape(valsE, -1), numpy.reshape(vals, -1)):
      self.assertAlmostEqual(vE, v, 6)

    db.close()    
    return


# End of file 
