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

  return suite

def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return

if __name__ == '__main__':
  main()
  
# version
__id__ = "$Id: testspatial.py,v 1.1 2005/03/17 22:18:34 baagaard Exp $"

# End of file 
