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

# LIBRARY --------------------------------------------------------------
lib_LTLIBRARIES = libyournamespatialdb.la

libyournamespatialdb_la_SOURCES = \
	GeoGridVelModel.cc

libyournamespatialdb_la_LDFLAGS = $(AM_LDFLAGS)

libyournamespatialdb_la_LIBADD = \
	-lspatialdata \
	-lproj

INCLUDES = 

# MODULE ---------------------------------------------------------------

pkgpyexec_LTLIBRARIES = yournamespatialdbmodule.la

yournamespatialdbmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist_yournamespatialdbmodule_la_SOURCES = spatialdb.pyxe.src
nodist_yournamespatialdbmodule_la_SOURCES = \
	spatialdb.pyxe \
	spatialdb.c spatialdb_embed.cpp spatialdb_embed.h

yournamespatialdbmodule_la_LIBADD = libyournamespatialdb.la
if NO_UNDEFINED
yournamespatialdbmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(PYTHON_INCDIR)

spatialdb.pyx spatialdb_embed.cpp  spatialdb_embed.h: spatialdb.pyxe
	pyrexembed spatialdb.pyxe
spatialdb.pyxe: $(srcdir)/spatialdb.pyxe.src
	cp $(srcdir)/spatialdb.pyxe.src $@
spatialdb_embed.cpp: spatialdb_embed.h
spatialdb_embed.h: spatialdb.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = spatialdb.pyx spatialdb.pyxe spatialdb.c *_embed.*



# PYTHON ---------------------------------------------------------------

nobase_pkgpyexec_PYTHON = \
	__init__.py \
	GeoGridVelModel.py


# End of file 
