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

## @file solver/pyre/convert.py
## @brief Python convert application driver

from pyre.applications.Script import Script


from pyre.components.Component import Component

# Dummy class for empty component
class Dummy(Component):
  def __init__(self):
    Component.__init__(self, name="dummy", facility="dummy")
    return

# Convert class
class Convert(Script):
  """Python Convert application driver."""

  # INVENTORY //////////////////////////////////////////////////////////

  class Inventory(Script.Inventory):
    """Python object for managing Convert facilities and properties."""

    ## @class Inventory
    ## Python object for managing Convert facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b unpickler Unpickler to load data
    ## @li \b converter Converter to convert data
    ## @li \b pickler Pickler to dump data

    import pyre.inventory

    unpickler = pyre.inventory.facility("unpickler", factory=Dummy)
    unpickler.meta['tip'] = "Unpickler to load data."

    converter = pyre.inventory.facility("converter", factory=Dummy)
    converter.meta['tip'] = "Converter to convert data."

    pickler = pyre.inventory.facility("pickler", factory=Dummy)
    pickler.meta['tip'] = "Pickler to dump data"

  # PUBLIC METHODS /////////////////////////////////////////////////////

  def main(self, *args, **kwds):
    data = self.unpickler.load()
    self.converter.convert(data)
    self.pickler.dump(data)
    return

  def __init__(self):
    Script.__init__(self, 'convert')
    return

  # PRIVATE METHODS ////////////////////////////////////////////////////

  def _defaults(self):
    Script._defaults(self)
    return

  def _configure(self):
    Script._configure(self)
    if self.inventory.unpickler.name == "dummy":
      raise UnboundLocalError, "convert needs an unpickler to load the data.\n" \
            "Please specify an unpickler with --unpickler=myunpickler"
    else:
      self.unpickler = self.inventory.unpickler

    if self.inventory.converter.name == dummy:
      raise UnboundLocalError, "convert needs a converter to convert the data.\n" \
            "Please specify a converter with --converter=myconverter"
    else:
      self.converter = self.inventory.converter

    if self.inventory.pickler.name == dummy:
      self.pickler = self.unpickler
    else:
      self.pickler = self.inventory.pickler
    return

  def _init(self):
    Script._init(self)
    return

# ----------------------------------------------------------------------
# main
if __name__ == '__main__':
  app = Convert()
  app.run()

# version
__id__ = "$Id: convert.py,v 1.1 2005/05/31 15:18:43 baagaard Exp $"

# End of file 
