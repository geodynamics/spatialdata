// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2012 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
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
  // Initialize Python interpreter if it is not already initialized.
  _alreadyInitialized = Py_IsInitialized();
  if (!_alreadyInitialized)
    Py_Initialize();

  // Should check for NULL, decode the exception, and throw a C++ equivalent
  PyObject* mod = PyImport_ImportModule("pyre.units");
  if (!mod) {
    throw std::runtime_error("Could not import module 'pyre.units'.");
  } // if
  PyObject* cls = PyObject_GetAttrString(mod, "parser");
  if (!cls) {
    throw std::runtime_error("Could not get 'parser' attribute in pyre.units module.");
  } // if
  _parser = PyObject_CallFunctionObjArgs(cls, NULL);
  if (!_parser) {
    throw std::runtime_error("Could not create parser Python object.");
  } // if
  Py_DECREF(cls);
  Py_DECREF(mod);
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::units::Parser::~Parser(void)
{ // destructor
  Py_CLEAR(_parser);

  if (!_alreadyInitialized)
    Py_Finalize();
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
   */
  PyObject* pyUnit  = PyObject_CallMethod(_parser, "parse", "s", units);
  if (!pyUnit) {
    if (PyErr_Occurred()) {
      PyErr_Clear();
    } // if      
    std::ostringstream msg;
    msg << "Could not parse units string '" << units << "'.";
    throw std::runtime_error(msg.str());
  } // if
  PyObject* pyScale = PyObject_GetAttrString(pyUnit, "value");
  if (!pyScale) {
    Py_DECREF(pyUnit);
    if (PyErr_Occurred()) {
      PyErr_Clear();
    } // if
    std::ostringstream msg;
    msg << "Could not get floating point value when parsing units string '"
	<< units << "'.";
    throw std::runtime_error(msg.str());
  } // if
  if (!PyFloat_Check(pyScale)) {
    Py_DECREF(pyScale);
    Py_DECREF(pyUnit);
    PyErr_Clear();
    std::ostringstream msg;
    msg << "Could not get floating point value when parsing units string '"
	<< units << "'.";
    throw std::runtime_error(msg.str());
  } // if

  scale = PyFloat_AsDouble(pyScale);
  Py_DECREF(pyScale);
  Py_DECREF(pyUnit);

  return scale;
} // parser


// End of file 
