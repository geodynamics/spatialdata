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

TESTS = testutils.py

check_SCRIPTS = testutils.py

noinst_PYTHON = \
	TestSimpleArray.py

# module
subpkgpyexec_LTLIBRARIES = testcppmodule.la

testcppmodule_la_LDFLAGS = -module

testcppmodule_la_SOURCES = testcpp.pyxe

nodist_testcppmodule_la_SOURCES = \
	testcpp.c testcpp_embed.cpp testcpp_embed.h

INCLUDES += -I$(PYTHON_INCDIR)

testcpp.pyx testcpp_embed.cpp  testcpp_embed.h: testcpp.pyxe
	pyrexembed testcpp.pyxe
testcpp.pyxe: $(srcdir)/testcpp.pyxe.src
	cp $(srcdir)/testcpp.pyxe.src $@
testcpp_embed.cpp: testcpp_embed.h
testcpp_embed.h: testcpp.pyx

.pyx.c:
	pyrexc $<

CLEANFILES = testcpp.pyxe testcpp.pyx testcpp.c *_embed.*


# version
# $Id$

# End of file 
