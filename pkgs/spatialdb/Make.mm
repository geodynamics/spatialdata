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
PACKAGE = spatialdb

RECURSE_DIRS = \
	lib \
	liblang \
	module \
	pyre \
	tests \

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
# $Id: Make.mm,v 1.1 2005/05/25 18:40:47 baagaard Exp $

# End of file 
