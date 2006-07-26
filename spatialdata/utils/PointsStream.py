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

## @file spatialdata/utils/PointsStream.py
## @brief Python object for reading/writing points from stdin/stdout.

from pyre.components.Component import Component

# PointsStream class
class PointsStream(Component):
  """
  Python object for reading/writing points from stdin/stdout.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing PointsStream facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing PointsStream facilities and properties.
    ##
    ## \b Properties (input)
    ## @li \b commentFlag String identifying comment.
    ##
    ## \b Properties (output)
    ## @li \b field_width Width of field for coordinates
    ## @li \b precision Decimnal precision of coordinates
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    commentFlag = pyre.inventory.str("comment_flag", default="#")
    commentFlags.meta['tip'] = "String identifying comment."

    fieldWidth = pyre.inventory.int("field_width", default=14)
    fieldWidth.meta['tip'] = "Width of field for coordinates."
    fieldWidth.validator = pyre.inventory.greater(0)

    precision = pyre.inventory.int("precision", default=5)
    precision.meta['tip'] = "Decimal precision of coordinates."
    precision.validator = pyre.inventory.greaterEqual(0)


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def read(self):
    """
    Read points from stdin.
    """
    self._sync()
    points = self.cppHandle.read()
    return points


  def write(self, points):
    """
    Write points to stdout.
    """
    self._sync()
    self.cppHandle.write(points)
    return


  def __init__(self, name="pointsstream"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="pointsstream")
    import spatialdata.utils.utils as bindings
    self.cppHandle = bindings.PointsStream()
    self.commentFlag = "#"
    self.fieldWidth = 14
    self.precision = 5
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    self.commentFlag = self.inventory.commentFlag
    self.fieldWidth = self.inventory.fieldWidth
    self.precision = self.inventory.precision
    return


  def _sync(self):
    """
    Synchronize with C++ object.
    """
    self.cppHandle.commentFlag = self.commentFlag
    self.cppHandle.fieldWidth = self.fieldWidth
    self.cppHandle.precision = self.precision
    return
  

# End of file 
