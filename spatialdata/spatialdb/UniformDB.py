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
from .spatialdb import UniformDB as ModuleUniformDB


class UniformDB(SpatialDBObj, ModuleUniformDB):
    """
    Spatial database with uniform values.

    Implements `SpatialDB`.
    """
    DOC_CONFIG = {
        "cfg": """
            [db]
            description = Uniform material properties
            values = [density, vp, vs]
            data = [2000*kg/m**3, 2.0*km/s, 1000*m/s]
            """,
    }

    import pythia.pyre.inventory

    values = pythia.pyre.inventory.list("values", default=[])
    values.meta['tip'] = "Names of values in spatial database."

    data = pythia.pyre.inventory.list("data", default=[])
    data.meta['tip'] = "Values in spatial database."

    # PUBLIC METHODS /////////////////////////////////////////////////////

    def __init__(self, name="uniformdb"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)
        from pythia.pyre.units import parser
        self.parser = parser()

    # PRIVATE METHODS ////////////////////////////////////////////////////

    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        self._validateParameters(self.inventory)
        data = []
        units = []
        for x in self.data:
            if len(str(x).split("*")) > 1:
                xdim = self.parser.parse(str(x))
                data.append(float((xdim.value)))
                strDeriv = xdim._strDerivation()
                if len(strDeriv) > 0:
                    units.append(xdim._strDerivation())
                else:
                    units.append("none")
            else:
                data.append(float(x))
                units.append("none")
        values = []
        for v in self.values:
            values.append(v.strip())
        ModuleUniformDB.setData(self, values, units, data)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleUniformDB.__init__(self)
        return

    def _validateParameters(self, params):
        """
        Validate parameters.
        """
        if len(params.values) == 0:
            raise ValueError("Values in UniformDB '%s' not specified.", self.description)
        if len(params.data) == 0:
            raise ValueError("Data for UniformDB '%s' not specified." % self.description)
        if len(params.values) != len(params.data):
            raise ValueError("Incompatible settings for uniform spatial database '%s'.\n"
                             "'values' and 'data' must be lists of the same size.\n"
                             "'values' has size of %d but 'data' has size of %d."
                             % (self.description, len(params.values), len(params.data)))
        try:
            for x in params.data:
                if len(str(x).split("*")) > 1:
                    xdim = self.parser.parse(str(x))
                    dataFloat = float(xdim.value)
                else:
                    dataFloat = float(x)
        except:
            raise ValueError(
                "'data' list for UniformDB '%s' must contain dimensioned or nondimensional values." % self.inventory.label)


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with UniformDB.
    """
    return UniformDB()


# End of file
