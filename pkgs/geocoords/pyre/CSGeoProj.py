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

## @file geocoords/pyre/CSGeoProj.py
## @brief Python manager for geographic coordinate systems.

from CSGeo import CSGeo

# CoordSysGeo class
class CSGeoProj(CSGeo):
  """Python manager for projected geographic coordinate systems."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(CSGeo.Inventory):
    """Python object for managing CSGeoProj facilities and properties."""

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
    projector = pyre.inventory.facility("projector", factory=Projector)
    projector.meta['tip'] = "Geographic coordinate projector."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def initialize(self):
    """Initialize coordinate system."""

    import spatialdata.geocoords.geocoords as bindings
    bindings.CppCSGeoProj_projector(self._cppCoordSys,
                                    self.projector.handle())

    CoordSys.initialize()
    return


  def __init__(self, name="csgeoproj"):
    """Constructor."""
    CSGeo.__init__(self, name)

    import spatialdata.geocoords.geocoords as bindings
    self._cppCoordSys = bindings.CppCSGeoProj()
    self.projector = None
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """Setup members using inventory."""

    self.projector = self.inventory.projector
    return


# version
__id__ = "$Id$"

# End of file 
