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
##
## @brief Python object for reading/writing points from stdin/stdout.
##
## Factories: reader, writer

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

    Factories: reader, writer
    """

    ## @class Inventory
    ## Python object for managing PointsStream facilities and properties.
    ##
    ## \b Properties
    ## @li \b filename Name of file for input/output
    ##          (default is to use stdin/stdout).
    ## @li \b commentFlag String identifying comment (input).
    ## @li \b field_width Width of field for coordinates (output).
    ## @li \b precision Decimnal precision of coordinates (output).
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="")
    filename.meta['tip'] = "Name of file for input/output."

    commentFlag = pyre.inventory.str("comment_flag", default="#")
    commentFlag.meta['tip'] = "String identifying comment."

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
    self.filename = ""
    self.commentFlag = "#"
    self.fieldWidth = 14
    self.precision = 5
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    self.filename = self.inventory.filename
    self.commentFlag = self.inventory.commentFlag
    self.fieldWidth = self.inventory.fieldWidth
    self.precision = self.inventory.precision
    return


  def _sync(self):
    """
    Synchronize with C++ object.
    """
    self.cppHandle.filename = self.filename
    self.cppHandle.commentFlag = self.commentFlag
    self.cppHandle.fieldWidth = self.fieldWidth
    self.cppHandle.precision = self.precision
    return


# FACTORIES ////////////////////////////////////////////////////////////

def writer():
  """
  Factory associated with PointsStream.
  """
  return PointsStream()


def reader():
  """
  Factory associated with PointsStream.
  """
  return PointsStream()


# End of file 
