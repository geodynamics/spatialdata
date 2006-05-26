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

## @file spatialdata/spatialdb/generator/Geometry.py
## @brief Python manager for geometry used in generating database.

from pyre.components.Component import Component

# Dummy class for empty component
class Dummy(Component):
  def __init__(self):
    Component.__init__(self, name="dummy", facility="dummy")
    return


# Geometry class
class Geometry(Component):
  """Python manager for geometry used in generating database."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """Python object for managing Geometry facilities and properties."""

    ## @class Inventory
    ## Python object for managing Geometry facilities and properties.
    ##
    ## \b Properties
    ## @li \b topology Topology of the database
    ##
    ## \b Facilities
    ## @li \b unpickler Object to unpickle geometry
    ## @li \b coordsys Coordinate system of geometry

    import pyre.inventory

    topology = pyre.inventory.str("topology", default="area")
    topology.validator = pyre.inventory.choice(["point", "line",
                                                "area", "volume"])
    topology.meta['tip'] = "Topology of the database."

    unpickler = pyre.inventory.facility("unpickler", factory=Dummy)
    unpickler.meta['tip'] = "Object to unpickle geometry."

    from spatialdata.geocoords.CoordSys import CoordSys
    coordsys = pyre.inventory.facility("coordsys", factory=CoordSys)
    coordsys.meta['tip'] = "Coordinate system for database."
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def load(self):
    mesh = self.unpickler.load()
    self.vertices = mesh.vertices()
    self.coordsys.initialize()
    return


  def __init__(self, name="geometry"):
    """Constructor."""
    Component.__init__(self, name, facility="geometry")
    self.vertices = None
    return


  def _configure(self):
    Component._configure(self)
    self.topology = self.inventory.topology
    self.unpickler = self.inventory.unpickler
    self.coordsys = self.inventory.coordsys
    return


# version
__id__ = "$Id$"

# End of file 
