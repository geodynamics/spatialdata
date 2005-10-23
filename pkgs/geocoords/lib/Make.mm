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

include local.def

PROJ_SRCS = \
	Converter.cc \
	CoordSys.cc \
	CSCart.cc \
	CSGeo.cc \
	CSGeoLocalCart.cc \
	CSGeoProj.cc \
	Geoid.cc \
	Projector.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	Converter.h \
	CoordSys.h \
	CoordSys.icc \
	CSCart.h \
	CSCart.icc \
	CSGeo.h \
	CSGeo.icc \
	CSGeoLocalCart.h \
	CSGeoLocalCart.icc \
	CSGeoProj.h \
	Geoid.h \
	Projector.h \
	Projector.icc \
	proj4fwd.h \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.5 2005/06/21 18:20:24 baagaard Exp $

# End of file 
