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
PACKAGE = 

RECURSE_DIRS = \
	lib \
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
# $Id: Make.mm,v 1.1 2005/03/17 22:18:34 baagaard Exp $

# End of file 
