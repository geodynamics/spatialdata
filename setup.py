
from archimedes import use_merlin
use_merlin()

from merlin import setup, find_packages

setup(
    
    name = 'spatialdata', 
    version = '0.6.0',

    zip_safe = False,
    packages = find_packages(),
    
    install_requires = [
    'pythia[mpi] >= 0.8.1.4, < 0.8.2a',
    ],

    author = 'Brad T. Aagaard',
    author_email = 'baagaard@usgs.gov',
    description = """""",
    license = 'other',
    url = 'http://www.geodynamics.org/',

)
