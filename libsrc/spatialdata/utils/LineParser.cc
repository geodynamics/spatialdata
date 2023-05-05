// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2023 University of California, Davis
//
// See LICENSE.md for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "LineParser.hh" // implementation of class methods

#include <iostream>
#include <sstream>

// ----------------------------------------------------------------------
spatialdata::utils::LineParser::LineParser(std::istream& sin,
                                           const char* delimiter,
                                           const size_t bufsize) :
    _in(sin),
    _delimiter(delimiter),
    _bufsize(bufsize),
    _buffer(0) { // constructor
    _buffer = new char[bufsize];
} // constructor


// ----------------------------------------------------------------------
spatialdata::utils::LineParser::~LineParser(void) { // destructor
    delete[] _buffer;_buffer = 0;
} // destructor


// ----------------------------------------------------------------------
const std::string&
spatialdata::utils::LineParser::next(void) {
    if (_eatwhitespace) {
        _in >> std::ws;
    }
    _in.getline(_buffer, _bufsize);
    _value = _buffer;
    size_t pos = _value.find(_delimiter);
    while (0 == pos && !_in.eof() && _in.good()) {
        if (_eatwhitespace) {
            _in >> std::ws;
        }
        _in.getline(_buffer, _bufsize);
        _value = _buffer;
        pos = _value.find(_delimiter);
    } // while
    const size_t last = (pos == std::string::npos) ? _value.length() : pos;
    _value = _value.substr(0, last);
    return _value;
} // next


// ----------------------------------------------------------------------
// Ignore input until character read.
void
spatialdata::utils::LineParser::ignore(const char marker) { // ignore
    _in.ignore(_bufsize, marker);
} // ignore


// ----------------------------------------------------------------------
// Set eating whitespace flag.
void
spatialdata::utils::LineParser::eatwhitespace(const bool flag) { // eatwhitespace
    _eatwhitespace = flag;
} // eatwhitespace


// ----------------------------------------------------------------------
// Putback string.
void
spatialdata::utils::LineParser::putback(const std::string& buffer) { // putback
    const size_t size = buffer.length();
    for (int i = size-1; i >= 0; --i) {
        _in.putback(buffer[i]);
    }
    _in.clear();
} // putback


// End of file
