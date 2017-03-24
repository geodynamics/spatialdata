#!/usr/bin/env python
#
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

## @file spatialdata/spatialdb/TimeHistoryIO.py
##
## @brief Python function to write time history file.

def write(time, amplitude, units, filename):
  """
  Write time history file.
  """
  import spatialdb
  spatialdb.TimeHistoryIO.write(time, amplitude, units, filename)
  return


# End of file 
