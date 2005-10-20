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

def suite():

  suite = unittest.TestSuite()

  from TestCoordSysGeo import TestCoordSysGeo
  suite.addTest(unittest.makeSuite(TestCoordSysGeo))

  from TestCoordSysLocal import TestCoordSysLocal
  suite.addTest(unittest.makeSuite(TestCoordSysLocal))

  from TestProjector import TestProjector
  suite.addTest(unittest.makeSuite(TestProjector))

  from TestConverter import TestConverter
  suite.addTest(unittest.makeSuite(TestConverter))

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  
# version
__id__ = "$Id$"

# End of file 
