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
PACKAGE = doc

all builddoc:
	doxygen doxyconfig

clean::
	$(RM) $(RMFLAGS) html

# version
# $Id: Make.mm,v 1.1.1.1 2005/03/17 22:18:34 baagaard Exp $

#
# End of file
