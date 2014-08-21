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

## @file spatialdata/geocoords/Projector.py
##
## @brief Python manager for projector.
##
## Factory: projector.

from pyre.components.Component import Component
from geocoords import Projector as ModuleProjector

# Projector class
class Projector(Component, ModuleProjector):
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
    ## @li \b proj_options Additional proj options
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    projection = pyre.inventory.str("projection", default="aea")
    projection.meta['tip'] = "Name of projection."

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    projOptions = pyre.inventory.str("proj_options", default="")
    projOptions.meta['tip'] = "Additional proj options."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="projector"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="projector")
    self._createModuleObj()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    self.projection(self.inventory.projection)
    self.units(self.inventory.units)
    self.projOptions(self.inventory.projOptions)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleProjector.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return Projector()


# End of file 
