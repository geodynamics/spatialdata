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

# ----------------------------------------------------------------------
class TestGenSimpleDBApp(unittest.TestCase):

  def test(self):
    """
    Test GenSimpleDBApp with 1-D data in 2-D space.
    """
    from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp
    from spatialdata.geocoords.CSCart import CSCart
    from spatialdata.spatialdb.SimpleDB import SimpleDB
    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    
    app = GenSimpleDBApp()
    app.run()

    # Test write using query
    from spatialdata.spatialdb.SimpleDB import SimpleDB
    iohandler = SimpleIOAscii()
    iohandler.filename = "data/gen1Din2D.spatialdb"
    db = SimpleDB()
    db.label = "test"
    db.queryType = "nearest"
    db.iohandler = iohandler
    db.initialize()

    db.open()
    db.queryVals(["two", "one"])

    qlocs = numpy.array( [[-2.0,  2.0],
                          [ 3.0, -4.0],
                          [ 0.0,  0.7]],
                         numpy.float64)
    
    valsE = numpy.array( [[-0.15, 3.45],
                          [2.4, 6.4],
                          [-0.6, 3.45]], numpy.float64)
    
    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    cs.spaceDim = 2
    cs.initialize()

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
