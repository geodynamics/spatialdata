#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/SpatialDBObj.py
##
## @brief Python abstract base class for spatial database.
##
## Factory: spatial_database

from pyre.components.Component import Component
from spatialdb import SpatialDB as ModuleSpatialDB

# SpatialDBObj class
class SpatialDBObj(Component, ModuleSpatialDB):
  """
  Python abstract base class for spatial database.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing SpatialDBObj facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SpatialDBObj facilities and properties.
    ##
    ## \b Properties
    ## @li \b label Label of database
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    label = pyre.inventory.str("label", default="spatial database")
    label.meta['tip'] = "Label of database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="spatialdb"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="spatial_database")
    self._createModuleObj()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set attributes based on inventory.
    """
    Component._configure(self)
    self.label(self.inventory.label)
    return
  

  def _createModuleObj(self):
    """
    Create Python module object.
    """
    raise NotImplementedError("_createModuleObj() not implemented.")
    return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with SpatialDB.
  """
  # Abstract object (so return None).
  return None


# End of file 
