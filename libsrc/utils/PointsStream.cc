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
#include <iomanip> // USES std::setprecision(), std::width()
#include <vector> // USES std::vector
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor
spatialdata::utils::PointsStream::PointsStream(void) :
  _commentFlag("#"),
  _fieldWidth(14),
  _precision(5),
  _pIn(&std::cin),
  _pOut(&std::cout)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor
spatialdata::utils::PointsStream::~PointsStream(void)
{ // destructor
} // destructor

// ----------------------------------------------------------------------
// Set input stream.
void
spatialdata::utils::PointsStream::input(std::istream* pIn)
{ // input
  _pIn = pIn;
} // input

// ----------------------------------------------------------------------
// Set output stream.
void
spatialdata::utils::PointsStream::output(std::ostream* pOut)
{ // output
  _pOut = pOut;
} // output

// ----------------------------------------------------------------------
// Read points from stdin.
void
spatialdata::utils::PointsStream::read(double** ppPoints,
				       int* pNumPts,
				       int* pNumDims) const
{ // read
  assert(0 != _pIn);

  size_t numPts = 0;
  size_t numDims = 3;

  const size_t initialCapacity = numDims*256;
  std::vector<double> buffer(initialCapacity);

  size_t capacity = initialCapacity;
  size_t index = 0;
  while(!_pIn->eof() && _pIn->good()) {
    if (numPts*numDims >= capacity) {
      capacity *= 2;
      buffer.resize(capacity);
    } // if
    for (size_t iDim=0; iDim < numDims; ++iDim)
      *_pIn >> buffer[index++];
    if (_pIn->good())
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
} // read

// ----------------------------------------------------------------------
// Write points to stdout.
void
spatialdata::utils::PointsStream::write(const double* pPoints,
					const int numPts,
					const int numDims) const
{ // write
  assert(0 != _pOut);

  *_pOut
    << std::resetiosflags(std::ios::fixed)
    << std::setiosflags(std::ios::scientific)
    << std::setprecision(_precision);

  for (size_t iPoint=0, index=0; iPoint < numPts; ++iPoint) {
    for (size_t iDim=0; iDim < numDims; ++iDim)
      *_pOut << std::setw(_fieldWidth) << pPoints[index++];
    *_pOut << "\n";
  } // for

} // write

// End of file
