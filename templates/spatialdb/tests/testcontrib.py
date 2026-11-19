#!/usr/bin/env python
# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


import unittest


def suite():

    suite = unittest.TestSuite()

    from TestUniformVelModel import TestUniformVelModel

    suite.addTest(unittest.makeSuite(TestUniformVelModel))

    return suite


def main():
    unittest.TextTestRunner(verbosity=2).run(suite())
    return


if __name__ == "__main__":
    main()


# End of file
