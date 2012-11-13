# ----------------------------------------------------------------------
#
# Brad T. Aagaard, U.S. Geological Survey
#
# This code was developed as part of the Computational Infrastructure
# for Geodynamics (http://geodynamics.org).
#
# Copyright (c) 2010-2012 University of California, Davis
#
# See COPYING for license information.
#
# ----------------------------------------------------------------------
#

from archimedes import use_merlin
use_merlin()

from merlin import setup, find_packages

setup(
    
    name = 'spatialdata', 
    version = '1.9.1',

    zip_safe = False,
    packages = find_packages(),
    
    install_requires = [
    'pythia[mpi] >= 0.8.1.4, < 0.8.2a',
    ],

    author = 'Brad T. Aagaard',
    author_email = 'baagaard@usgs.gov',
    description = """C++/Python module for specifying variations in fields over a domain (typically parameters for boundary conditions or physical properties over a simulation domain. The module also supports conversions between coordinate systems, using Proj.4 for conversions between geographic coordinate systems.""",
    license = 'MIT license',
    url = 'http://www.geodynamics.org/',

)
