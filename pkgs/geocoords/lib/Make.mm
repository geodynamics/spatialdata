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
	Geoid.cc \
	GeoLocalConverter.cc \
	Projector.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	GeoCoordSys.h \
	GeoCoordSys.icc \
	GeoCSConverter.h \
	Geoid.h \
	GeoLocalConverter.h \
	PointStream.h \
	Projector.h \
	Projector.icc \
	proj4fwd.h \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.4 2005/06/19 19:36:53 baagaard Exp $

# End of file 
