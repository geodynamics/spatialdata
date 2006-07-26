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

## @file spatialdata/utils/ChangeCoordSys.py
## @brief Python object for changing coordinate system of points.

from pyre.components.Component import Component

# ChangeCoordSys class
class ChangeCoordSys(Component):
  """
  Python object for changing coordinate system of points.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing ChangeCoordSys facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing ConvertMeshVertices facilities
    ## and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b cs_src Source coordinate system
    ## @li \b cs_dest Destination coordinate system

    import pyre.inventory

    from spatialdata.geocoords.CSCart import CSCart

    csSrc = pyre.inventory.facility("cs_src", factory=CSCart)
    csSrc.meta['tip'] = "Source coordinate system."

    csDest = pyre.inventory.facility("cs_dest", factory=CSCart)
    csDest.meta['tip'] = "Destination coordinate system."    


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """
    Initialize converter.
    """
    self.csSrc.initialize()
    self.csDest.initialize()
    return


  def convert(self, points):
    """
    Convert coordinates of vertices.
    """

    self.initialize()
    
    from spatialdata.geocoords.Converter import convert
    convert(points, self.csDest, self.csSrc)
    return


  def __init__(self, name="convertcs"):
    """
    Constructor.
    """
    Converter.__init__(self, name)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members from inventory.
    """
    
    self.csDest = self.inventory.csDest
    self.csSrc = self.inventory.csSrc
    return


# End of file 
