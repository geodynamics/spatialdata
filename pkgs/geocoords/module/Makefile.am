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

pkgpyexec_LTLIBRARIES = spatialdatageocoordsmodule.la

spatialdatageocoordsmodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	converter.cc \
	coordsys.cc \
	cscart.cc \
	csgeo.cc \
	csgeolocalcart.cc \
	csgeoproj.cc \
	projector.cc

INCLUDES += -I$(PYTHON_INCDIR)

spatialdatageocoordsmodule_la_LDFLAGS = -module

spatialdatageocoordsmodule_la_LIBADD = \
	$(top_builddir)/pkgs/geocoords/lib/libspatialdatageocoords.la

# version
# $Id$

# End of file 
