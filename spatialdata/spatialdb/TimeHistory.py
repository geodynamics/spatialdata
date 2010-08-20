#!/usr/bin/env python
#
# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

## @file spatialdata/spatialdb/TimeHistory.py
##
## @brief Python object for time history dependence with spatial databases.
##
## Factory: temporal_database

from pyre.components.Component import Component
from spatialdb import TimeHistory as ModuleTimeHistory

# TimeHistory class
class TimeHistory(Component, ModuleTimeHistory):
  """
  Python object for time history dependence with spatial databases.

  \b Properties
  @li \b label Label for time history.
  @li \b filename Name of file for time history.
  
  \b Facilities
  @li None

  Factory: temporal_database
  """

  import pyre.inventory

  label = pyre.inventory.str("label", default="temporal database")
  label.meta['tip'] = "Label for time history."

  filename = pyre.inventory.str("filename", default="timehistory.timedb")
  filename.meta['tip'] = "Name of file for time history."


  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="timehistory"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="temporal_database")
    self._createModuleObj()
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set attributes based on inventory.
    """
    Component._configure(self)
    ModuleTimeHistory.label(self, self.inventory.label)
    ModuleTimeHistory.filename(self, self.inventory.filename)
    return
  

  def _createModuleObj(self):
    """
    Create Python module object.
    """
    ModuleTimeHistory.__init__(self)
    return


# FACTORIES ////////////////////////////////////////////////////////////

def temporal_database():
  """
  Factory associated with TimeHistory.
  """
  return TimeHistory()


# End of file 
