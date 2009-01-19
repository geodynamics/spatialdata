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

  from TestCSCart import TestCSCart
  suite.addTest(unittest.makeSuite(TestCSCart))

  from TestCSGeo import TestCSGeo
  suite.addTest(unittest.makeSuite(TestCSGeo))

  from TestCSGeoLocalCart import TestCSGeoLocalCart
  suite.addTest(unittest.makeSuite(TestCSGeoLocalCart))

  from TestCSGeoProj import TestCSGeoProj
  suite.addTest(unittest.makeSuite(TestCSGeoProj))

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
  

# End of file 
