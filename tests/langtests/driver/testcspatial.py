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

  from spatialdata.tests.TestSpatialDB import TestSpatialDB
  suite.addTest(unittest.makeSuite(TestSpatialDB))

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  
# version
__id__ = "$Id: testcspatial.py,v 1.1 2005/03/19 00:46:56 baagaard Exp $"

# End of file 
