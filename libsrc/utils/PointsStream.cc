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

#include "PointsStream.hh" // Implementation of class methods

#include <iostream> // USES std::cout, std::cin
#include <fstream> // USES std::ifstream, std::ofstream
#include <iomanip> // USES std::setprecision(), std::width()
#include <vector> // USES std::vector
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::utils::PointsStream::PointsStream(void) :
  _commentFlag("#"),
  _filename(""),
  _fieldWidth(14),
  _precision(5)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::utils::PointsStream::~PointsStream(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Read points from stdin.
void
spatialdata::utils::PointsStream::read(double** ppPoints,
				       int* pNumPts,
				       int* pNumDims) const
{ // read
  std::istream* pIn = (0 != _filename.length()) ?
    new std::ifstream(_filename.c_str()) :
    &std::cin;

  size_t numPts = 0;
  size_t numDims = 3;

  const size_t initialCapacity = numDims*256;
  std::vector<double> buffer(initialCapacity);

  size_t capacity = initialCapacity;
  size_t index = 0;
  while(!pIn->eof() && pIn->good()) {
    if (numPts*numDims >= capacity) {
      capacity *= 2;
      buffer.resize(capacity);
    } // if
    for (size_t iDim=0; iDim < numDims; ++iDim)
      *pIn >> buffer[index++];
    if (pIn->good())
      ++numPts;
  } // while

  if (0 != ppPoints) {
    const size_t size = numPts * numDims;
    double* pPoints = (size > 0) ? new double[size] : 0;
    for (int i=0; i < size; ++i)
      pPoints[i] = buffer[i];
    *ppPoints = pPoints;
  } // if
  if (0 != pNumPts)
    *pNumPts = numPts;
  if (0 != pNumDims)
    *pNumDims = numDims;
  if (&std::cin != pIn)
    delete pIn;
} // read

// ----------------------------------------------------------------------
// Write points to stdout.
void
spatialdata::utils::PointsStream::write(const double* pPoints,
					const int numPts,
					const int numDims) const
{ // write
  std::ostream* pOut = (0 != _filename.length()) ?
    new std::ofstream(_filename.c_str()) :
    &std::cout;

  *pOut
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(_precision);

  for (size_t iPoint=0, index=0; iPoint < numPts; ++iPoint) {
    for (size_t iDim=0; iDim < numDims; ++iDim)
      *pOut << std::setw(_fieldWidth) << pPoints[index++];
    *pOut << "\n";
  } // for

  if (&std::cout != pOut)
    delete pOut;
} // write

// End of file
