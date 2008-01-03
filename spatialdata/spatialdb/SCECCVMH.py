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

## @file spatialdata/spatialdb/SCECCVMH.py
##
## @brief Python manager for spatial database interface to the SCEC
## CVM-H.
##
## Factory: spatial_database

from SpatialDB import SpatialDB

# SCECCVMH class
class SCECCVMH(SpatialDB):
  """
  Python manager for spatial database to the SCEC CVM-H.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """
    Python object for managing SCECCVMH facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SCECCVMH facilities and properties.
    ##
    ## \b Properties
    ## @li \b dataDir Directory containing SCEC CVM-H data files.
    ## @li \b squash Squash topography/bathymetry to sea level.
    ## @li \b squash_limit Elevation above which topography is squashed.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    dataDir = pyre.inventory.str("data_dir", default=".")
    dataDir.meta['tip'] = "Directory containing SCEC CVM-H data files."

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
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.SCECCVMH()
    self.cppHandle.label = "SCEC CVM-H"
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self)
    self.cppHandle.dataDir(self.dataDir)
    self.cppHandle.squash(self.squash, self.squashLimit.value)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self.dataDir = self.inventory.dataDir
    self.squash = self.inventory.squash
    self.squashLimit = self.inventory.squashLimit
    return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with SCECCVMH.
  """
  return SCECCVMH()


# End of file 
