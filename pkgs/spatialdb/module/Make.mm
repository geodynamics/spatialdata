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

PROJECT = spatialdata/spatialdb
PACKAGE = spatialdbmodule

include std-pythonmodule.def
include local.def

PROJ_SRCS = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	spatialdb.cc \
	simpledb.cc \
	simpleio.cc \
	simpleioascii.cc \

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:42:58 baagaard Exp $

# End of file
