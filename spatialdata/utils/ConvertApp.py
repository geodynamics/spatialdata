#!/usr/bin/env python
#
# ======================================================================
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ======================================================================
#

## @file spatialdata/utils/pyconvert.py
## @brief Python convert application driver

from pyre.components.Component import Component
# Dummy class for empty component
class Dummy(Component):
  def __init__(self):
    Component.__init__(self, name="dummy", facility="dummy")
    return

from pyre.applications.Script import Script
# ConvertApp class
class ConvertApp(Script):
  """
  Python Convert application driver.
  """

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Script.Inventory):
    """
    Python object for managing ConvertApp facilities and properties.
    """

    ## @class Inventory
    ## Python object for managing ConvertApp facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b unpickler Unpickler to load data
    ## @li \b converter Converter to convert data
    ## @li \b pickler Pickler to dump data

    import pyre.inventory

    reader = pyre.inventory.facility("reader", factory=Dummy)
    reader.meta['tip'] = "Reader to load data."

    converter = pyre.inventory.facility("converter", factory=Dummy)
    converter.meta['tip'] = "Converter to convert data."

    writer = pyre.inventory.facility("writer", factory=Dummy)
    writer.meta['tip'] = "Writer to dump data."

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def main(self, *args, **kwds):
    """
    Main entry point for application.
    """
    data = self.reader.read()
    if not self.converter is None:
      self.converter.convert(data)
    self.writer.write(data)
    return


  def __init__(self):
    """
    Constructor.
    """
    Script.__init__(self, 'pyconvert')
    return


  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _configure(self):
    """
    Set members using inventory.
    """
    
    Script._configure(self)
    if self.inventory.reader.name == "dummy":
      raise UnboundLocalError, "convert needs a reader to load the data.\n" \
            "Please specify an unpickler with --reader=myreader"
    else:
      self.reader = self.inventory.reader

    if self.inventory.converter.name == "dummy":
      self.converter = None
    else:
      self.converter = self.inventory.converter

    if self.inventory.writer.name == "dummy":
      self.writer = self.reader
    else:
      self.writer = self.inventory.writer
      
    return


# End of file 
