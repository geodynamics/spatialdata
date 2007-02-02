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

## @file spatialdata/spatialdb/SpatialDB.py
## @brief Python abstract base class for spatial database.

from pkg_resources import require
require("pythia>=0.8")

from pyre.components.Component import Component

import spatialdb as bindings

# SpatialDB class
class SpatialDB(Component):
  """Python abstract base class for spatial database."""

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
    label.meta['tip'] = "Label of database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize database."""
    self.cppHandle.label = self.label
    return


  def open(self):
    """Open database and prepare for querying."""
    self.cppHandle.open()
    return


  def close(self):
    """Close database."""
    self.cppHandle.close()
    return


  def queryVals(self, names):
    """Set values to return in queries."""
    self.cppHandle.queryVals(names)
    return


  def query(self, locs, cs, numvals):
    """Perform query of db to get values at locations."""
    return self.cppHandle.query(locs, cs.cppHandle, numvals)


  def __init__(self, name="spatialdb"):
    """Constructor."""
    Component.__init__(self, name, facility="spatialdb")
    self.cppHandle = None
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Set attributes based on inventory."""
    self.label = self.inventory.label
    return
  

# version
__id__ = "$Id$"

# End of file 
