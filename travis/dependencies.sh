#!/bin/bash

action="download"
if [ $# == 1 ]; then
  action=$1
fi

MAKE_THREADS=16
TOP_DIR=`pwd`
TARBALL=spatialdata_deps-${TRAVIS_OS_NAME}.tgz
REPO=http://geoweb.cse.ucdavis.edu/~buildbot/deps

if [ $action == "download" ]; then
  curl -O ${REPO}/${TARBALL} && tar -zxvf ${TARBALL}

elif [ $action == "build" ]; then

git clone --depth 1 --recursive https://github.com/geodynamics/pylith_installer.git

pushd pylith_installer && \
  autoreconf --install --verbose && \
  ./configure --prefix=${TOP_DIR}/dist --enable-mpi=mpich --enable-cppunit --enable-numpy --enable-proj4 --enable-hdf5 --enable-netcdfpy --enable-cmake --enable-setuptools --enable-nemesis --enable-fiat --enable-pcre --enable-swig --enable-force-install --with-make-threads=${MAKE_THREADS} && \
  . ./setup.sh && \
  make deps && \
  popd && \
  tar -zcvf $TARBALL dist && curl -T ${TARBALL} ftp://ftpext.usgs.gov/from_pub/wr/
fi

# End of file
