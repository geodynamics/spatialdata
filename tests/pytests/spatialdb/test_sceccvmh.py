#!/usr/bin/env nemesis
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest

import TestSCECCVMH


def load_tests(loader, tests, pattern):
    TEST_MODULES = [
        TestSCECCVMH,
    ]
    suite = unittest.TestSuite()
    for mod in TEST_MODULES:
        suite.addTests(loader.loadTestsFromModule(mod))
    return suite


if __name__ == '__main__':
    unittest.main(verbosity=2)


# End of file
