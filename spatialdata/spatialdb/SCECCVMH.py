#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/SCECCVMH.py
##
## @brief Python manager for spatial database interface to the SCEC
## CVM-H.
##
## Factory: spatial_database

from SpatialDBObj import SpatialDBObj
from spatialdb import SCECCVMH as ModuleSCECCVMH

# SCECCVMH class
class SCECCVMH(SpatialDBObj, ModuleSCECCVMH):
  """
  Python manager for spatial database to the SCEC CVM-H.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDBObj.Inventory):
    """
    Python object for managing SCECCVMH facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SCECCVMH facilities and properties.
    ##
    ## \b Properties
    ## @li \b data_dir Directory containing SCEC CVM-H data files.
    ## @li \b min_vs Minimum shear wave speed.
    ## @li \b squash Squash topography/bathymetry to sea level.
    ## @li \b squash_limit Elevation above which topography is squashed.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    dataDir = pyre.inventory.str("data_dir", default=".")
    dataDir.meta['tip'] = "Directory containing SCEC CVM-H data files."

    from pyre.units.length import meter
    from pyre.units.time import second
    minVs = pyre.inventory.dimensional("min_vs", default=500.0*meter/second)
    minVs.meta['tip'] = "Minimum shear wave speed."

    squash = pyre.inventory.bool("squash", default=False)
    squash.meta['tip'] = "Squash topography/bathymetry to sea level."

    from pyre.units.length import km
    squashLimit = pyre.inventory.dimensional("squash_limit",
                                             default=-2.0*km)
    squashLimit.meta['tip'] = "Elevation above which topography is squashed."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="sceccvmh"):
    """
    Constructor.
    """
    SpatialDBObj.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDBObj._configure(self)
    self.label("SCEC CVM-H")
    self.dataDir(self.inventory.dataDir)
    self.minVs(self.inventory.minVs.value)
    self.squash(self.inventory.squash, self.inventory.squashLimit.value)
    return


  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleSCECCVMH.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with SCECCVMH.
  """
  return SCECCVMH()


# End of file 
