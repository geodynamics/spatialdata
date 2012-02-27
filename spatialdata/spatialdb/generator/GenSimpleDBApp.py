#!/usr/bin/env python
#
# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ======================================================================
#

## @file spatialdata/spatialdb/generator/GenSimpleDBApp.py
##
## @brief Python application to generate simple spatial database from
## other simple spatial databases.

from pyre.applications.Script import Script

# GenSimpleDBApp class
class GenSimpleDBApp(Script):
  """
  Python object to generate simple spatial database.
  """
  
  # INVENTORY //////////////////////////////////////////////////////////
  
  class Inventory(Script.Inventory):
    """
    Python object for managing GenSimpleDBApp facilities and properties.
    """
    
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
    geometry = pyre.inventory.facility("geometry", family="geometry",
                                       factory=Geometry)
    geometry.meta['tip'] = "Object defining geometry of database."

    from Values import Values
    values = pyre.inventory.facility("values", family="database_values",
                                     factory=Values)
    values.meta['tip'] = "Values in database."

    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    iohandler = pyre.inventory.facility("iohandler", family="simpledb_io",
                                        factory=SimpleIOAscii)
    iohandler.meta['tip'] = "Object for writing database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name='gensimpledb'):
    """
    Constructor.
    """
    Script.__init__(self, name)
    return


  def main(self, *args, **kwds):
    """
    Application driver.
    """
    self._info.log("Reading geometry.")
    self.geometry.read()
    points = self.geometry.vertices
    coordsys = self.geometry.coordsys
    data = {'points': points,
            'coordsys': coordsys,
            'data_dim': self.geometry.dataDim,
            'values': []}
    for value in self.values.values:
      self._info.log("Creating value '%s'" % value.name)
      data['values'].append({'name': value.name,
                             'units': value.units,
                             'data': value.calculate(points, coordsys)})
    self._info.log("Writing database.")
    self.iohandler.write(data)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members based on inventory.
    """
    Script._configure(self)
    self.geometry = self.inventory.geometry
    self.values = self.inventory.values
    self.iohandler = self.inventory.iohandler
    return


# End of file 
