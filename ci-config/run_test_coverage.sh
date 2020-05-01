#!/bin/bash

# Run tests to generate coverage information. Upload test coverage data
# Must run codeocov script in top-level source directory.

make -j$(nproc) install
if [ $? != 0 ]; then exit 1; fi

make -j$(nproc) check VERBOSE=1
if [ $? != 0 ]; then exit 1; fi

LCOV=`which lcov`
if test -f $LCOV; then
  make coverage-libtests

  pushd ../../src/spatialdata && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ../../build/spatialdata/coverage-libtests.info -F libtests -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
else
    echo "lcov not found. Skipping C++ test coverage."
fi

PYCOV=`which coverage`
if test -f $PYCOV; then
  make coverage-pytests

  pushd ../../src/spatialdata && \
      bash <(curl -s https://codecov.io/bash) -X gcov -f ../../build/spatialdata/coverage-pytests.xml -F pytests -y ci-config/codecov.yml \
	  || echo "Codecov did not collect coverage reports." && \
      popd
else
    echo "coverage not found. Skipping Pyhton test coverage."
fi

exit 0
