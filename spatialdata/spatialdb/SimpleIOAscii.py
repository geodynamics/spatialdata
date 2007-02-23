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

## @file spatialdata/spatialdb/SimpleIOAscii.py
## @brief Python ascii I/O manager for simple spatial database (SimpleDB).

from SimpleIO import SimpleIO

# SimpleIOAscii class
class SimpleIOAscii(SimpleIO):
  """
  Python ascii I/O manager for simple spatial database (SimpleDB).
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def write(self, cppDB, cs):
    """
    Write database data to file.
    """
    self.cppHandle.write(cppDB, cs.cppHandle)
    return


  def __init__(self, name="simpleioascii"):
    """Constructor."""
    SimpleIO.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.SimpleIOAscii()
    return


# End of file 
