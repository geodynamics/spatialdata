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

## @file spatialdata/geocoords/Projector.py
##
## @brief Python manager for projector.
##
## Factory: projector.

from pyre.components.Component import Component

# Projector class
class Projector(Component):
  """
  Python manager for projector.

  Factory: projector.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Projector facilities and properties."""

    ## @class Inventory
    ## Python object for managing Projector facilities and properties.
    ##
    ## \b Properties
    ## @li \b projection Name of projection
    ## @li \b units Name of units
    ## @li \b proj-options Additional proj options
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    projection = pyre.inventory.str("projection", default="aea")
    projection.meta['tip'] = "Name of projection."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    projOptions = pyre.inventory.str("proj-options", default="")
    projOptions.meta['tip'] = "Additional proj options."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="projector"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="projector")

    import spatialdata.geocoords.geocoords as bindings
    self.cppHandle = bindings.Projector()
    return


  def initialize(self, coordSys):
    """
    Initialize projector.
    """

    self.cppHandle.projection = self.projection
    self.cppHandle.units = self.units
    self.cppHandle.projOptions = self.projOptions
    self.cppHandle.initialize(coordSys.cppHandle)
    return


  def project(self, lonlat):
    """
    Project geographic coordinates.
    """
    return self.cppHandle.project(lonlat)
  

  def invproject(self, xy):
    """
    Project geographic coordinates.
    """
    return self.cppHandle.invproject(xy)
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    self.projection = self.inventory.projection
    self.units = self.inventory.units
    self.projOptions = self.inventory.projOptions
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return Projector()


# End of file 
