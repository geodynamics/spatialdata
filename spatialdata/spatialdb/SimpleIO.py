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
##
## @brief Python I/O manager for simple spatial database (SimpleDB).
##
## Factory: simpledb_io

from pyre.components.Component import Component

# SimpleIO class
class SimpleIO(Component):
  """
  Python I/O manager for simple database (SimpleDB).

  Factory: simpledb_io
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing SimpleIO facilities and properties.
    """

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

  def __init__(self, name="simpleio"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="simpledb_io")
    self.cppHandle = None
    return


  def initialize(self):
    """
    Initialize the database.
    """
    self.cppHandle.filename(self.filename)
    return
    

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members using inventory.
    """
    Component._configure(self)
    self.filename = self.inventory.filename
    return


# FACTORIES ////////////////////////////////////////////////////////////

def simpledb_io():
  """
  Factory associated with SimpleIO.
  """
  return SimpleIO()


# End of file 
