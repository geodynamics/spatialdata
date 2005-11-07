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

## @file geocoords/pyre/Converter.py
## @brief Python function to convert b/t coordinate systems.

def convertpy(coordsSrc, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system. Coordinates are stored in a Python array."""

  import spatialdata.geocoords.geocoords as bindings
  coordsDest = bindings.CppConverter_convertpy(coordsSrc,
                                               csDest.handle(), csSrc.handle())

  return coordsDest


def convertcpp(handle, numLocs, numCoords, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system. Coordinates are stored in a PyCObject. """

  import spatialdata.geocoords.geocoords as bindings
  bindings.CppConverter_convertcpp(handle, numLocs, numCoords,
                                   csDest.handle(),
                                   csSrc.handle())

  return


# version
__id__ = "$Id$"

# End of file 
