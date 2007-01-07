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
## @brief Python function to convert b/t coordinate systems.

def convert(coordsSrc, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system. Transformation is done in place."""

  if not csDest.spaceDim == csSrc.spaceDim:
    msg = "Spatial dimensions of source (%d) and destination (%d) " \
          "coordinate systems must match." % (csSrc.spaceDim, csDest.spaceDim)
    raise ValueError(msg)

  import spatialdata.geocoords.geocoords as bindings
  bindings.Converter_convert(coordsSrc, csDest.cppHandle, csSrc.cppHandle)
  return


# End of file 
