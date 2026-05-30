# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2026, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================
# @file spatialdata/__init__.py
#
# @brief Python top-level SpatialData module initialization

try:
    import importlib.metadata
    version = importlib.metadata.version("spatialdata")
except:
    version = "Could not get version information via importlib.metadata."

__version__ = version


__all__ = [
    'geocoords',
    'spatialdb',
    'units',
    'utils',
]


# End of file
