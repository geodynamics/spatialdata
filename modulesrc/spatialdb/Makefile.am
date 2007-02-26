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

spatialdbmodule_la_LDFLAGS = -module

spatialdbmodule_la_SOURCES = spatialdb.pyxe

nodist_spatialdbmodule_la_SOURCES = \
	spatialdb.c spatialdb_embed.cpp spatialdb_embed.h

spatialdbmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la

INCLUDES += -I$(PYTHON_INCDIR)

spatialdb.pyx spatialdb_embed.cpp  spatialdb_embed.h: spatialdb.pyxe
	pyrexembed spatialdb.pyxe
spatialdb.pyxe: $(srcdir)/spatialdb.pyxe.src
	cp $(srcdir)/spatialdb.pyxe.src $@
spatialdb_embed.cpp: spatialdb_embed.h
spatialdb_embed.h: spatialdb.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = spatialdb.pyx spatialdb.c *_embed.*

# End of file 
