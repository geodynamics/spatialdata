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
	cspatialdb.cc \
	f77spatialdb.cc \

all: $(PROJ_SAR) export-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	cspatialdb.h \
	spatialdbF77.h \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/03/19 00:47:11 baagaard Exp $

# End of file 
