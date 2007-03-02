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

## @file spatialdata/geocoords/CSGeoProj.py
##
## @brief Python manager for geographic coordinate systems.
##
## Factory: CSGeoProj

from CSGeo import CSGeo

# CoordSysGeo class
class CSGeoProj(CSGeo):
  """
  Python manager for projected geographic coordinate systems.

  Factory: CSGeoProj
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """
    Python object for managing CSGeoProj facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing CSGeoProj facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b projector Geographic coordinate projector

    import pyre.inventory

    from Projector import Projector
    projector = pyre.inventory.facility("projector", family="projector",
                                        factory=Projector)
    projector.meta['tip'] = "Geographic coordinate projector."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="csgeoproj"):
    """
    Constructor.
    """
    CSGeo.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self.cppHandle = bindings.CSGeoProj()
    self.projector = None
    return


  def initialize(self):
    """
    Initialize coordinate system.
    """
    self.projector.initialize(self)
    self.cppHandle.projector = self.projector.cppHandle

    CSGeo.initialize(self)
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    CSGeo._configure(self)
    self.projector = self.inventory.projector
    return


# FACTORIES ////////////////////////////////////////////////////////////

def coordsys():
  """
  Factory associated with CoordSys.
  """
  return CSGeoProj()


# End of file 
