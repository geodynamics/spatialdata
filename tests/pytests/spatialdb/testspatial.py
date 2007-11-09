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

  from TestSpatialDB import TestSpatialDB
  suite.addTest(unittest.makeSuite(TestSpatialDB))

  from TestSimpleIOAscii import TestSimpleIOAscii
  suite.addTest(unittest.makeSuite(TestSimpleIOAscii))

  from TestUniformDB import TestUniformDB
  suite.addTest(unittest.makeSuite(TestUniformDB))

  from TestGravityField import TestGravityField
  suite.addTest(unittest.makeSuite(TestGravityField))

  from TestGenSimpleDBApp import TestGenSimpleDBApp
  suite.addTest(unittest.makeSuite(TestGenSimpleDBApp))

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  

# End of file 
