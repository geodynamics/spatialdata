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

## @file spatialdata/geocoords/CSCart.py
##
## @brief Python manager for Cartesian coordinate systems.
##
## Factory: coordsys.

from CoordSys import CoordSys
from geocoords import CSCart as ModuleCSCart

# CSCart class
class CSCart(CoordSys, ModuleCSCart):
  """
  Python manager for Cartesian coordinate systems.

  Factory: coordsys.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CoordSys.Inventory):
    """
    Python object for managing CSCart facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CSCart facilities and properties.
    ##
    ## \b Properties
    ## @li \b units Name of units
    ## @li \b space_dim Number of dimensions for coordinate system
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    units = pyre.inventory.str("units", default="m")
    units.meta['tip'] = "Units of coordinates."

    spaceDim = pyre.inventory.int("space_dim", default=3)
    spaceDim.meta['tip'] = "Number of dimensions for coordinate system."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="cscart"):
    """
    Constructor.
    """
    CoordSys.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CoordSys._configure(self)

    import pyre.units
    uparser = pyre.units.parser()
    coordUnits = uparser.parse(self.inventory.units)
    self.toMeters(coordUnits.value)
    self.setSpaceDim(self.inventory.spaceDim)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleCSCart.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSCart()


# End of file 
