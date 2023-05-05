# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2023 University of California, Davis
#
# See LICENSE.md for license information.
#
# ----------------------------------------------------------------------


def write(time, amplitude, units, filename):
    """
    Write time history file.
    """
    from .spatialdb import TimeHistoryIO as ModuleTimeHistoryIO
    ModuleTimeHistoryIO.write(time, amplitude, units, filename)
    return


# End of file
