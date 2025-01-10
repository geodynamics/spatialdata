# =================================================================================================
# This code is part of SpatialData, developed through the Computational Infrastructure
# for Geodynamics (https://github.com/geodynamics/spatialdata).
#
# Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
# All rights reserved.
#
# See https://mit-license.org/ and LICENSE.md and for license information. 
# =================================================================================================

from .SpatialDBObj import SpatialDBObj
from .spatialdb import SCECCVMH as ModuleSCECCVMH


class SCECCVMH(SpatialDBObj, ModuleSCECCVMH):
    """
    Spatial database for the SCEC CVM-H seismic velocity model versions 5.2 and 5.3.

    Implements `SpatialDB`.
    
    :::{danger}
    These models are obsolete and no longer available from SCEC.
    :::
    """
    DOC_CONFIG = {
        "cfg": """
            data_dir = data/scec-cvmh
            min_vs = 500.0*m/s
            squash = False
            squash_limit = -20.0*km
            """,
    }

    import pythia.pyre.inventory

    dataDir = pythia.pyre.inventory.str("data_dir", default=".")
    dataDir.meta['tip'] = "Directory containing SCEC CVM-H data files."

    from pythia.pyre.units.length import meter
    from pythia.pyre.units.time import second
    minVs = pythia.pyre.inventory.dimensional("min_vs", default=500.0 * meter / second)
    minVs.meta['tip'] = "Minimum shear wave speed."

    squash = pythia.pyre.inventory.bool("squash", default=False)
    squash.meta['tip'] = "Squash topography/bathymetry to sea level."

    from pythia.pyre.units.length import km
    squashLimit = pythia.pyre.inventory.dimensional("squash_limit", default=-2.0 * km)
    squashLimit.meta['tip'] = "Elevation above which topography is squashed."

    def __init__(self, name="sceccvmh"):
        """
        Constructor.
        """
        SpatialDBObj.__init__(self, name)

    def _defaults(self):
        self.description = "SCEC CVM-H v5.3"
    
    def _configure(self):
        """
        Set members based on inventory.
        """
        SpatialDBObj._configure(self)
        ModuleSCECCVMH.setDescription(self, "SCEC CVM-H")
        ModuleSCECCVMH.setDataDir(self, self.dataDir)
        ModuleSCECCVMH.setMinVs(self, self.minVs.value)
        ModuleSCECCVMH.setSquashFlag(self, self.squash, self.squashLimit.value)

    def _createModuleObj(self):
        """
        Create Python module object.
        """
        ModuleSCECCVMH.__init__(self)


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
    """
    Factory associated with SCECCVMH.
    """
    return SCECCVMH()


# End of file
