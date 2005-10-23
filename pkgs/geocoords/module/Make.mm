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

PROJECT = spatialdata/geocoords
PACKAGE = geocoordsmodule

include std-pythonmodule.def
include local.def

PROJ_SRCS = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	converter.cc \
	coordsys.cc \
	cscart.cc \
	csgeo.cc \
	csgeolocalcart.cc \
	csgeoproj.cc \
	projector.cc \

# version
# $Id: Make.mm,v 1.1 2005/06/01 23:56:10 baagaard Exp $

# End of file
