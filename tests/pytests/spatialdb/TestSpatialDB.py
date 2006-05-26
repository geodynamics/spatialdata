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
    self._db.close()    
    return

# version
__id__ = "$Id: TestSpatialDB.py,v 1.1 2005/05/25 18:43:08 baagaard Exp $"

# End of file 
