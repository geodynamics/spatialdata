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
dist_check_SCRIPTS = testspatial.py

if ENABLE_SCEC_CVM_H
  TESTS += test_sceccvmh.py
  dist_check_SCRIPTS += test_sceccvmh.py
endif

TESTS_ENVIRONMENT = $(PYTHON)

noinst_PYTHON = \
	TestCompositeDB.py \
	TestGenSimpleDBApp.py \
	TestGravityField.py \
	TestSCECCVMH.py \
	TestSimpleIOAscii.py \
	TestSimpleDB.py \
	TestUniformDB.py

dist_noinst_PYTHON = \
	TestSCECCVMH.py.in

dist_data_DATA = \
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
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_data_DATA); do $(install_sh_DATA) $(srcdir)/$$f $(export_datadir); done; fi

clean-data:
	if [ "X$(top_srcdir)" != "X$(top_builddir)" ]; then for f in $(dist_data_DATA); do $(RM) $(RM_FLAGS) $(export_datadir)/$$f; done; fi

BUILT_SOURCES = export-data
clean-local: clean-data

CLEANFILES = \
	$(srcdir)/TestSCECCVMH.py

# End of file 
