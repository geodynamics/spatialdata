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

  import spatialdata.utils.simplearray as simplearray
  coordsSrcArray = simplearray.SimplePyArray(coordsSrc)

  import spatialdata.geocoords.geocoords as bindings
  bindings.Converter_convert(coordsSrcArray, csDest.cppHandle, csSrc.cppHandle)
  return


# version
__id__ = "$Id$"

# End of file 
