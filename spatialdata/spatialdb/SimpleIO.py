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

## @file spatialdata/spatialdb/SimpleIO.py
##
## @brief Python I/O manager for simple spatial database (SimpleDB).
##
## Factory: simpledb_io

from pyre.components.Component import Component

# Validator for filename
def validateFilename(value):
  """
  Validate filename.
  """
  if 0 == len(value):
    raise ValueError("Filename for spatial database not specified.")
  return value


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

    filename = pyre.inventory.str("filename", default="", 
                                  validator=validateFilename)
    filename.meta['tip'] = "Name of database file."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpleio"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="simpledb_io")
    self._createModuleObj()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members using inventory.
    """
    try:
      Component._configure(self)
      self.filename(self.inventory.filename)
    except ValueError, err:
      aliases = ", ".join(self.aliases)
      raise ValueError("Error while configuring spatial database reader "
                       "(%s):\n%s" % (aliases, err.message))
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    raise NotImplementedError("_createModuleObj() not implemented.")
    return


  def _validateData(self, data):
    """
    Check consistency of database data.
    """
    (numLocs, spaceDim) = data['points'].shape
    cs = data['coordsys']
    if spaceDim != cs.spaceDim():
      raise ValueError, \
          "Simple database space-dim (%d) does not agree with spatial "\
          "dimension of coordinate system (%d)." % \
          (spaceDim, cs.spaceDim())
    return


# FACTORIES ////////////////////////////////////////////////////////////

def simpledb_io():
  """
  Factory associated with SimpleIO.
  """
  return SimpleIO()


# End of file 
