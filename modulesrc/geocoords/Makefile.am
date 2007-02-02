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
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = geocoordsmodule.la

geocoordsmodule_la_LDFLAGS = -module

geocoordsmodule_la_SOURCES = geocoords.pyxe

nodist_geocoordsmodule_la_SOURCES = \
	geocoords.c geocoords_embed.cpp geocoords_embed.h

geocoordsmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la

INCLUDES += -I$(PYTHON_INCDIR)

geocoords.pyx geocoords_embed.cpp  geocoords_embed.h: geocoords.pyxe
	pyrexembed geocoords.pyxe
geocoords.pyxe: $(srcdir)/geocoords.pyxe.src
	cp $(srcdir)/geocoords.pyxe.src $@
geocoords_embed.cpp: geocoords_embed.h
geocoords_embed.h: geocoords.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = geocoords.pyx geocoords.c *_embed.*

# End of file 
