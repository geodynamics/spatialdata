# -*- python -*-
# -*- coding: utf-8 -*-
#
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026 The SpatialData authors and contributors
# SPDX-License-Identifier: MIT


try:
    import importlib.metadata

    version = importlib.metadata.version("spatialdata")
except:
    version = "Could not get version information via importlib.metadata."

__version__ = version


__all__ = [
    "geocoords",
    "spatialdb",
    "utils",
]


# End of file
