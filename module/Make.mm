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

PROJECT = spatialdata
PACKAGE = spatialdatamodule

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
# $Id: Make.mm,v 1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file
