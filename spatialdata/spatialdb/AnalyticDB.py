# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================


from .SpatialDBObj import SpatialDBObj
from .spatialdb import AnalyticDB as ModuleAnalyticDB


class AnalyticDB(SpatialDBObj, ModuleAnalyticDB):
    """
    Spatial database composed of analytic functions.

    Implements `SpatialDB`.
    """
    DOC_CONFIG = {
        "cfg": """
            [db]
            description = Uniform material properties
            values = [density, vp, vs]
            units = [kg/m**3, km/s, m/s]
            expressions = [2.0*x-y, 2.0x*x/(y*y), -2.0*z]
            cs = spatialdata.geocoords.CSCart
            cs.space_dim = 3
            """,
    }

    import pythia.pyre.inventory

    values = pythia.pyre.inventory.list("values", default=[])
    values.meta['tip'] = "Names of values in spatial database."

    units = pythia.pyre.inventory.list("units", default=[])
    units.meta['tip'] = "Units for values in spatial database."

    expressions = pythia.pyre.inventory.list("expressions", default=[])
    expressions.meta['tip'] = "Analytical expressions for values in spatial database."

    from spatialdata.geocoords.CSCart import CSCart
    cs = pythia.pyre.inventory.facility("coordsys", factory=CSCart)
    cs.meta['tip'] = "Coordinate system."

    def __init__(self, name="AnalyticDB"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)
        from pythia.pyre.units import parser
        self.parser = parser()

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        self._validateParameters(self.inventory)
        self.cs._configure()
        ModuleAnalyticDB.setCoordSys(self, self.cs)
        values = []
        for v in self.values:
            values.append(v.strip())
        ModuleAnalyticDB.setData(self, values, self.units, self.expressions)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleAnalyticDB.__init__(self)

    def _validateParameters(self, params):
        """
        Validate parameters.
        """
        if len(params.values) == 0:
            raise ValueError("Values in AnalyticDB '%s' not specified.", self.description)
        if len(params.units) == 0:
            raise ValueError("Units for AnalyticDB '%s' not specified." % self.description)
        if len(params.expressions) == 0:
            raise ValueError("Analytical expressions for AnalyticDB '%s' not specified." % self.description)
        if len(params.values) != len(params.units or len(params.values) != len(params.expressions)):
            raise ValueError("Incompatible settings for uniform spatial database '%s'.\n"
                             "'values', 'units', and 'expressions' must be lists of the same size.\n"
                             "Size of 'values'=%d, 'units'=%d, and 'expressions'=%d."
                             % (self.description, len(params.values), len(params.units), len(params.expressions)))
        try:
            for x in params.units:
                if len(str(x).split("*")) > 1:
                    xdim = self.parser.parse(str(x))
        except:
            raise ValueError(
                "'units' for AnalyticDB '%s' must contain dimensioned or nondimensional values." % self.description)


def spatial_database():
    """
    Factory associated with AnalyticDB.
    """
    return AnalyticDB()


# End of file
