# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


def write(time, amplitude, units, filename):
    """
    Write time history file.
    """
    from .spatialdb import TimeHistoryIO as ModuleTimeHistoryIO

    ModuleTimeHistoryIO.write(time, amplitude, units, filename)
    return


# End of file
