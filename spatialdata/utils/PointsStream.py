# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

# @file spatialdata/utils/PointsStream.py
#
# @brief Python object for reading/writing points from stdin/stdout.
#
# Factories: reader, writer

from pythia.pyre.components.Component import Component

import numpy


class PointsStream(Component):
    """
    Python object for reading/writing points from stdin/stdout.

    INVENTORY

    Properties
      - *filename* Name of file to use for input/output (default is stdin/stdout).
      - *comment_flag* String at beginning of comment lines.
      - *number_format* C style string specifying number format.

    Facilities
      - None
    """

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
