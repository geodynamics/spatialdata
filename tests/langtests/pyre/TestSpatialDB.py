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

class TestSpatialDB(unittest.TestCase):

  def setUp(self):

    from spatialdata.SimpleIOAscii import SimpleIOAscii
    iohandler = SimpleIOAscii()
    iohandler.inventory.filename = "data/spatialdb.dat"
    iohandler.initialize()

    from spatialdata.SimpleDB import SimpleDB
    db = SimpleDB()
    db.inventory.query_type = "Nearest"
    db.inventory.iohandler = iohandler
    db.initialize()

    self._db = db
    return

  def test_cquery(self):
    self._db.open()
    self._db.queryVals(["two", "one"])
    self._cquery()
    self._db.close()
    
    return

  def test_f77query(self):
    self._db.open()
    self._db.queryVals(["two", "one"])
    self._f77query()
    self._db.close()
    
    return

  def _cquery(self):
    import spatialdata.tests.langtestspatialdb as bindings
    bindings.CTestQuery(self._db.handle())
    return

  def _f77query(self):
    import spatialdata.tests.langtestspatialdb as bindings
    bindings.F77TestQuery(self._db.handle())
    return

# version
__id__ = "$Id: TestSpatialDB.py,v 1.3 2005/03/23 18:10:47 baagaard Exp $"

# End of file 
