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
# @file spatialdata/applications/gensimpledb.py
#
# @brief Generic use of GenSimpleDBApp.

# ----------------------------------------------------------------------
if __name__ == '__main__':
    from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp

    app = GenSimpleDBApp()
    app.run()


# End of file
