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
PACKAGE = tests/langtests

RECURSE_DIRS = \
	libc \
	libf77 \
	module \
	pyre \
	driver \

OTHERS = \

# ----------------------------------------------------------------------

all:
	BLD_ACTION="all" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

# version
# $Id: Make.mm,v 1.1 2005/03/19 00:46:58 baagaard Exp $

# End of file 
