#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file tests/libtests/spatialdb/data/SimpleDBQueryApp.py

## @brief Python application for generating C++ data files for testing
## C++ SimpleDBQuery objects.

from pyre.applications.Script import Script

# SimpleDBQueryApp class
class SimpleDBQueryApp(Script):
  """
  Python application for generating C++ data files for testing C++
  SimpleDBQuery objects.
  """
  
  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Script.Inventory):
    """
    Python object for managing SimpleDBQueryApp facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing SimpleDBQueryApp facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b data Data manager.

    import pyre.inventory

    from spatialdata.utils.CppData import CppData
    data = pyre.inventory.facility("data", factory=CppData)
    data.meta['tip'] = "Data manager."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="simpledbqueryapp"):
    """
    Constructor.
    """
    Script.__init__(self, name)

    # Database information
    self.numLocs = None
    self.spaceDim = None
    self.numVals = None
    self.dataDim = None
    self.dbCoords = None
    self.dbData = None
    self.names = None
    self.units = None

    # Query information
    self.numPts = None
    self.coords = None
    self.dist2 = None
    self.area = None
    self.areaDir = None
    self.volume = None

    return


  def main(self):
    """
    Run the application.
    """
    self._compute()
    self._initData()
    self.data.write(self.name)
    return
  

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members using inventory.
    """
    Script._configure(self)
    self.data = self.inventory.data
    return


  def _compute(self):
    """
    Compute query data.
    """
    raise NotImplementedError
    return


  def _initData(self):
    self.data.addScalar(vtype="int", name="_numLocs", value=self.numLocs,
                        format="%d")
    self.data.addScalar(vtype="int", name="_spaceDim", value=self.spaceDim,
                        format="%d")
    self.data.addScalar(vtype="int", name="_numVals", value=self.numVals,
                        format="%d")
    self.data.addScalar(vtype="int", name="_dataDim", value=self.dataDim,
                        format="%d")
    self.data.addArray(vtype="double", name="_dbCoords", values=self.dbCoords,
                       format="%16.8e", ncols=self.spaceDim)
    self.data.addArray(vtype="double", name="_dbData", values=self.dbData,
                       format="%16.8e", ncols=self.numVals)
    self.data.addArray(vtype="char*", name="_names", values=self.names,
                       format="\"%s\"", ncols=1)
    self.data.addArray(vtype="char*", name="_units", values=self.units,
                       format="\"%s\"", ncols=1)

    self.data.addScalar(vtype="int", name="_numPts",
                        value=self.numPts, format="%d")
    self.data.addArray(vtype="double", name="_coords",
                       values=self.coords,
                       format="%16.8e", ncols=self.spaceDim)
    self.data.addScalar(vtype="double", name="_dist2",
                        value=self.dist2, format="%16.8e")
    self.data.addScalar(vtype="double", name="_area",
                        value=self.area, format="%16.8e")
    self.data.addArray(vtype="double", name="_areaDir",
                       values=self.areaDir,
                       format="%16.8e", ncols=self.numPts)
    self.data.addScalar(vtype="double", name="_volume",
                        value=self.volume, format="%16.8e")
    return


# End of file
