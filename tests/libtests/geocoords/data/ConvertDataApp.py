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
## @file geocoords/tests/libtests/data/ConvertDataApp.py
## @brief Python application to generate data for coordinate conversion tests.

from pyre.applications.Script import Script

# ConvertDataApp class
class ConvertDataApp(Script):
  """Python application to generate data for coordinate conversion tests."""

  def main(self, *args, **kwds):
    """Run application."""
    data = self.inventory.data
    data.calculate()
    data.dump(self.inventory.dumper)
    return

  def __init__(self):
    """Constructor."""
    Script.__init__(self, 'convertdataapp')
    return

  class Inventory(Script.Inventory):

    ## @class Inventory
    ## Python object for managing ConvertDataApp facilities and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b data Data generator for coordinate transformation test
    ## @li \b dumper Dump data to file

    import pyre.inventory
    from pythiautil.DumpCpp import DumpCpp
    from ConvertData import ConvertData
    data = pyre.inventory.facility('data', factory=ConvertData)
    dumper = pyre.inventory.facility('dumper', factory=DumpCpp)

# main
if __name__ == '__main__':
  app = ConvertDataApp()
  app.run()

# version
__id__ = "$Id: ConvertDataApp.py,v 1.1 2005/05/25 17:30:21 baagaard Exp $"

# End of file 
