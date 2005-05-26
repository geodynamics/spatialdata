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
PACKAGE = spatialdb

include local.def

PROJ_SRCS = \
	SimpleDB.cc \
	SpatialDB.cc \
	SimpleDBQuery.cc \
	SimpleIO.cc \
	SimpleIOAscii.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	SpatialDB.h \
	SpatialDB.icc \
	SimpleDB.h \
	SimpleDB.icc \
	SimpleIO.h \
	SimpleIO.icc \
	SimpleIOAscii.h \
	SimpleIOAscii.icc \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:42:56 baagaard Exp $

# End of file 
