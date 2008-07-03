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

# 1. Rename the GeoGridVelModel class to something appropriate.
# 2. Adjust the Pyre properties and facilities for user parameters.
# 3. Update the constructor, __init__().
# 4. Update initialize().
# 5. Update _configure().

## @brief Python manager for spatial database interface to a new velocity
## model.
##
## Factory: spatial_database

from spatialdata.spatialdb.SpatialDB import SpatialDB

# GeoGridVelModel class
class GeoGridVelModel(SpatialDB):
  """
  Python manager for spatial database to a new velocity model.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """
    Python object for managing GeoGridVelModel facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing GeoGridVelModel facilities and properties.
    ##
    ## \b Properties
    ## @li \b filename Filename for seismic velocity model.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    filename = pyre.inventory.str("filename", default="model.txt")
    filename.meta['tip'] = "Filename for seismic velocity model."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  # Change this name.
  def __init__(self, name="geogridvelmodel"):
    """
    Constructor.
    """
    SpatialDB.__init__(self, name) # Call parent function

    # Create handle to corresponding C++ object
    import spatialdb as bindings
    self.cppHandle = bindings.GeoGridVelModel()
    self.cppHandle.label = "Geographic gridded velocity model"
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self) # Call parent function

    # Transfer Pyre properties/facilities to C++
    self.cppHandle.filename(self.filename)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self) # Call parent function.
    
    # Transfer inventory to object
    self.filename = self.inventory.filename
    return


# FACTORIES ////////////////////////////////////////////////////////////

# Factory used when setting GeoGridVelModel to a Pyre
# 'spatial_database' facility.
def spatial_database():
  """
  Factory associated with GeoGridVelModel.
  """
  return GeoGridVelModel()


# End of file 
