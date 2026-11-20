#!/usr/bin/env nemesis
# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


"""Generic use of GenSimpleDBApp."""

# ----------------------------------------------------------------------
if __name__ == "__main__":
    from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp

    app = GenSimpleDBApp()
    app.run()


# End of file
