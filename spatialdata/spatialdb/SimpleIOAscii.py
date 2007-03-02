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

## @file spatialdata/spatialdb/SimpleIOAscii.py
##
## @brief Python ascii I/O manager for simple spatial database (SimpleDB).
##
## Factory: simpledb_io

from SimpleIO import SimpleIO

import numpy

# SimpleIOAscii class
class SimpleIOAscii(SimpleIO):
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
    import spatialdb as bindings
    self.cppHandle = bindings.SimpleIOAscii()
    return


  def write(self, data):
    """
    Write database to file.

    @param data Dictionary of the following form:
      data = {'locs': 2-D array (numLocs, spaceDim),
              'coordsys': Coordinate system associated with locations,
              'data_dim': Dimension of spatial distribution,
              'values': [{'name': Name of value,
                          'units': Units of value,
                          'data': Data for value (numLocs)}]}
    """
    names = []
    units = []
    (numLocs, spaceDim) = data['locs'].shape
    dataDim = data['data_dim']
    numValues = len(data['values'])
    dbData = numpy.zeros( (numLocs, spaceDim+numValues), dtype=numpy.float64)
    dbData[:,0:spaceDim] = data['locs'][:]
    i = spaceDim
    for value in data['values']:
      names.append(value['name'])
      units.append(value['units'])
      dbData[:,i] = value['data'][:]
      i += 1
    cs = data['coordsys']
    self.cppHandle.write(names, units, dbData, spaceDim, dataDim, cs.cppHandle)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def simpledb_io():
  """
  Factory associated with SimpleIOAscii.
  """
  return SimpleIOAscii()


# End of file 
