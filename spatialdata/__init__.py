# ----------------------------------------------------------------------
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
# ----------------------------------------------------------------------
#
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
