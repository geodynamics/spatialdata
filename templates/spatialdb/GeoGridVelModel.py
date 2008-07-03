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

# 1. Rename the MyVelModel class to something appropriate (do a
#    search/replace on MyVelModel).
# 2. Add the necessary Pyre properties and facilities for user parameters.
# 3. Update the constructor, __init__().
# 4. Update initialize().
# 5. Update _configure().

## @brief Python manager for spatial database interface to a new velocity
## model.
##
## Factory: spatial_database

from spatialdata.spatialdb.SpatialDB import SpatialDB

# MyVelModel class
class MyVelModel(SpatialDB):
  """
  Python manager for spatial database to a new velocity model.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """
    Python object for managing MyVelModel facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing MyVelModel facilities and properties.
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
  def __init__(self, name="myvelmodel"):
    """
    Constructor.
    """
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.MyVelModel() # Change this
    self.cppHandle.label = "My velocity model" # Change this
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self)

    # Transfer Pyre properties/facilities to C++
    self.cppHandle.filename(self.filename)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    # Transfer inventory to object
    self.filename = self.inventory.filename
    return


# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with MyVelModel.
  """
  return MyVelModel()


# End of file 
