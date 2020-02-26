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

from pyre.applications.Script import Script
from pyre.components.Component import Component


# ----------------------------------------------------------------------------------------------------------------------
def valueFactory(name):
    """
    Factory for values.
    """
    from pyre.inventory import facility
    from Value import Value
    return facility(name, family="database_value", factory=Value)


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

    import pyre.inventory

    from Value import Value
    dbValue = pyre.inventory.facility("value", family="database_value", factory=Value)
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

    import pyre.inventory

    from Geometry import Geometry
    geometry = pyre.inventory.facility("geometry", family="geometry", factory=Geometry)
    geometry.meta['tip'] = "Object defining geometry of region covered by database."

    values = pyre.inventory.facilityArray("values", itemFactory=valueFactory, factory=SingleValue)
    values.meta['tip'] = "Values in database."

    from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
    iohandler = pyre.inventory.facility("iohandler", family="simpledb_io", factory=SimpleIOAscii)
    iohandler.meta['tip'] = "Object for writing database."

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
        self.iohandler.write(data)

# End of file
