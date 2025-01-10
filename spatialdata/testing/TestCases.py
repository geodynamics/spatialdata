# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================
"""PyLith module for unit test helper functions."""

import unittest

def make_suite(test_classes, loader=unittest.defaultTestLoader):
    suite = unittest.TestSuite()
    for cls in test_classes:
        suite.addTests(loader.loadTestsFromTestCase(cls))
    return suite


# End of file
