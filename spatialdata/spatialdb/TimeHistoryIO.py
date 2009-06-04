#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
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
