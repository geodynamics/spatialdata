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

## @file spatialdata/spatialdb/generator/Shapers.py
##
## @brief Python manager for shapers controlling spatial distribution.
##
## Factory: shapers

from pyre.components.Component import Component

# Shapers class
class Shapers(Component):
  """
  Python manager for shapers controlling spatial distribution.

  Factory: shapers
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="shapers"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="shapers")
    self.shapers = []
    return


# FACTORIES ////////////////////////////////////////////////////////////

def shapers():
  """
  Factory associated with Shapers.
  """
  return Shapers()


# End of file 
