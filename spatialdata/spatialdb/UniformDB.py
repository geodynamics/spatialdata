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

## @file spatialdata/spatialdb/UniformDB.py
##
## @brief Python manager for spatial database with uniform values.
##
## Factory: spatial_database

from SpatialDB import SpatialDB

# UniformDB class
class UniformDB(SpatialDB):
  """
  Python manager for spatial database with uniform values.

  Factory: spatial_database
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(SpatialDB.Inventory):
    """
    Python object for managing UniformDB facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing UniformDB facilities and properties.
    ##
    ## \b Properties
    ## @li \b values Names of values in spatial database.
    ## @li \b data Values in spatial database.
    ##
    ## \b Facilities
    ## @li none

    import pyre.inventory

    values = pyre.inventory.list("values", default=[])
    values.meta['tip'] = "Names of values in spatial database."

    data = pyre.inventory.list("data", default=[])
    data.meta['tip'] = "Values in spatial database."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="uniformdb"):
    """
    Constructor.
    """
    SpatialDB.__init__(self, name)
    import spatialdb as bindings
    self.cppHandle = bindings.UniformDB()
    return


  def initialize(self):
    """
    Initialize database.
    """
    SpatialDB.initialize(self)
    self.cppHandle.setData(self.values, self.data)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members based on inventory.
    """
    SpatialDB._configure(self)
    self._validate(self.inventory)
    self.values = self.inventory.values
    self.data = map(float, self.inventory.data)
    return


  def _validate(self, data):
    """
    Validate parameters.
    """
    if (len(data.values) != len(data.data)):
      raise ValueError, \
            "Incompatible settings for uniform spatial database '%s'.\n"\
            "'values' and 'data' must be lists of the same size.\n"\
            "'values' has size of %d but 'data' has size of %d." \
            % (self.label, len(self.values), len(self.data))
    try:
      dataFloat = map(float, data.data)
    except:
        raise ValueError, \
              "'data' list must contain floating point values."
    return
  

# FACTORIES ////////////////////////////////////////////////////////////

def spatial_database():
  """
  Factory associated with UniformDB.
  """
  return UniformDB()


# End of file 
