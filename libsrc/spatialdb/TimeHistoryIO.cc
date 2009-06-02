// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
//                           Brad T. Aagaard
//                        U.S. Geological Survey
//
// <LicenseText>
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "TimeHistoryIO.hh" // Implementation of class methods

#include "spatialdata/utils/LineParser.hh" // USES LineParser
#include "spatialdata/units/Parser.hh" // USES Parser

#include <fstream> // USES std::ifstream, std::ofstream
#include <iomanip> // USES setw(), setiosflags(), resetiosflags()

#include <cassert> // USES assert()
#include <stdexcept> // USES std::runtime_error
#include <sstream> // USES std::ostringstream

// ----------------------------------------------------------------------
const char* spatialdata::spatialdb::TimeHistoryIO::HEADER =
  "#TIME HISTORY ascii";

// ----------------------------------------------------------------------
// Read time history file.
void
spatialdata::spatialdb::TimeHistoryIO::read(double** time,
					    double** amplitude,
					    int* npts,
					    const char* filename)
{ // read
  assert(0 != time);
  assert(0 != amplitude);
  assert(0 != npts);

  try {
    std::ifstream filein(filename);
    if (!filein.is_open() || !filein.good()) {
      std::ostringstream msg;
      msg << "Could not open time history file '" << filename
	  << "' for reading.\n";
      throw std::runtime_error(msg.str());
    } // if

    utils::LineParser parser(filein, "//");
    parser.eatwhitespace(true);

    const int maxIgnore = 256;
    std::string token;
    std::istringstream buffer;
    buffer.str(parser.next());
    buffer.clear();

    const int headerLen = strlen(HEADER);
    std::string hbuffer;
    hbuffer.resize(headerLen+1);
    buffer.read((char*) hbuffer.c_str(), sizeof(char)*headerLen);
    hbuffer[headerLen] = '\0';
    if (0 != strcasecmp(HEADER, hbuffer.c_str())) {
      std::ostringstream msg;
      msg
	<< "Magic header '" << buffer << "' does not match expected header '"
	<< HEADER << "' in time history file '" << filename << "'.\n";
      throw std::runtime_error(msg.str());
    } // if

    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    if (0 != strcasecmp(token.c_str(), "TimeHistory")) {
      std::ostringstream msg;
      msg << "Could not parse '" << token << "' into 'TimeHistory'.\n";
      throw std::runtime_error(msg.str());
    } // else

    std::string timeUnits = "second";
    buffer.str(parser.next());
    buffer.clear();
    buffer >> token;
    while (buffer.good() && token != "}") {
      if (0 == strcasecmp(token.c_str(), "num-points")) {
	buffer.ignore(maxIgnore, '=');
	buffer >> *npts;
      } else if (0 == strcasecmp(token.c_str(), "time-units")) {
	buffer.ignore(maxIgnore, '=');
	buffer >> timeUnits;
      } else {
	std::ostringstream msg;
	msg << "Could not parse '" << token
	    << "' into a TimeHistory setting.";
	throw std::runtime_error(msg.str());
      } // else
      
      buffer.str(parser.next());
      buffer.clear();
      buffer >> token;
    } // while
    if (token != "}" || !filein.good())
      throw std::runtime_error("I/O error while parsing TimeHistory "
			       "settings.");
    
    bool ok = true;
    std::ostringstream msg;
    if (0 == *npts) {
      ok = false;
      msg << "TimeHistory settings must include 'num-points'.\n";
    } // if
    if (*npts <= 0) {
      ok = false;
      msg << "TimeHistory must contain at least one point.\n";
    } // if
    if (!ok)
      throw std::runtime_error(msg.str());

    units::Parser uparser;
    const double scale = uparser.parse(timeUnits.c_str());
    
    const int size = *npts;
    delete[] *time; *time = (size > 0) ? new double[size] : 0;
    delete[] *amplitude; *amplitude = (size > 0) ? new double[size] : 0;
    
    for (int i=0; i < size; ++i) {
      buffer.str(parser.next());
      buffer.clear();
      buffer >> (*time)[i];
      buffer >> (*amplitude)[i];
      (*amplitude)[i] *= scale;
    } // for
    
    if (!filein.good())
      throw std::runtime_error("Unknown error while reading.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while reading time history file '"
	<< filename << "'.\n"
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while reading time history file '"
	<< filename << "'.\n";
    throw std::runtime_error(msg.str());
  } // try/catch
} // read
  
// ----------------------------------------------------------------------
// Read time history file.
void
spatialdata::spatialdb::TimeHistoryIO::write(const double* time,
					     const int nptsT,
					     const double* amplitude,
					     const int nptsA,
					     const char* timeUnits,
					     const char* filename)
{ // write
  assert( (0 == nptsT && 0 == time) ||
	  (0 < nptsT && 0 != time) );
  assert( (0 == nptsA && 0 == amplitude) ||
	  (0 < nptsA && 0 != amplitude) );

  try {
    if (nptsT != nptsA) {
      std::ostringstream msg;
      msg << "Number of time stamps (" << nptsT << ") does not match the "
	  << "number of amplitude points (" << nptsA << ").";
      throw std::runtime_error(msg.str());
    } // if

    std::ofstream fileout(filename);
    if (!fileout.is_open() || !fileout.good()) {
      std::ostringstream msg;
      msg << "Could not open time history file " << filename
	  << "for writing.\n";
      throw std::runtime_error(msg.str());
    } // if
    
    const int npts = nptsA;
    
    fileout
      << HEADER << "\n"
      << "TimeHistory {\n"
      << "  num-points = " << std::setw(6) << npts << "\n"
      << "  time-units = " << timeUnits << "\n"
      << "}\n";
    if (!fileout.good())
      throw std::runtime_error("I/O error while writing TimeHistory "
			       "settings.");

    fileout
      << std::resetiosflags(std::ios::fixed)
      << std::setiosflags(std::ios::scientific)
      << std::setprecision(6);
    for (int i=0; i < npts; ++i)
      fileout << std::setw(14) << time[i]
	      << std::setw(14) << amplitude[i]
	      << "\n";
    if (!fileout.good())
      throw std::runtime_error("I/O error while writing TimeHistory data.");
  } catch (const std::exception& err) {
    std::ostringstream msg;
    msg << "Error occurred while writing time history file '"
	<< filename << "'.\n" 
	<< err.what();
    throw std::runtime_error(msg.str());
  } catch (...) {
    std::ostringstream msg;
    msg << "Unknown error occurred while writing time history file '"
	<< filename << "'.";
    throw std::runtime_error(msg.str());
  } // try/catch
} // write


// End of file 
