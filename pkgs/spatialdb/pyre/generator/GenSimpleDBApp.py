#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

## @file spatialdb/pyre/GenSimpleDBApp.py
## @brief Python application to generate simple spatial database.

from pyre.applications.Script import Script

# GenSimpleDBApp class
class GenSimpleDBApp(Script):
  """Python object to generate simple spatial database."""
  
  # INVENTORY //////////////////////////////////////////////////////////
  
  class Inventory(Script.Inventory):
    """Python object for managing GenSimpleDBApp facilities and properties."""
    
    ## @class Inventory
    ## Python object for managing GenSimpleDBApp facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b geometry Object defining geometry of database
    ## @li \b values Object defining values in database
    ## @li \b iohandler Object for writing database

    import pyre.inventory

    from Geometry import Geometry
    geometry = pyre.inventory.facility("geometry", factory=Geometry)
    geometry.meta['tip'] = "Object defining geometry of database."

    from Values import Values
    values = pyre.inventory.facility("values", factory=Values)
    values.meta['tip'] = "Values in database."

    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    iohandler = pyre.inventory.facility("iohandler", factory=SimpleIOAscii)
    iohandler.meta['tip'] = "Object for writing database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def main(self, *args, **kwds):
    self.geometry.load()
    vertices = self.geometry.vertices
    coordsys = self.geometry.coordsys
    for value in self.values.values:
      value.applyFilters(vertices.handle(), vertices.vertexCount, coordsys)
    cppDB = self._assembleDB()
    self.iohandler.initialize()
    self.iohandler.write(cppDB, coordsys)
    return


  def __init__(self, name='gensimpledb'):
    Script.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _assembleDB(self):
    import spatialdata.spatialdb.spatialdb as bindings
    vertices = self.geometry.vertices
    numValues = len(self.values.values)
    cppDB = bindings.CppGenSimpleDB_create(vertices.handle(),
                                           vertices.vertexCount, vertices.dim,
                                           numValues,
                                           self.geometry.topology)
    for i in range(numValues):
      self.values.values[i].setDB(cppDB, i)
    return cppDB


  def _defaults(self):
    Script._defaults(self)
    return


  def _configure(self):
    Script._configure(self)
    self.geometry = self.inventory.geometry
    if not self.inventory.values.name == "dummy":
      self.values = self.inventory.values
    else:
      self.values = []
    self.iohandler = self.inventory.iohandler
    return


  def _init(self):
    Script._init(self)
    return

# version
__id__ = "$Id$"

# End of file 
