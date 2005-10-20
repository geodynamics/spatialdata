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

def convert(coordsSrc, csDest, csSrc):
  """Convert coordinates from source coordinate system to destination
  coordinate system."""

  import spatialdata.geocoords.geocoords as bindings
  coordsDest = bindings.CppConverter_convert(coordsSrc,
                                             csDest.handle(), csSrc.handle())

  return coordsDest


# version
__id__ = "$Id$"

# End of file 
