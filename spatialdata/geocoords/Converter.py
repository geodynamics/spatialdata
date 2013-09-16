#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/geocoords/Converter.py
##
## @brief Python function to convert b/t coordinate systems.

def convert(coords, csDest, csSrc):
  """
  Convert coordinates from source coordinate system to destination
  coordinate system. Transformation is done in place.
  """

  if not csDest.spaceDim() == csSrc.spaceDim():
    msg = "Spatial dimensions of source (%d) and destination (%d) " \
          "coordinate systems must match." % (csSrc.spaceDim(), csDest.spaceDim())
    raise ValueError(msg)

  import geocoords
  geocoords.Converter.convert(coords, csDest, csSrc)
  return


# End of file 
