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

subpackage = utils
include $(top_srcdir)/subpackage.am

subpkgpyexec_LTLIBRARIES = utilsmodule.la

utilsmodule_la_LDFLAGS = -module

utilsmodule_la_SOURCES = utils.pyxe

nodist_utilsmodule_la_SOURCES = \
	utils.c utils_embed.cpp utils_embed.h

INCLUDES += -I$(PYTHON_INCDIR)

utils.pyx utils_embed.cpp  utils_embed.h: utils.pyxe
	cp $< . && pyrexembed.py utils.pyxe && rm -f utils.pyxe
utils_embed.cpp: utils_embed.h
utils_embed.h: utils.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = utils.pyx utils.c *_embed.*

# End of file 
