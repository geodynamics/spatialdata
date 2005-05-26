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
	cspatialdb.cc \
	f77spatialdb.cc \

all: $(PROJ_SAR) export-package-headers

# ----------------------------------------------------------------------
export:: release-package-headers export-libraries

EXPORT_HEADERS = \
	cspatialdb.h \

EXPORT_LIBS = $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:42:57 baagaard Exp $

# End of file 
