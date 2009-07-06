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
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = _spatialdbmodule.la

subpkgpyexec_PYTHON = spatialdb.py

swig_sources = \
	spatialdb.i \
	SpatialDBObj.i \
	SimpleDB.i \
	SimpleDBData.i \
	SimpleIO.i \
	SimpleIOAscii.i \
	UniformDB.i \
	CompositeDB.i \
	SCECCVMH.i \
	GravityField.i \
	TimeHistory.i \
	TimeHistoryIO.i

swigincludedir = $(pkgdatadir)/swig/$(subpackage)
swiginclude_HEADERS = \
	SpatialDBObj.i

swig_generated = \
	spatialdb_wrap.cxx \
	spatialdb.py

_spatialdbmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist__spatialdbmodule_la_SOURCES = $(swig_sources) $(swig_generated)

_spatialdbmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la
if NO_UNDEFINED
_spatialdbmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(NUMPY_INCDIR) -I$(PYTHON_INCDIR)

if ENABLE_SWIG
$(srcdir)/spatialdb_wrap.cxx $(srcdir)/spatialdb.py: $(swig_sources)
	$(SWIG) -Wall -c++ -python $<
endif


MAINTAINERCLEANFILES = $(swig_generated)


# End of file 
