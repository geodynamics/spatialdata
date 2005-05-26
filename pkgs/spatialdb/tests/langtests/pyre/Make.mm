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
PACKAGE = spatialdb/tests

# ----------------------------------------------------------------------

all: export

# ----------------------------------------------------------------------

EXPORT_PYTHON_MODULES = \
	TestSpatialDB.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:04 baagaard Exp $

# End of file
