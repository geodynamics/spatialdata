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
## @file tests/libtests/data/TestSimpleDBDataApp.py
## @brief Python application to generate data for SimpleDB tests.

from pyre.applications.Script import Script

# TestSimpleDBDataApp class
class TestSimpleDBDataApp(Script):
  """Python application to generate data for SimpleDB tests."""

  def main(self, *args, **kwds):
    """Run the application."""
    data = self.inventory.data
    data.initialize()
    data.dump(self.inventory.dumper)

  def __init__(self):
    """Constructor."""
    Script.__init__(self, 'testsimpledbdataapp')
    return

  class Inventory(Script.Inventory):
    ## @class Inventory
    ## Python object for managing TestSimpleDBDataApp facilities
    ## and properties.
    ##
    ## \b Properties
    ## @li None
    ##
    ## \b Facilities
    ## @li \b query_data Query data to dump
    ## @li \b dumper Dump data to file

    import pyre.inventory

    from SimpleDBQueryData import SimpleDBQueryData
    data = pyre.inventory.facility('query_data', factory=SimpleDBQueryData)
    
    from pythiautil.DumpCpp import DumpCpp
    dumper = pyre.inventory.facility('dumper', factory=DumpCpp)


# main
if __name__ == '__main__':
  app = TestSimpleDBDataApp()
  app.run()

# version
__id__ = "$Id: TestSimpleDBDataApp.py,v 1.1 2005/05/25 18:43:07 baagaard Exp $"

# End of file 
