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
PACKAGE = tests

# ----------------------------------------------------------------------

all: export

# ----------------------------------------------------------------------

EXPORT_PYTHON_MODULES = \
	TestSpatialDB.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.1 2005/03/19 00:46:58 baagaard Exp $

# End of file
