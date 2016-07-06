# Spatialdata

[![MIT License](https://img.shields.io/badge/license-MIT-blue.svg)](https://github.com/geodynamics/spatialdata/blob/master/COPYING)
[![Build Status](https://travis-ci.org/geodynamics/spatialdata.svg?branch=master)](https://travis-ci.org/geodynamics/spatialdata)

Spatialdata is a C++ library for

* interpolating values for spatially distributed data,
* converting coordinates among geographic projections using Proj.4,
* nondimensionalization of quantities,
* specification of units via Pyre (optional).

This library is used in the finite-element code PyLith
(https://github.com/geodynamics/pylith). The primary focus is
specification of parameters that vary in space, such as values for
boundary conditions and parameters of constitutive models. This
provides a specification of these parameters independent of the
discretization.

## Dependencies

* GNU build tools w/C++ and C compilers
* Proj.4 cartographic projections library (http://proj.maptools.org)
* [Optional] Pyre 0.8 and NumPy
* [Optional] CppUnit (for unit testing)

## Author

* Brad Aagaard, Earthquake Science Center, USGS, USA
