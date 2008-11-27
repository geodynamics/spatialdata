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

subpackage = units
include $(top_srcdir)/subpackage.am


subpkgpyexec_LTLIBRARIES = unitsmodule.la

unitsmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)

dist_unitsmodule_la_SOURCES = units.pyxe.src

nodist_unitsmodule_la_SOURCES = \
	units.pyxe \
	units.c units_embed.cpp units_embed.h

unitsmodule_la_LIBADD = \
	$(top_builddir)/libsrc/libspatialdata.la
if NO_UNDEFINED
unitsmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

INCLUDES += -I$(PYTHON_INCDIR)

units.pyx units_embed.cpp  units_embed.h: units.pyxe
	pyrexembed units.pyxe
units.pyxe: $(srcdir)/units.pyxe.src
	cp $(srcdir)/units.pyxe.src $@
units_embed.cpp: units_embed.h
units_embed.h: units.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = units.pyx units.pyxe units.c *_embed.*

# End of file 
