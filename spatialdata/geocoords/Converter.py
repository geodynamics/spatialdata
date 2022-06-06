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
