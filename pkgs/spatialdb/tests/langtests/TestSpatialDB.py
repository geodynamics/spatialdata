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

    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    iohandler = SimpleIOAscii()
    iohandler.inventory.filename = "data/spatialdb.dat"
    iohandler.initialize()

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = SimpleDB()
    db.query_type = "Nearest"
    db.iohandler = iohandler
    db.initialize()

    self._db = db

    from spatialdata.geocoords.CSCart import CSCart
    cs = CSCart()
    cs.initialize()
    self._cs = cs
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
    import langtestspatialdb as bindings
    bindings.cTestQuery(self._db.handle(), self._cs.handle())
    return

  def _f77query(self):
    import langtestspatialdb as bindings
    bindings.f77TestQuery(self._db.handle(), self._cs.handle())
    return

# version
__id__ = "$Id$"

# End of file 
