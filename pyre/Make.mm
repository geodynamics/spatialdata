# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# <LicenseText>
#
# ----------------------------------------------------------------------
#

PROJECT = spatialdata
PACKAGE = 

# ----------------------------------------------------------------------

all: export

# ----------------------------------------------------------------------

EXPORT_PYTHON_MODULES = \
	SpatialDB.py \
	SimpleDB.py \
	SimpleIO.py \
	SimpleIOAscii.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file
