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

## @file pyre/SimpleIO.py
## @brief Python I/O manager for simple spatial database (SimpleDB).

from pyre.components.Component import Component

# SimpleIO class
class SimpleIO(Component):
  """Python I/O manager for simple database (SimpleDB)."""

  def initialize(self):
    """Initialize the database."""
    import spatialdata as bindings
    bindings.CppSimpleIO_Filename(self._cppSimpleIO,
                                  self.inventory.filename)
    return
    
  def handle(self):
    """Get handle to C++ object."""
    return self._cppSimpleIO

  def __init__(self, name="simpleio"):
    """Constructor."""
    Component.__init__(self, name, facility="simpleio")
    self._cppSimpleIO = None
    return

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

# version
__id__ = "$Id: SimpleIO.py,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $"

# End of file 
