# -*- Makefile -*-
#
# ----------------------------------------------------------------------
#
#                           Brad T. Aagaard
#                        U.S. Geological Survey
#
# {LicenseText}
#
# ----------------------------------------------------------------------
#

PROJECT = spatialdata
PACKAGE = tests/pytests

RECURSE_DIRS = \
	data \

# ----------------------------------------------------------------------
all:
	BLD_ACTION="all" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

test:
	@LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(BLD_LIBDIR) ./testspatial.py

# version
# $Id: Make.mm,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file
