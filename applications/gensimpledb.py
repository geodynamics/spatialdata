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

## @file spatialdata/applications/gensimpledb.py
## @brief Generic use of GenSimpleDBApp.

# ----------------------------------------------------------------------
if __name__ == '__main__':
  from spatialdata.spatialdb.generator.GenSimpleDBApp import GenSimpleDBApp

  app = GenSimpleDBApp()
  app.run()


# End of file 
