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

  def test_database(self):
    self._initialize()
    
    self._db.open()
    self._db.queryType("Nearest")
    self._db.queryVals(["two", "one"])
    self._db.close()
    
    return

  def _initialize(self):

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

# version
__id__ = "$Id: TestSpatialDB.py,v 1.1 2005/03/17 22:18:34 baagaard Exp $"

# End of file 
