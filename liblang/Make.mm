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

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.2 2005/03/19 04:21:48 baagaard Exp $

# End of file 
