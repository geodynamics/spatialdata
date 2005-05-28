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
	GeoCSConverter.py \
	GeoLocalConverter.py \
	Projector.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.1 2005/05/28 00:31:04 baagaard Exp $

# End of file
