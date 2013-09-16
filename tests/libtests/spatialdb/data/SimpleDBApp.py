#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file tests/libtests/spatialdb/data/SimpleDBApp.py

## @brief Python application for generating C++ data files for testing
## C++ SimpleDB objects.

from pyre.applications.Script import Script

# SimpleDBApp class
class SimpleDBApp(Script):
  """
  Python application for generating C++ data files for testing C++
  SimpleDB objects.
  """
  
  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Script.Inventory):
    """Python object for managing SimpleDBApp facilities and properties."""

    ## @class Inventory
    ## Python object for managing SimpleDBApp facilities and properties.
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

  def __init__(self, name="simpledbapp"):
    """
    Constructor.
    """
    Script.__init__(self, name)

    # Database information
    self.numLocs = None
    self.spaceDim = None
    self.numVals = None
    self.dataDim = None
    self.dbData = None
    self.dbCords = None
    self.names = None
    self.units = None

    # Query information
    self.numQueries = None
    self.queryNearest = None
    self.queryLinear = None
    self.errFlags = None

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

    self.data.addScalar(vtype="int", name="_numQueries",
                        value=self.numQueries, format="%d")
    self.data.addArray(vtype="double", name="_queryNearest",
                       values=self.queryNearest,
                       format="%16.8e", ncols=self.spaceDim+self.numVals)
    self.data.addArray(vtype="double", name="_queryLinear",
                       values=self.queryLinear,
                       format="%16.8e", ncols=self.spaceDim+self.numVals)
    self.data.addArray(vtype="int", name="_errFlags",
                       values=self.errFlags,
                       format="%2d", ncols=self.spaceDim+self.numQueries)
      
    return

  
# End of file 
