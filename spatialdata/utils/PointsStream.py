#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2015 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/utils/PointsStream.py
##
## @brief Python object for reading/writing points from stdin/stdout.
##
## Factories: reader, writer

from pyre.components.Component import Component

import numpy

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
    ## @li \b numFormat C style string specifying number format.
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="")
    filename.meta['tip'] = "Name of file for input/output."

    commentFlag = pyre.inventory.str("comment_flag", default="#")
    commentFlag.meta['tip'] = "String identifying comment."

    numFormat = pyre.inventory.str("number_format", default="%14.5e")
    numFormat.meta['tip'] = "C style string specifying number format."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def read(self):
    """
    Read points from stdin.
    """
    points = numpy.loadtxt(self.filename,
                           comments=self.commentFlag)
    return points


  def write(self, points):
    """
    Write points to stdout.
    """
    numpy.savetxt(self.filename,
                  points,
                  fmt=self.numFormat)
    return


  def __init__(self, name="pointsstream"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="pointsstream")
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    self.filename = self.inventory.filename
    self.commentFlag = self.inventory.commentFlag
    self.numFormat = self.inventory.numFormat
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
