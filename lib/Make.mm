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
PACKAGE = 

include local.def

PROJ_SRCS = \
	SimpleDB.cc \
	SpatialDB.cc \
	SimpleDBQuery.cc \
	SimpleIO.cc \
	SimpleIOAscii.cc \

all: $(PROJ_SAR) export-headers

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
# $Id: Make.mm,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file 
