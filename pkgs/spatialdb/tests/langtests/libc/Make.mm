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
PACKAGE = spatialdb/tests/langtests

include local.def

PROJ_SRCS = \
	ctestspatialdb.c \

all: $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:01 baagaard Exp $

# End of file 
