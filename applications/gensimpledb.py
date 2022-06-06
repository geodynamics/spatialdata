#!/usr/bin/env nemesis
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================
#
# @file spatialdata/applications/gensimpledb.py
#
# @brief Generic use of GenSimpleDBApp.

# ----------------------------------------------------------------------
if __name__ == '__main__':
    from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp

    app = GenSimpleDBApp()
    app.run()


# End of file
