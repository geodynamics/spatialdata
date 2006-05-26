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

## @file spatialdata/spatialdb/generator/gensimpledb.py
## @brief Generic use of GenSimpleDBApp.

# ----------------------------------------------------------------------
# main
if __name__ == '__main__':
  from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp

  app = GenSimpleDBApp()
  app.run()

# version
__id__ = "$Id$"

# End of file 
