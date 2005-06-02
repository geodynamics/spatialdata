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
PACKAGE = geocoords

# ----------------------------------------------------------------------

all: export

# ----------------------------------------------------------------------

EXPORT_PYTHON_MODULES = \
	GeoCoordSys.py \
	GeoLocalConverter.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.2 2005/06/01 23:55:48 baagaard Exp $

# End of file
