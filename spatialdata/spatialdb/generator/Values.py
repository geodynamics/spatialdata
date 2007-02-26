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

## @file spatialdata/spatialdb/generator/Values.py

## @brief Python manager for values in database.

from pyre.components.Component import Component

# Values class
class Values(Component):
  """
  Python manager for values in database.
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="values"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="values")
    self.values = []
    return


# End of file 
