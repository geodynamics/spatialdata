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
PACKAGE = tests/langtests

include local.def

PROJ_SRCS = \
	f77testspatialdb.f \

all: $(PROJ_SAR)

# version
# $Id: Make.mm,v 1.1 2005/03/19 00:46:57 baagaard Exp $

# End of file 
