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

SUBDIRS = data

TESTS = testspatial.py

TESTS_ENVIRONMENT = $(PYTHON)

check_SCRIPTS = testspatial.py

if ENABLE_SCEC_CVM_H
  TESTS += test_sceccvmh.py
  check_SCRIPTS += test_sceccvmh.py
endif

noinst_PYTHON = \
	TestGenSimpleDBApp.py \
	TestSCECCVMH.py \
	TestSimpleIOAscii.py \
	TestSpatialDB.py \
	TestUniformDB.py


data_DATA = \
	testgen1din2d.odb \
	testgen1din2d_one.odb \
	testgen1din2d_two.odb \
	gensimpledb.cfg

do_build = sed -e s%[@]SCECCVMH_DATADIR[@]%${SCECCVMH_DATADIR}%g

$(srcdir)/TestSCECCVMH.py: $(srcdir)/TestSCECCVMH.py.in Makefile
	$(do_build) < $< > $@
testspatial.py: $(srcdir)/TestSCECCVMH.py

# 'export' the input files by performing a mock install
export_datadir = $(top_builddir)/tests/pytests/spatialdb
export-data: $(data_DATA)
	for f in $(data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done

BUILT_SOURCES = export-data

CLEANFILES = \
	$(srcdir)/TestSCECCVMH.py \
	$(export_datadir)/$(data_DATA)

# End of file 
