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

PROJECT = spatialdata/tests
PACKAGE = langtestspatialdbmodule

include std-pythonmodule.def
include local.def

PROJ_SRCS = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	langtestspatialdb.cc \

# version
# $Id: Make.mm,v 1.1 2005/03/19 00:46:58 baagaard Exp $

# End of file
