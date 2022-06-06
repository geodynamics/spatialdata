## Version 3.0.0 (2022/06/06)

* Convert to Python 3
* Change `label` in `SpatialDB` and `TimeHistory` to `description` to avoid confusion with other Pyre properties called `label`.
* Create online documentation for Spatial Data that is now separate from PyLith.
  * Documentation covers more features and use cases.
  * Examples include C++, Python, and `cfg` files.

## Version 2.0.0 (2021/01/09)

* Update to use Proj 6.x. This allows a user to specify a coordinate
system using a string consisting of Proj parameters, EPSG code, or
WKT.
* Eliminate overloading of getters/settings in C++ interface. Use getXXX/setXXX instead, which is more widely used.
* Clean up layout of C++ unit test code. Consolidate files with test data. 
* Add factory methods for creating spatial database writers to bypass validators that require files to exist. This is a result of using Pyre validators to check that spatial and temporal database file exist (this triggers early notification of any missing spatial or temporal database files).
* Improve continuous integration testing via docker containers for multiple Linux distributions and Travis CI.
* This is the final release for Python 2.7. The next release will only support Python 3.6 and later.

## Version 1.10.1 (2019/07/29)

* Fix bug in composite spatial database. Allow queries that only use one of the two spatial databases.


## Version 1.10.0 (2019/07/01)

* Added UserFunctionDB for user-specified analytical functions.
* Changed GravityField::gravAcceleration() to GravityField::gravityAcc for consistency with gravityDir().
* Add methods for computing density scale and pressure scale from other scales. Only three of length scale, time scale, pressure scale, and density scale are independent.

## Version 1.9.10 (2017/07/07)

  Improved error messages when reading SimpleDB and SimpleGridDB files.
  Provide information about the number of points read and instructions on
  how to fix common problems.

## Version 1.9.9 (2017/06/19)

  BUGFIX: Improved Python interface to SimpleGridDB to make it
  possible to write 1-D and 2-D files.

  Improve validation error messages; some error messages were missing
  spatial database label.

## Version 1.9.8 (2017/03/24)

* Added temperature scale to Nondimensional.
* Changed query values for gravity field (GravityField) from x, y, z to gravity_field_x, gravity_field_y, gravity_field_z. This makes it easier to use gravity within applications with other fields.

## Version 1.9.7 (2016/10/13)

* Add version information.
* Fix compilation issues associated with gcc-6.x.
* Added configuration for testing via Travis.

## Version 1.9.6 (2016/06/14)

* Improve checking for parsing errors for spatial database files.

## Version 1.9.5 (2015/02/13)

* Added check for no data when validating UniformDB.

## Version 1.9.4 (2014/08/19)

* Updates to files for compatibility with automake v1.14.1. Also changed libsrc layout to eliminate need to export header files.

## Version 1.9.3 (2013/09/17)

* Removed use of Python eggs in configuration and install.

## Version 1.9.2 (2013/06/13)

* Set spatialdata label in template test to avoid error message about unset parameter.

## Version 1.9.1 (2012/12/10)

* Fixed some small memory leaks (mostly in unit tests).  Updated `cit_python.m4` macros to fix configure errors on some systems.

## Version 1.9.0 (2012/10/22)

* Added local origin and rotation angle to projected geographic coordinate system. This provides a local origin to geographic projects that do not necessarily support them in addition to rotated coordinate systems.
* Added SimpleGridDB for efficient querying of data on logical grids. Works in 1-D, 2-D, and 3-D for lower-dimension grids, e.g., 1-D in 3-D space.

## Version 1.8.2 (2012/03/23)

* Added ability to use empty ellipsoid and datum in order to use +init option for Google Earth projections.

## Version 1.8.1 (2012/01/27)

* Fixed parsing of non-derived units (e.g., degree and radian) in for UniformDB spatial databases.

## Version 1.8.0 (2011/11/09)

* Changed to old syntax for catching exceptions for compatibility with Python 2.4.
* Added single precision wrapper for SpatialDB query.

## Version 1.7.1 (2011/07/07)

* Require labels for spatial databases.
* Check for empty filenames.
* Improve error messages.

## Version 0.7.0 (2011/05/06)

* Added check for more than one point in SimpleDB with zero data dimension.
* Permit whitespace in values and data for UniformDB.

## Version 0.6.0 (2010/06/08)

* Permit nondimensionl values in spatial databases.

## Version 0.5.2 (2009/07/06)

* Added `--enable-swig` configure argument because source distribution already contains the SWIG generated files (use `--enable-swig` when using the source repository).

## Version 0.5.1 (2009/07/01)

* Fixed trapping of errors from Python when using units parser.

## Version 0.5.0 (2009/06/19)

* Switched to SWIG for Python modules. Added parsing of units in SimpleDB headers. Added time history files.

## 2007/02/26

* Switched to using numpy arrays as arguments in Python SimpleIOAscii::write(). This greatly simplifies creating a database from Python. Simplified GenSimpleDBApp so that it is all Python.

## 2007/01/01

* Changed interface so that it no longer uses pointers to pointers when passing arrays as arugments. You now pass just a pointer to where the values are to be stored. This makes the user interface cleaner.
* Numpy version >= 1.0 is now required (previous changeset).

## 2007/01/07

* Changed interfaces to allow spatial dimension of coordinate systems to be 1-D and 2-D instead of just 3-D.
