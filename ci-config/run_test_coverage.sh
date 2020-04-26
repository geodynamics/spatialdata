#!/bin/bash

# Run tests to generate coverage information. Upload test coverage data.

make -j$(nproc) install
make -j$(nproc) check VERBOSE=1

LCOV=`which lcov`
if test -f $LCOV; then
  make coverage-libsrc

  # Must run codeocov script in top-level source directory.
  cd ../../src/spatialdata && bash <(curl -s https://codecov.io/bash) -X gcov -f ../../build/spatialdata/coverage.info -F libsrc -y ci-config/codecov.yml
else
    echo "lcov not found. Skipping test coverage."
fi
  
exit 0
