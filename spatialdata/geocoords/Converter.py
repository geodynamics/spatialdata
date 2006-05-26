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

def convertpy(coordsSrc, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system. Coordinates are stored in a Python array."""

  import spatialdata.geocoords.geocoords as bindings
  coordsDest = bindings.Converter_convertpy(coordsSrc,
                                            csDest.cppHandle, csSrc.cppHandle)

  return coordsDest


def convertcpp(handle, numLocs, numCoords, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system. Coordinates are stored in a PyCObject. """

  import spatialdata.geocoords.geocoords as bindings
  bindings.pConverter_convertcpp(handle, numLocs, numCoords,
                                 csDest.cppHandle, csSrc.cppHandle)
  
  return


# version
__id__ = "$Id$"

# End of file 
