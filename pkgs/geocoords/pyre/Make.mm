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
	CoordSys.py \
	CSCart.py \
	CSGeo.py \
	CSGeoLocalCart.py \
	CSGeoProj.py \
	Converter.py \
	Projector.py \
	__init__.py \

export:: export-package-python-modules

# version
# $Id: Make.mm,v 1.2 2005/06/01 23:55:48 baagaard Exp $

# End of file
