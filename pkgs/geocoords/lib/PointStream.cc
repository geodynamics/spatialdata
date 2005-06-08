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

#include "PointStream.h" // implementation of class methods

#include <iostream> // USES std::istream, std::ostream
#include <vector> // USES std::vector

#include <journal/firewall.h> // USES FIREWALL
#include <pythiautil/FireWallUtil.h> // USES FIREWALL

#include <stdexcept> // USES std::exception

// ----------------------------------------------------------------------
// Default constructor
spatialdata::geocoords::PointStream::PointStream(void)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::geocoords::PointStream::~PointStream(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Load data from input stream into array of points.
void
spatialdata::geocoords::PointStream::load(double** ppPoints,
					  int* pNumLocs,
					  int* pNumCoords,
					  std::istream& sin) const
{ // load
  FIREWALL(0 != ppPoints);
  FIREWALL(0 != pNumLocs);
  FIREWALL(0 != pNumCoords);

  const size_t numCoords = 3;
  const size_t initialCapacity = 256;
  std::vector<double> buffer(numCoords*initialCapacity);

  size_t numVertices = 0;
  size_t capacity = initialCapacity;
  size_t index = 0;
  while(!sin.eof() && sin.good()) {
    if (numVertices >= capacity) {
      capacity *= 2;
      buffer.resize(capacity);
    } // if
    for (size_t iCoord=0; iCoord < numCoords; ++iCoord)
      sin >> buffer[index++];
    if (sin.good())
      ++numVertices;
  } // while

  const size_t size = numCoords*numVertices;
  delete[] *ppPoints; *ppPoints = (size > 0) ? new double[size] : 0;
  for (size_t i=0; i < size; ++i)
    *ppPoints[i] = buffer[i];

  *pNumLocs = numVertices;
  *pNumCoords = numCoords;
} // load

// ----------------------------------------------------------------------
// Dump data from array of points to output stream.
void 
spatialdata::geocoords::PointStream::dump(const double* const pPoints,
					  const int numLocs,
					  const int numCoords,
					  std::ostream& sout) const
{ // dump
  for (int iLoc=0, index=0; iLoc < numLocs; ++iLoc) {
    for (int iCoord=0; iCoord < numCoords; ++iCoord)
      sout << pPoints[index++];
    sout << "\n";
  } // for
} // dump

// version
// $Id: PointStream.cc,v 1.1 2005/06/08 03:20:40 baagaard Exp $

// End of file 
