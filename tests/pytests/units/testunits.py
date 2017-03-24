#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
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
