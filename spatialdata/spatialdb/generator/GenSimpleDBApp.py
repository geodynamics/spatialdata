# ======================================================================
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
# ======================================================================
#

# @file spatialdata/spatialdb/generator/GenSimpleDBApp.py
#
# @brief Python application to generate simple spatial database from
# other simple spatial databases.

from pythia.pyre.applications.Script import Script
from pythia.pyre.components.Component import Component

from .Value import Value


# ----------------------------------------------------------------------------------------------------------------------
def valueFactory(name):
    """
    Factory for values.
    """
    from pythia.pyre.inventory import facility
    return facility(name, family="database_value", factory=Value)


def validateFilename(value):
    """
    Validate filename.
    """
    if 0 == len(value):
        raise ValueError("Filename for spatial database not specified.")
    return value


# ----------------------------------------------------------------------------------------------------------------------
class SingleValue(Component):
    """
    Python container with one value.

    INVENTORY

    Properties
      - None

    Facilities
      - *value* Spatial database value.
    """

    import pythia.pyre.inventory
    dbValue = pythia.pyre.inventory.facility("value", family="database_value", factory=Value)
    dbValue.meta['tip'] = "Value in spatial database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="siglevalue"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="database_value")


# ----------------------------------------------------------------------------------------------------------------------
class GenSimpleDBApp(Script):
    """
    Python object to generate simple spatial database.

    INVENTORY

    Properties
      - None

    Facilities
      - *geometry* Geometry of region covered by spatial database.
      - *values* Values in spatial database.
      - *iohandler* Writer for spatial database.
    """

    import pythia.pyre.inventory

    from .Geometry import Geometry
    geometry = pythia.pyre.inventory.facility("geometry", family="geometry", factory=Geometry)
    geometry.meta['tip'] = "Object defining geometry of region covered by database."

    values = pythia.pyre.inventory.facilityArray("values", itemFactory=valueFactory, factory=SingleValue)
    values.meta['tip'] = "Values in database."

    filename = pythia.pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Filename for generated ASCII SimpleDB."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name='gensimpledb'):
        """
        Constructor.
        """
        Script.__init__(self, name)

    def main(self, *args, **kwds):
        """
        Application driver.
        """
        from spatialdata.spatialdb.SimpleIOAscii import createWriter

        self._info.log("Reading geometry.")
        self.geometry.read()
        points = self.geometry.vertices
        coordsys = self.geometry.coordsys
        data = {
            'points': points,
            'coordsys': coordsys,
            'data_dim': self.geometry.dataDim,
            'values': [],
        }
        for value in self.values.components():
            self._info.log("Creating value '%s'" % value.name)
            data['values'].append({
                'name': value.vname,
                'units': value.units,
                'data': value.calculate(points, coordsys),
            })
        self._info.log("Writing database.")
        writer = createWriter(self.filename)
        writer.write(data)

# End of file
