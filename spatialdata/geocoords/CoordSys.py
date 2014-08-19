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

## @file spatialdata/geocoords/CoordSys.py
##
## @brief Python manager for coordinate systems.
##
## Factory: coordsys

from pyre.components.Component import Component

# CoordSys class
class CoordSys(Component):
  """
  Python manager for coordinate systems.

  Factory: coordsys
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing CoordSys facilities and properties."""

    ## @class Inventory
    ## Python object for managing CoordSys facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li None

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="coordsys"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="coordsys")
    self._createModuleObj()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    raise NotImplementedError("_createModuleObj() not implemented.")
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CoordSys()


# End of file 
