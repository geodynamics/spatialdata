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
dist_check_SCRIPTS = testutils.py

TESTS_ENVIRONMENT = $(PYTHON)

noinst_PYTHON = \
	TestChangeCoordSys.py \
	TestConvertApp.py \
	TestPointsStream.py \
	TestSimpleArray.py

# module
subpkgpyexec_LTLIBRARIES = testcppmodule.la

testcppmodule_la_LDFLAGS = -module -avoid-version \
	$(AM_LDFLAGS) $(PYTHON_LA_LDFLAGS)
testcppmodule_la_LIBADD =
if NO_UNDEFINED
testcppmodule_la_LIBADD += \
	$(PYTHON_BLDLIBRARY) $(PYTHON_LIBS) $(PYTHON_SYSLIBS)
endif

dist_testcppmodule_la_SOURCES = testcpp.pyxe.src

nodist_testcppmodule_la_SOURCES = \
	testcpp.pyxe \
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


# End of file 
