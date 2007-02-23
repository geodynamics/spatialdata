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

## @file spatialdata/spatialdb/generator/SimpleDBCreator.py

## @brief Python object for creating a SimpleDB file.

# SimpleDBCreator class
class SimpleDBCreator(object):
  """
  Python object for creating a SimpleDB file.
  """

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def create(self, filename, values, units, coords, data, dataDim, cs):
    """
    Create database file.
    """
    self._validate(values, units, coords, data)
    (numLocs, spaceDim) = coords.shape
    numValues = len(values)
    
    import spatialdb.spatialdb.generator.generator as bindings
    cppData = bindings.createData(values, units, coords, data, dataDim)

    # Create SimpleIOAscii object
    # Write database file
    return
  

  def __init__(self):
    """
    Constructor.
    """
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _validate(values, units, coords, data):
    """
    Check consistency of dimensions.
    """
    msg = ""
    numValues = len(values)
    if numValues != len(units):
      msg += "Number of values given in 'values' and 'units' do not match."
    (numLocs, spaceDim) = coords.shape
    (dataLocs, dataValues) = data.shape
    if numLocs != dataLocs:
      msg += "Number of locations in 'coords' and 'data' do not match."
    if numValues != dataValues:
      msg += "Number of values in 'values' and 'data' do not match."
    if msg != "":
      raise ValueError(msg)
    return



# End of file 
