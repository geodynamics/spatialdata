#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
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
    
    app = GenSimpleDBApp()
    app.run()

    # Test write using query
    db = SimpleDB()
    db.inventory.iohandler.inventory.filename = \
        "data/gen1Din2D.spatialdb"
    db.inventory.iohandler._configure()
    db.inventory.label = "test"
    db.inventory.queryType = "nearest"
    db._configure()

    qlocs = numpy.array( [[-2.0,  2.0],
                          [ 3.0, -4.0],
                          [ 0.0,  0.7]],
                         numpy.float64)
    
    dataE = numpy.array( [[-0.15, 3.45],
                          [2.4, 6.4],
                          [-0.6, 3.45]], numpy.float64)
    errE = [0, 0, 0]

    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    cs.inventory.spaceDim = 2
    cs._configure()

    db.open()
    db.queryVals(["two", "one"])
    data = numpy.zeros(dataE.shape, dtype=numpy.float64)
    err = []
    nlocs = qlocs.shape[0]
    for i in xrange(nlocs):
      e = db.query(data[i,:], qlocs[i,:], cs)
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
