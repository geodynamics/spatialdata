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
PACKAGE = geocoords/tests

RECURSE_DIRS = \
	libtests \

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
# $Id: Make.mm,v 1.1 2005/05/25 17:29:14 baagaard Exp $

# End of file 
