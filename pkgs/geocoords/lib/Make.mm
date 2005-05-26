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
	GeoCoordSys.cc \
	GeoCSConverter.cc \
	GeoLocalConverter.cc \
	Projector.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	GeoCoordSys.h \
	GeoCoordSys.icc \
	GeoCSConverter.h \
	GeoLocalConverter.h \
	Projector.h \
	Projector.icc \
	proj4fwd.h \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/05/25 17:28:11 baagaard Exp $

# End of file 
