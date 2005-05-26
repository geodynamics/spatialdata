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

## @file pyre/SpatialDB.py
## @brief Python manager for spatial database.

from pyre.components.Component import Component

import spatialdb as bindings

# SpatialDB class
class SpatialDB(Component):
  """Python manager for spatial database."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing SpatialDB facilities and properties."""

    ## @class Inventory
    ## Python object for managing SpatialDB facilities and properties.
    ##
    ## \b Properties
    ## @li \b label Label of database
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    label = pyre.inventory.str("label", default="spatial database")

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def handle(self):
    """Get handle to C++ object."""
    return self._cppSpatialDB

  def initialize(self):
    """Initialize database."""
    bindings.CppSpatialDB_Label(self._cppSpatialDB, self.inventory.label)
    return

  def open(self):
    """Open database and prepare for querying."""
    bindings.CppSpatialDB_Open(self._cppSpatialDB)
    return

  def close(self):
    """Close database."""
    bindings.CppSpatialDB_Close(self._cppSpatialDB)
    return

  def queryVals(self, names):
    """Set values to return in queries."""
    bindings.CppSpatialDB_QueryVals(self._cppSpatialDB, names)
    return

  def __init__(self, name="spatialdb"):
    """Constructor."""
    Component.__init__(self, name, facility="spatialdb")
    self._cppSpatialDB = None
    return

# version
__id__ = "$Id: SpatialDB.py,v 1.1 2005/05/25 18:43:00 baagaard Exp $"

# End of file 
