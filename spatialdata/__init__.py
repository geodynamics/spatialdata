# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================
# @file spatialdata/__init__.py
#
# @brief Python top-level SpatialData module initialization

try:
    from pkg_resources import get_distribution
    version = get_distribution("spatialdata").version
except:
    version = "Could not get version information via pkg_resources."

__version__ = version


__all__ = [
    'geocoords',
    'spatialdb',
    'units',
    'utils',
]


# End of file
