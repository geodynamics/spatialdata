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

## @file spatialdata/spatialdb/generator/Filter.py

## @brief Python manager for shaping spatial distribution of data
## while generating database.

from pyre.components.Component import Component

import numpy

# Filter class
class Filter(Component):
  """
  Python manager for shaping spatial distribution of data while
  generating database.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Component.Inventory):
    """
    Python object for managing Filter facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing Filter facilities and properties.
    ##
    ## \b Properties
    ## @li \b db_value Name of value in supplied spatial database filter
    ## @li \b operand Operand to use in applying filter
    ##
    ## \b Facilities
    ## @li \b db Database containing value defining filter

    import pyre.inventory

    default = pyre.inventory.float("default", default=0.0)
    default.meta['tip'] = "Default value for filter."

    dbValue = pyre.inventory.str("db_value", default="")
    dbValue.meta['tip'] = "Name of value supplied in filter spatial database."
    
    operand = pyre.inventory.str("operand", default="multiply")
    operand.validator = pyre.inventory.choice(["add", "subtract", 
                                               "multiply", "divide"])
    operand.meta['tip'] = "Operand to use in applying filter."

    from spatialdata.spatialdb.SimpleDB import SimpleDB
    db = pyre.inventory.facility("db", factory=SimpleDB)
    db.meta['tip'] = "Database containing value defining filter."
    

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def __init__(self, name="filter"):
    """
    Constructor.
    """
    Component.__init__(self, name, facility="filter")
    return


  def initialize(self):
    """
    Initialize filter.
    """
    self.db.initialize()
    self.db.open()
    return


  def finalize(self):
    """
    Cleanup.
    """
    self.db.close()
    return


  def apply(self, value, locs, cs):
    """
    Apply filter to data.
    """
    self.db.queryVals([self.dbValue])
    (vals, err) = self.db.query(locs, cs, numvals=1)
    vals = numpy.reshape(numpy.array(vals), -1)
    err = numpy.array(err)
    default = self.defaultValue*numpy.ones( vals.shape, dtype=numpy.float64)
    mask = numpy.zeros( vals.shape, dtype=numpy.float64)
    mask[err[:] != 0] = 1.0
    vals[:] += default[:]*mask[:]

    if self.operand == "add":
      value[:] += vals[:]
    elif self.operand == "subtract":
      value[:] -= vals[:]
    elif self.operand == "multiply":
      value[:] *= vals[:]
    elif self.operand == "divide":
      value[:] /= vals[:]
    else:
      raise ValueError, \
            "Unknown operand setting '%s'." % self.operand
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Setup members using inventory.
    """
    Component._configure(self)
    if self.inventory.dbValue == "":
      raise ValueError, \
            "Name of value in spatial database must be set for Filter '%s'." %\
            self.name
    self.dbValue = self.inventory.dbValue
    self.operand = self.inventory.operand
    self.db = self.inventory.db
    self.defaultValue = self.inventory.default
    return


# End of file 
