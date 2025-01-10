# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from pythia.pyre.components.Component import Component

import numpy


class PointsStream(Component):
    """
    Object for reading/writing points from stdin/stdout.
    """
    DOC_CONFIG = {
        "cfg": """
            [points_writer]
            filename = points.txt
            comment_flag = #
            number_format = %14.5e
            """,
    }

    import pythia.pyre.inventory

    filename = pythia.pyre.inventory.str("filename", default="")
    filename.meta['tip'] = "Name of file for input/output."

    commentFlag = pythia.pyre.inventory.str("comment_flag", default="#")
    commentFlag.meta['tip'] = "String identifying comment."

    numFormat = pythia.pyre.inventory.str("number_format", default="%14.5e")
    numFormat.meta['tip'] = "C style string specifying number format."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def read(self):
        """
        Read points from stdin.
        """
        points = numpy.loadtxt(self.filename, comments=self.commentFlag)
        return points

    def write(self, points):
        """
        Write points to stdout.
        """
        numpy.savetxt(self.filename, points, fmt=self.numFormat)
        return

    def __init__(self, name="pointsstream"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="pointsstream")
        return


# FACTORIES ////////////////////////////////////////////////////////////

def writer():
    """
    Factory associated with PointsStream.
    """
    return PointsStream()


def reader():
    """
    Factory associated with PointsStream.
    """
    return PointsStream()


# End of file
