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

  from TestNondimensional import TestNondimensional
  suite.addTest(unittest.makeSuite(TestNondimensional))

  from TestNondimElasticQuasistatic import TestNondimElasticQuasistatic
  suite.addTest(unittest.makeSuite(TestNondimElasticQuasistatic))

  from TestNondimElasticDynamic import TestNondimElasticDynamic
  suite.addTest(unittest.makeSuite(TestNondimElasticDynamic))

  return suite


def main():
  unittest.TextTestRunner(verbosity=2).run(suite())
  return


if __name__ == '__main__':
  main()

  
# End of file 
