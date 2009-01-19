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
