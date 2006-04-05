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

## @file pyre/Filters.py
## @brief Python manager for filters controlling spatial distribution.

from pyre.components.Component import Component

# Filters class
class Filters(Component):
  """Python manager for filters controlling spatial distribution."""

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="filters"):
    """Constructor."""
    Component.__init__(self, name, facility="filters")
    self.filters = []
    return


# version
__id__ = "$Id$"

# End of file 