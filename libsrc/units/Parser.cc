// -*- C++ -*-
//
// ======================================================================
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// {LicenseText}
//
// ======================================================================
//

#include <portinfo>

#include "Parser.hh" // implementation of class methods

#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::runtime_error
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::units::Parser::Parser(void)
{ // constructor
  // Should check for NULL, decode the exception, and throw a C++ equivalent
  PyObject *mod = PyImport_ImportModule("pyre.units");
  PyObject *cls = PyObject_GetAttrString(mod, "parser");
  this->_p      = PyObject_CallFunctionObjArgs(cls, NULL);
  Py_DECREF(cls);
  Py_DECREF(mod);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::units::Parser::~Parser(void)
{ // destructor
  Py_DECREF(this->_p);
} // destructor

// ----------------------------------------------------------------------
// Get SI scaling factor for units given by string. To get value in
// SI units, multiple value given by units by scaling factor.
double
spatialdata::units::Parser::parse(const char* units)
{ // parse
  double scale = 1.0;

  /* Replicate Python functionality given by
   *
   * import pyre.units
   * p = pyre.units.parser()
   * x = p.parse(units) [units is a string]
   * scale = x.value
   *
   * Any nontrivial setup/teardown should be moved to
   * constructor/destructor.
   */
  PyObject *pyUnit  = PyObject_CallFunction(this->_p, "s", units);
  PyObject *pyScale = PyObject_GetAttrString(pyUnit, "value");
  scale             = PyFloat_AsDouble(pyScale);
  Py_DECREF(pyScale);
  Py_DECREF(pyUnit);
  return scale;
} // parser


// End of file 
