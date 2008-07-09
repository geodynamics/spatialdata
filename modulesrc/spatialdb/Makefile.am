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

subpkgpyexec_LTLIBRARIES = spatialdbmodule.la

spatialdbmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist_spatialdbmodule_la_SOURCES = spatialdb.pyxe.src
nodist_spatialdbmodule_la_SOURCES = \
	spatialdata.spatialdb.spatialdb.pyxe \
	spatialdata.spatialdb.spatialdb.c spatialdata.spatialdb.spatialdb_embed.cpp spatialdata.spatialdb.spatialdb_embed.h

spatialdbmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la
if NO_UNDEFINED
spatialdbmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(PYTHON_INCDIR)

include_HEADERS = \
	spatialdata.spatialdb.spatialdb.pxd

spatialdata.spatialdb.spatialdb.pyx spatialdata.spatialdb.spatialdb_embed.cpp spatialdata.spatialdb.spatialdb_embed.h: spatialdata.spatialdb.spatialdb.pyxe spatialdata.spatialdb.spatialdb.pxd
	pyrexembed spatialdata.spatialdb.spatialdb.pyxe
spatialdata.spatialdb.spatialdb.pyxe: $(srcdir)/spatialdb.pyxe.src
	cp $(srcdir)/spatialdb.pyxe.src $@
spatialdata.spatialdb.spatialdb.pxd: $(srcdir)/spatialdb.pxd.src
	cp $(srcdir)/spatialdb.pxd.src $@
spatialdata.spatialdb.spatialdb_embed.cpp: spatialdata.spatialdb.spatialdb_embed.h
spatialdata.spatialdb.spatialdb_embed.h: spatialdata.spatialdb.spatialdb.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = spatialdata.spatialdb.spatialdb.pyx spatialdata.spatialdb.spatialdb.pyxe spatialdata.spatialdb.spatialdb.c *_embed.*

# End of file 
