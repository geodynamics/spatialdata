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

subpackage = spatialdb
include $(top_srcdir)/pkgs/subpackage.am

pkgpyexec_LTLIBRARIES = spatialdatamodule.la

spatialdatamodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	spatialdb.cc \
	simpledb.cc \
	simpleio.cc \
	simpleioascii.cc

INCLUDES += -I$(PYTHON_INCDIR)

spatialdatamodule_la_LDFLAGS = -module

spatialdatamodule_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la

# version
# $Id$

# End of file 
