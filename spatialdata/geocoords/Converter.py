# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================


def convert(points, csDest, csSrc):
    """
    Convert coordinates from source coordinate system to destination
    coordinate system. Transformation is done in place.

    :param points: Numpy array of points [npoints, 2].
    :param csDest: Destination coordinate system.
    :param csSrc: Source coordinate system. Current coordinate system for points.
    """

    if not csDest.getSpaceDim() == csSrc.getSpaceDim():
        msg = "Spatial dimensions of source (%d) and destination (%d) " \
              "coordinate systems must match." % (
                  csSrc.getSpaceDim(), csDest.getSpaceDim())
        raise ValueError(msg)

    from . import geocoords
    converter = geocoords.Converter()
    converter.convert(points, csDest, csSrc)
    return


# End of file
