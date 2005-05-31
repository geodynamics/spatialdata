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
PACKAGE = geocoords

RECURSE_DIRS = \
	lib \
	tests \
	applications \

OTHERS = \

# ----------------------------------------------------------------------

all:
	BLD_ACTION="all" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

builddoc:
	$(MM) -C doc

# version
# $Id: Make.mm,v 1.2 2005/05/31 15:18:16 baagaard Exp $

# End of file 
