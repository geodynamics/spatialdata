# ======================================================================
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2022 University of California, Davis
#
# See LICENSE.md for license information.
#
# ======================================================================

from pythia.pyre.applications.Script import Script
from pythia.pyre.components.Component import Component

from .Value import Value


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


class SingleValue(Component):
    """
    Container with one value.
    """

    import pythia.pyre.inventory
    dbValue = pythia.pyre.inventory.facility("value", family="database_value", factory=Value)
    dbValue.meta['tip'] = "Value in spatial database."

    def __init__(self, name="siglevalue"):
        """
        Constructor.
        """
        Component.__init__(self, name, facility="database_value")


class GenSimpleDBApp(Script):
    """
    Application to generate simple spatial database.
    """
    DOC_CONFIG = {
        "cfg": """
            # Create a spatial dabaset with values `Vp` and `Vs`.
            #
            # Vp is generated from a background value given in `vp_background.spatialdb`
            # plus a perturbation given in `vp_perturbation.spatialdb`.
            # 
            # Vs is generatef from a backgorund value given in `vs_background.spatialdb`
            # multiplied by a value given in `vs_scaling.spatialdb`.
            [gensimpledb.geometry]
            reader = read_geometry
            data_dim = 2
            coordsys.space_dim = 2

            [gensimpledb]
            values = [vp, vs]

            [gensimpledb.values.vp]
            name = Vp
            units = m/s
            shapers = [bg, add]

            [gensimpledb.values.vp.shapers.bg]
            default = 0.0
            operand = add
            db_value = Vp
            db.description = Background
            db.query_type = linear
            db.iohandler.filename = vp_background.spatialdb

            [gensimpledb.values.vp.shapers.add]
            default = 1.0
            operand = add
            db_value = Vp
            db.description = Add
            db.query_type = linear
            db.iohandler.filename = vp_perturbation.spatialdb

            [gensimpledb.values.vs]
            name = Vs
            units = m/s
            shapers = [bg, multiply]

            [gensimpledb.values.vs.shapers.bg]
            default = 0.0
            operand = add
            db_value = Vs
            db.description = Background
            db.query_type = linear
            db.iohandler.filename = vs_background.spatialdb

            [gensimpledb.values.vs.shapers.add]
            default = 1.0
            operand = multiply
            db_value = Vs
            db.description = Multiply
            db.query_type = linear
            db.iohandler.filename = vs_scaling.spatialdb
            """
    }

    import pythia.pyre.inventory

    from .Geometry import Geometry
    geometry = pythia.pyre.inventory.facility("geometry", family="geometry", factory=Geometry)
    geometry.meta['tip'] = "Object defining geometry of region covered by database."

    values = pythia.pyre.inventory.facilityArray("values", itemFactory=valueFactory, factory=SingleValue)
    values.meta['tip'] = "Values in database."

    filename = pythia.pyre.inventory.str("filename", default="", validator=validateFilename)
    filename.meta['tip'] = "Filename for generated ASCII SimpleDB."


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
