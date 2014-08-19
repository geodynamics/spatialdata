#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2014 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/utils/ChangeCoordSys.py
##
## @brief Python object for changing coordinate system of points.
##
## Factory: converter.

from pyre.components.Component import Component

# ChangeCoordSys class
class ChangeCoordSys(Component):
  """
  Python object for changing coordinate system of points.

  Factory: converter.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing ChangeCoordSys facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing ChangeCoordSys facilities
    ## and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b cs_src Source coordinate system
    ## @li \b cs_dest Destination coordinate system

    import pyre.inventory

    from spatialdata.geocoords.CSCart import CSCart

    csSrc = pyre.inventory.facility("cs_src", family="coordsys",
                                    factory=CSCart)
    csSrc.meta['tip'] = "Source coordinate system."

    csDest = pyre.inventory.facility("cs_dest", family="coordsys",
                                     factory=CSCart)
    csDest.meta['tip'] = "Destination coordinate system."    


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def convert(self, points):
    """
    Transform coordinates of points from one coordinate system to another.
    """
    self._initialize()
    from spatialdata.geocoords.Converter import convert
    convert(points, self.csDest, self.csSrc)
    return


  def __init__(self, name="changecoordsys"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="converter")
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members from inventory.
    """
    Component._configure(self)
    self.csDest = self.inventory.csDest
    self.csSrc = self.inventory.csSrc
    return


  def _initialize(self):
    """
    Initialize converter.
    """
    self.csSrc.initialize()
    self.csDest.initialize()
    return


# FACTORIES ////////////////////////////////////////////////////////////

def converter():
  """
  Factory associated with ChangeCoordSys.
  """
  return ChangeCoordSys()


# End of file 
