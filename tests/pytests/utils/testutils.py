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

  from TestSimpleArray import TestSimpleArray
  suite.addTest(unittest.makeSuite(TestSimpleArray))

  from TestChangeCoordSys import TestChangeCoordSys
  suite.addTest(unittest.makeSuite(TestChangeCoordSys))

  from TestPointsStream import TestPointsStream
  suite.addTest(unittest.makeSuite(TestPointsStream))

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  
# version
__id__ = "$Id$"

# End of file 
