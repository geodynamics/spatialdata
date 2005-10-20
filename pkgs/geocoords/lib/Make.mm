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
	CoordSysGeo.cc \
	CoordSysLocal.cc \
	Geoid.cc \
	Projector.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	Converter.h \
	CoordSys.h \
	CoordSys.icc \
	CoordSysGeo.h \
	CoordSysGeo.icc \
	CoordSysLocal.h \
	CoordSysLocal.icc \
	proj4fwd.h \
	Geoid.h \
	Projector.h \
	Projector.icc \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.5 2005/06/21 18:20:24 baagaard Exp $

# End of file 
