# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2013 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

from distutils.core import setup

setup(
    
    name = 'spatialdata', 
    version = '1.9.2',

    zip_safe = False,
    
    author = 'Brad T. Aagaard',
    author_email = 'baagaard@usgs.gov',
    description = """C++/Python module for specifying variations in fields over a domain (typically parameters for boundary conditions or physical properties over a simulation domain). The module also supports conversions between coordinate systems, using Proj.4 for conversions between geographic coordinate systems.""",
    license = 'MIT license',
    url = 'http://www.geodynamics.org/software/pylith',

)
