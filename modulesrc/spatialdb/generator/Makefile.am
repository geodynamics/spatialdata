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

subpackage = spatialdb/generator
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = generatormodule.la

generatormodule_la_LDFLAGS = -module

generatormodule_la_SOURCES = generator.pyxe

nodist_generatormodule_la_SOURCES = \
	generator.c generator_embed.cpp generator_embed.h

generatormodule_la_LIBADD = \
	$(top_builddir)/libsrc/spatialdb/libspatialdataspatialdb.la

INCLUDES += -I$(PYTHON_INCDIR)

generator.pyx generator_embed.cpp  generator_embed.h: generator.pyxe
	pyrexembed generator.pyxe
generator.pyxe: $(srcdir)/generator.pyxe.src
	cp $(srcdir)/generator.pyxe.src $@
generator_embed.cpp: generator_embed.h
generator_embed.h: generator.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = generator.pyx generator.c *_embed.*

# End of file 
