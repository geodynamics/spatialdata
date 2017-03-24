#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2017 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/SimpleIOAscii.py
##
## @brief Python ascii I/O manager for simple spatial database (SimpleDB).
##
## Factory: simpledb_io

from SimpleIO import SimpleIO
from spatialdb import SimpleIOAscii as ModuleSimpleIOAscii

# SimpleIOAscii class
class SimpleIOAscii(SimpleIO, ModuleSimpleIOAscii):
  """
  Python ascii I/O manager for simple spatial database (SimpleDB).

  Factory: simpledb_io
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpleioascii"):
    """
    Constructor.
    """
    SimpleIO.__init__(self, name)
    return


  def write(self, data):
    """
    Write database to file.

    @param data Dictionary of the following form:
      data = {'points': 2-D array (numLocs, spaceDim),
              'coordsys': Coordinate system associated with locations,
              'data_dim': Dimension of spatial distribution,
              'values': [{'name': Name of value,
                          'units': Units of value,
                          'data': Data for value (numLocs)}]}
    """
    import numpy

    self._validateData(data)

    (numLocs, spaceDim) = data['points'].shape
    dataDim = data['data_dim']
    numValues = len(data['values'])    
    names = []
    units = []
    values = numpy.zeros( (numLocs, numValues), dtype=numpy.float64)
    i = 0
    for value in data['values']:
      names.append(value['name'])
      units.append(value['units'])
      values[:,i] = value['data'][:]
      i += 1

    from spatialdb import SimpleDBData
    dbData = SimpleDBData()
    dbData.allocate(numLocs, numValues, spaceDim, dataDim)
    dbData.coordinates(data['points'])
    dbData.data(values)
    dbData.names(names)
    dbData.units(units)

    ModuleSimpleIOAscii.write(self, dbData, data['coordsys'])
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleSimpleIOAscii.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def simpledb_io():
  """
  Factory associated with SimpleIOAscii.
  """
  return SimpleIOAscii()


# End of file 
