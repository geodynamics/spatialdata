#!/usr/bin/env python
#
# ======================================================================
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
# ======================================================================
#

## @file spatialdata/applications/pyconvert.py

## @brief Generic use of ConvertApp.

# ----------------------------------------------------------------------
if __name__ == '__main__':
  from spatialdata.utils.ConvertApp import ConvertApp

  app = ConvertApp()
  app.run()


# End of file 
