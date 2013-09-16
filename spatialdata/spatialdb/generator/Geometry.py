#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/generator/Geometry.py
##
## @brief Python manager for geometry used in generating database.
##
## Factory: geometry.

from pyre.components.Component import Component

# Dummy class for empty component
class Dummy(Component):
  def __init__(self):
    Component.__init__(self, name="dummy", facility="dummy")
    return


# Geometry class
class Geometry(Component):
  """
  Python manager for geometry used in generating database.

  Factory: geometry.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing Geometry facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing Geometry facilities and properties.
    ##
    ## \b Properties
    ## @li \b data_dim Spatial dimension of database locations.
    ##
    ## \b Facilities
    ## @li \b reader Object to read geometry
    ## @li \b coordsys Coordinate system of geometry

    import pyre.inventory

    dataDim = pyre.inventory.int("data_dim", default=2)
    dataDim.validator = pyre.inventory.choice([0, 1, 2, 3])
    dataDim.meta['tip'] = "Spatial dimension of database locations."

    reader = pyre.inventory.facility("reader", family="reader",
                                     factory=Dummy)
    reader.meta['tip'] = "Object to read geometry."

    from spatialdata.geocoords.CSCart import CSCart
    coordsys = pyre.inventory.facility("coordsys", family="coordsys",
                                       factory=CSCart)
    coordsys.meta['tip'] = "Coordinate system for database."
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="geometry"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="geometry")
    self.vertices = None
    return


  def read(self):
    """
    Read geometry.
    """
    self.vertices = self.reader.read()
    self.coordsys.initialize()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    self.dataDim = self.inventory.dataDim
    self.reader = self.inventory.reader
    self.coordsys = self.inventory.coordsys
    return


# FACTORIES ////////////////////////////////////////////////////////////

def geometry():
  """
  Factory associated with Geometry.
  """
  return Geometry()


# End of file
