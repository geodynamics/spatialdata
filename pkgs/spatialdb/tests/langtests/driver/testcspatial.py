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

  from spatialdata.spatialdb.tests.TestSpatialDB import TestSpatialDB
  suite.addTest(unittest.makeSuite(TestSpatialDB))

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  
# version
__id__ = "$Id: testcspatial.py,v 1.1 2005/05/25 18:43:01 baagaard Exp $"

# End of file 
