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

subpkgpyexec_LTLIBRARIES = spatialdbmodule.la

spatialdbmodule_la_SOURCES = \
	bindings.cc \
	exceptions.cc \
	misc.cc \
	spatialdb.cc \
	simpledb.cc \
	simpleio.cc \
	simpleioascii.cc \
	spatialdbmodule.cc 

INCLUDES += -I$(PYTHON_INCDIR)

spatialdbmodule_la_LDFLAGS = -module

spatialdbmodule_la_LIBADD = \
	$(top_builddir)/pkgs/spatialdb/lib/libspatialdata.la \
	-lpythiautil

# version
# $Id$

# End of file 
