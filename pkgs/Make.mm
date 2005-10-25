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
	pyre \
	geocoords \
	spatialdb \

OTHERS = \

# ----------------------------------------------------------------------
all:
	BLD_ACTION="all" $(MM) recurse

clean::
	BLD_ACTION="clean" $(MM) recurse

tidy::
	BLD_ACTION="tidy" $(MM) recurse

# version
# $Id: Make.mm,v 1.1 2005/05/25 17:27:22 baagaard Exp $

# End of file 
