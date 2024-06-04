#!/usr/bin/env python
#
# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

import unittest


def suite():

    suite = unittest.TestSuite()

    from TestUniformVelModel import TestUniformVelModel
    suite.addTest(unittest.makeSuite(TestUniformVelModel))

    return suite


def main():
    unittest.TextTestRunner(verbosity=2).run(suite())
    return


if __name__ == '__main__':
    main()


# End of file
