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
PACKAGE = tests

RECURSE_DIRS = \
	libtests \
	pytests \
	langtests \

OTHERS = \

# ----------------------------------------------------------------------

all:
	BLD_ACTION="all" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

test::
	BLD_ACTION="test" $(MM) recurse

# version
# $Id: Make.mm,v 1.3 2005/03/21 04:34:39 baagaard Exp $

# End of file 
