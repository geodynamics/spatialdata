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
PACKAGE = spatialdb/tests/ctests/driver

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
	@LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(BLD_LIBDIR) ./testcspatial.py

# version
# $Id: Make.mm,v 1.1 2005/05/25 18:43:01 baagaard Exp $

# End of file
