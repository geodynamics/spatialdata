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

subpackage = geocoords
include $(top_srcdir)/pkgs/subpackage.am

subpkgpyexec_LTLIBRARIES = geocoordsmodule.la

geocoordsmodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	converter.cc \
	coordsys.cc \
	cscart.cc \
	csgeo.cc \
	csgeolocalcart.cc \
	csgeoproj.cc \
	projector.cc \
	geocoordsmodule.cc

INCLUDES += -I$(PYTHON_INCDIR)

geocoordsmodule_la_LDFLAGS = -module

geocoordsmodule_la_LIBADD = \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatageocoords.la \
	-lpythiautil

# version
# $Id$

# End of file 
