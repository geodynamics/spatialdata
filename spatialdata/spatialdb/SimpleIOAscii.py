# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .SimpleIO import SimpleIO
from .spatialdb import SimpleIOAscii as ModuleSimpleIOAscii


class SimpleIOAscii(SimpleIO, ModuleSimpleIOAscii):
    """
    ASCII writer for a simple spatial database (SimpleDB).

    Implements `SimpleIO`.
    """
    DOC_CONFIG = {
        "cfg": """
            [dbio]
            filename = mat_elastic.spatialdb
            """,
    }

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
        values = numpy.zeros((numLocs, numValues), dtype=numpy.float64)
        i = 0
        for value in data['values']:
            names.append(value['name'])
            units.append(value['units'])
            values[:, i] = value['data'][:]
            i += 1

        from .spatialdb import SimpleDBData
        dbData = SimpleDBData()
        dbData.allocate(numLocs, numValues, spaceDim, dataDim)
        dbData.setCoordinates(data['points'])
        dbData.setData(values)
        dbData.setNames(names)
        dbData.setUnits(units)

        ModuleSimpleIOAscii.write(self, dbData, data['coordsys'])

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        ModuleSimpleIOAscii.setFilename(self, self.filename)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleSimpleIOAscii.__init__(self)


# FACTORIES ////////////////////////////////////////////////////////////

def createWriter(filename):
    writer = SimpleIOAscii()
    writer.setFilename(filename)
    return writer


def simpledb_io():
    """
    Factory associated with SimpleIOAscii.
    """
    return SimpleIOAscii()


# End of file
