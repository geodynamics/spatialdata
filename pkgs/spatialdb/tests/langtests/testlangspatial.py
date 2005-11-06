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

import sys
sys.path.append('.libs')

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
__id__ = "$Id$"

# End of file 
