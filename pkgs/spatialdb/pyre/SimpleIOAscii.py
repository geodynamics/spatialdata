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

## @file pyre/SimpleIOAscii.py
## @brief Python ascii I/O manager for simple spatial database (SimpleDB).

from SimpleIO import SimpleIO

# SimpleIOAscii class
class SimpleIOAscii(SimpleIO):
  """Python ascii I/O manager for simple spatial database (SimpleDB)."""

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpleioascii"):
    """Constructor."""
    SimpleIO.__init__(self, name)

    import spatialdb as bindings
    self._cppSimpleIO = bindings.CppSimpleIOAscii()

    return

# version
__id__ = "$Id: SimpleIOAscii.py,v 1.1 2005/05/25 18:43:00 baagaard Exp $"

# End of file 
