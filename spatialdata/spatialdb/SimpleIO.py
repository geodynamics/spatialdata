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

## @file spatialdata/spatialdb/SimpleIO.py
## @brief Python I/O manager for simple spatial database (SimpleDB).

from pkg_resources import require
require("pythia>=0.8")

from pyre.components.Component import Component

# SimpleIO class
class SimpleIO(Component):
  """Python I/O manager for simple database (SimpleDB)."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing SimpleIO facilities and properties."""

    ## @class Inventory
    ## Python object for managing SimpleIO facilities and properties.
    ##
    ## \b Properties
    ## @li \b filename Name of database file
    ##
    ## \b Facilities
    ## @li None

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="")
    filename.meta['tip'] = "Name of database file."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize the database."""
    self.cppHandle.filename(self.filename)
    return
    

  def __init__(self, name="simpleio"):
    """Constructor."""
    Component.__init__(self, name, facility="simpleio")
    self.cppHandle = None
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Set attributes using inventory."""
    self.filename = self.inventory.filename
    return


# version
__id__ = "$Id$"

# End of file 
