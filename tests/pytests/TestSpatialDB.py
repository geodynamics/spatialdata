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

    from spatialdata.SimpleDB import SimpleDB
    db = SimpleDB()
    db.inventory.query_type = "Nearest"
    db.inventory.iohandler = iohandler
    db.initialize()
    self._db = db
    return

  def test_database(self):
    self._db.open()
    self._db.queryVals(["two", "one"])
    self._db.close()    
    return

# version
__id__ = "$Id: TestSpatialDB.py,v 1.3 2005/03/21 20:26:48 baagaard Exp $"

# End of file 
