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

PROJECT = spatialdata/spatialdb/tests
PACKAGE = langtestspatialdbmodule

include std-pythonmodule.def
include local.def

PROJ_SRCS = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	langtestspatialdb.cc \

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:03 baagaard Exp $

# End of file
