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

#include "SpatialDB.hh" // USES SimpleDB
#include "SimpleDB.hh" // USES SimpleDB
#include "SimpleDBQuery.hh" // implementation of class methods

#include "SimpleDBData.hh" // USEs SimpleDBData

#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <sstream> // USES std::ostringsgream
#include <algorithm> // USES std::fill(), std::lower_bound(), std::distance
#include "Exception.hh" // USES OutOfBounds

#include <math.h> // USES MAXFLOAT
#if !defined(MAXFLOAT)
#define MAXFLOAT 1e+30
#endif

#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Default constructor.
spatialdata::spatialdb::SimpleDBQuery::SimpleDBQuery(const SimpleDB& db) :
  _queryType(SimpleDB::LINEAR),
  _db(db),
  _queryVals(0),
  _querySize(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor.
spatialdata::spatialdb::SimpleDBQuery::~SimpleDBQuery(void)
{ // destructor
  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;
} // destructor
  
// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleDBQuery::queryType(const SimpleDB::QueryEnum queryType)
{ // queryType
  _queryType = queryType;
} // queryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleDBQuery::queryVals(const char** names,
						 const int numVals)
{ // queryVals
  assert(0 != _db._data);
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << _db.label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(0 != names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    int iName = 0;
    const int numNames = _db._data->numValues();
    while (iName < numNames) {
      if (0 == strcasecmp(names[iVal], _db._data->name(iName)))
	break;
      ++iName;
    } // while
    if (iName >= numNames) {
      std::ostringstream msg;
      msg
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< _db.label() << ". Available values are:";
      for (int iName=0; iName < numNames; ++iName)
	msg << "\n  " << _db._data->name(iName);
      msg << "\n";
      throw std::runtime_error(msg.str());
    } // if
    _queryVals[iVal] = iName;
  } // for
} // QueryVals

// ----------------------------------------------------------------------
// Query the database.
void
spatialdata::spatialdb::SimpleDBQuery::query(double* vals,
					     const int numVals,
					     const double* coords,
					     const int numDims,
			      const spatialdata::geocoords::CoordSys* pCSQuery)
{ // query
  assert(0 != coords);

  if (0 == _querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << _db.label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } // if
  else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << _db.label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } // if

  const int numLocs = 1;
  _q[0] = 0.0;
  _q[1] = 0.0;
  _q[2] = 0.0;
  for (int i=0; i < numDims; ++i)
    _q[i] = coords[i];
  spatialdata::geocoords::Converter::convert(_q, numLocs, numDims, 
					     _db._cs, pCSQuery);

  switch (_queryType)
    { // switch
    case SimpleDB::LINEAR :
      _queryLinear(vals, numVals);
      break;
    case SimpleDB::NEAREST :
      _queryNearest(vals, numVals);
      break;
    default :
      throw std::runtime_error("Could not find requested query type.");
    } // switch
} // query

// ----------------------------------------------------------------------
// Query database using nearest neighbor algorithm.
void
spatialdata::spatialdb::SimpleDBQuery::_queryNearest(double* vals,
						     const int numVals)
{ // _queryNearest
  assert( (0 < numVals && 0 != vals) ||
	  (0 == numVals && 0 == vals) );
  assert(0 != _db._data);
  assert(numVals == _querySize);

  int iNear = 0;
  const int spaceDim = _db._data->spaceDim();
  double pt[3];
  _setPoint3(pt, _db._data->coordinates(iNear), spaceDim);
  double nearDist = _distSquared(_q, pt);

  const int numLocs = _db._data->numLocs();
  for (int iLoc=1; iLoc < numLocs; ++iLoc) {
    _setPoint3(pt, _db._data->coordinates(iLoc), spaceDim);
    const double dist = _distSquared(_q, pt);
    if (dist < nearDist) {
      nearDist = dist;
      iNear = iLoc;
    } // if
  } // for

  const double* nearVals = _db._data->data(iNear);
  const int querySize = _querySize;
  for (int iVal=0; iVal < querySize; ++iVal)
    vals[iVal] = nearVals[_queryVals[iVal]];
} // _queryNearest

// ----------------------------------------------------------------------
// Query database using linear interpolation algorithm.
void
spatialdata::spatialdb::SimpleDBQuery::_queryLinear(double* vals,
						    const int numVals)
{ // _queryLinear
  assert( (0 < numVals && 0 != vals) ||
	  (0 == numVals && 0 == vals) );
  assert(0 != _db._data);
  assert(numVals == _querySize);

  if (0 == _db._data->dataDim()) {
    const int index = 0;
    const double* nearVals = _db._data->data(index);
    const int querySize = _querySize;
    for (int iVal=0; iVal < querySize; ++iVal)
      vals[iVal] = nearVals[_queryVals[iVal]];
  } else { // else
    // Find nearest locations in database
    _findNearest();

    // Get interpolation weights
    std::vector<WtStruct> weights;
    _getWeights(&weights);

    // Interpolate values
    const int numWts = weights.size();
    const int querySize = _querySize;
    for (int iVal=0; iVal < querySize; ++iVal) {
      double val = 0;
      for (int iWt=0; iWt < numWts; ++iWt) {
	const int iLoc = _nearest[weights[iWt].nearIndex];
	const double* locVals = _db._data->data(iLoc);
	val += weights[iWt].wt * locVals[_queryVals[iVal]];
      } // for
      vals[iVal] = val;
    } // for
  } // else
} // _queryLinear

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findNearest(void)
{ // _findNearest
  assert(0 != _db._data);

  const int maxnear = 100;
  const int numLocs = _db._data->numLocs();
  const int nearSize = (numLocs < maxnear) ? numLocs : maxnear;
  _nearest.resize(nearSize);
  std::fill(_nearest.begin(), _nearest.end(), -1);

  std::vector<double> nearestDist(nearSize);
  std::fill(nearestDist.begin(), nearestDist.end(), MAXFLOAT);
  
  // find closest nearSize points
  double pt[3];
  const int spaceDim = _db._data->spaceDim();
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    // use square of distance to find closest
    _setPoint3(pt, _db._data->coordinates(iLoc), spaceDim);
    const double dist2 = _distSquared(_q, pt);

    // find place in nearest list if it exists
    const std::vector<double>::iterator pNearDist = 
      std::lower_bound(nearestDist.begin(), nearestDist.end(),
		       dist2);
    if (dist2 <= *pNearDist) { // if found place in nearest list
#if !defined(_RWSTD_NO_CLASS_PARTIAL_SPEC)
      int index = std::distance(nearestDist.begin(), pNearDist);
#else
      int index = 0;
      std::distance(nearestDist.begin(), pNearDist, index);
#endif
      
      // move values to allow insertion of current
      for (int moveIndex = nearSize-1; moveIndex > index; --moveIndex) {
	nearestDist[moveIndex] = nearestDist[moveIndex-1];
	_nearest[moveIndex] = _nearest[moveIndex-1];
      } // for
      if (index < nearSize) {
	// insert current
	nearestDist[index] = dist2;
	_nearest[index] = iLoc;
      } // if
    } // if
  } // for
} // _findNearest

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_getWeights(std::vector<WtStruct>* pWeights)
{ // _getWeights
  assert(0 != _db._data);
  assert(0 != pWeights);

  /* Start with nearest point. Add next nearest points as necessary
   * to obtain appropriate interpolation. For example, adding 1 point
   * results in linear interpolation, adding 2 results in areal
   * interpolation, etc.
   */
  
  if (0 == _db._data->dataDim()) {
    const int numWts = 1;
    pWeights->resize(numWts);
    _findPointPt(pWeights);
  } else if (1 == _db._data->dataDim()) {
    const int numWts = 2;
    pWeights->resize(numWts);
    _findPointPt(pWeights);
    _findLinePt(pWeights);
  } else if (2 == _db._data->dataDim()) {
    const int numWts = 3;
    pWeights->resize(numWts);
    _findPointPt(pWeights);
    _findLinePt(pWeights);
    _findAreaPt(pWeights);
  } else if (3 == _db._data->dataDim()) {
    const int numWts = 4;
    pWeights->resize(numWts);
    _findPointPt(pWeights);
    _findLinePt(pWeights);
    _findAreaPt(pWeights);
    _findVolumePt(pWeights);
  } else
    throw std::runtime_error("Could not set weights for unknown data dimension.");
} // _getWeights

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findPointPt(std::vector<WtStruct>* pWeights)
{ // _findPointPt
  assert(0 != _db._data);
  assert(0 != pWeights);

  (*pWeights)[0].wt = 1.0;
  (*pWeights)[0].nearIndex = 0;
} // _findPointPt

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findLinePt(std::vector<WtStruct>* pWeights)
{ // _findPointPt
  assert(0 != _db._data);
  assert(0 != pWeights);
  
  const int spaceDim = _db._data->spaceDim();

  // best case is to use next nearest pt
  const int nearIndexA = (*pWeights)[0].nearIndex;
  int nearIndexB = nearIndexA + 1;

  const int locIndexA = _nearest[nearIndexA];
  double ptA[3];
  _setPoint3(ptA, _db._data->coordinates(locIndexA), spaceDim);

  double wtA = 0;
  double wtB = 0;
  double ptB[3];

  // find nearest pt where we can interpolate
  const int nearSize = _nearest.size();
  while (nearIndexB < nearSize) {
    const int locIndexB = _nearest[nearIndexB];
    _setPoint3(ptB, _db._data->coordinates(locIndexB), spaceDim);

    // wtA = DotProduct(pb, ab) / DotProduct(ab, ab)
    // wtB = DotProduct(ap, ab) / DotProduct(ab, ab)
    const double abX = ptB[0] - ptA[0];
    const double abY = ptB[1] - ptA[1];
    const double abZ = ptB[2] - ptA[2];
    const double abdotab = abX*abX + abY*abY + abZ*abZ;
    const double pbdotab = 
      (ptB[0]-_q[0])*abX + (ptB[1]-_q[1])*abY + (ptB[2]-_q[2])*abZ;
    const double apdotab = 
      (_q[0]-ptA[0])*abX + (_q[1]-ptA[1])*abY + (_q[2]-ptA[2])*abZ;
    wtA = pbdotab / abdotab;
    wtB = apdotab / abdotab;
    
    const double tolerance = 1e-06;
    if (wtA >= -tolerance &&
	wtB >= -tolerance)
      // found 2nd point if weights are positive within tolerance level
      // (i.e. interpolation, not extrapolation)
      break;
    ++nearIndexB;
  } // while
  if (nearIndexB >= nearSize)
    throw OutOfBounds("Could not find points for linear interpolation.");
  (*pWeights)[0].wt = wtA;
  (*pWeights)[1].wt = wtB;
  (*pWeights)[1].nearIndex = nearIndexB;
} // _findLinePt

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findAreaPt(std::vector<WtStruct>* pWeights)
{ // _findAreaPt
  assert(0 != _db._data);
  assert(0 != pWeights);

  const int spaceDim = _db._data->spaceDim();

  // best case is to use next nearest pt
  const int nearIndexA = (*pWeights)[0].nearIndex;
  const int locIndexA = _nearest[nearIndexA];
  double ptA[3];
  _setPoint3(ptA, _db._data->coordinates(locIndexA), spaceDim);

  const int nearIndexB = (*pWeights)[1].nearIndex;
  const int locIndexB = _nearest[nearIndexB];
  double ptB[3];
  _setPoint3(ptB, _db._data->coordinates(locIndexB), spaceDim);

  double wtA = 0;
  double wtB = 0;
  double wtC = 0;
  double ptC[3];

  // find nearest pt where we can interpolate
  const int nearSize = _nearest.size();
  int nearIndexC = nearIndexB + 1;
  while (nearIndexC < nearSize) {
    const int locIndexC = _nearest[nearIndexC];
    _setPoint3(ptC, _db._data->coordinates(locIndexC), spaceDim);

    double areaABC = 0;
    double dirABC[3];
    _area(&areaABC, dirABC, ptA, ptB, ptC);

#if 0
    // Alternate method of determining collinearity.
    // Compute unit vectors AB and AC, then compute the dot product.
    // If the absolute value of the dot product is somewhat less than 1,
    // the points are not collinear.
    double vecAB[3];
    double vecAC[3];
    double magAB = 0.0;
    double magAC = 0.0;
    for (int iDir=0; iDir < numCoords; ++iDir) {
      vecAB[iDir] = ptA[iDir] - ptB[iDir];
      vecAC[iDir] = ptA[iDir] - ptC[iDir];
      magAB += vecAB[iDir] * vecAB[iDir];
      magAC += vecAC[iDir] * vecAC[iDir];
    } // for
    magAB = sqrt(magAB);
    magAC = sqrt(magAC);
    double abdotac = 0.0;
    for (int iDir=0; iDir < numCoords; ++iDir) {
      abdotac += (vecAB[iDir]/magAB) * (vecAC[iDir]/magAC);
    } // for
    
    const double tolerance = 0.98;
    if (fabs(abdotac) < tolerance) {
#else
    // make sure A,B,C are not collinear by checking if area of
    // triangle ABC is not a tiny fraction of the distance AB
    
    // length(ab)^2
    const double ab2 = 
      pow(ptA[0]-ptB[0], 2) +
      pow(ptA[1]-ptB[1], 2) +
      pow(ptA[2]-ptB[2], 2);

    const double tolerance = 1.0e-06;
    if (areaABC > tolerance*ab2) {
#endif
      // project P onto abc plane
      double qProj[3];
      const double qmod = 
	dirABC[0]*_q[0] + dirABC[1]*_q[1] + dirABC[2]*_q[2];
      qProj[0] = _q[0] - dirABC[0]*qmod;
      qProj[1] = _q[1] - dirABC[1]*qmod;
      qProj[2] = _q[2] - dirABC[2]*qmod;

      // wtA = areaBCQ / areaABC * DotProduct(dirBCQ, dirABC);
      double areaBCQ = 0;
      double dirBCQ[3];
      _area(&areaBCQ, dirBCQ, ptB, ptC, qProj);
      wtA = areaBCQ/areaABC * (dirBCQ[0]*dirABC[0] + 
			       dirBCQ[1]*dirABC[1] +
			       dirBCQ[2]*dirABC[2]);

      // wtB = areaCAQ / areaABC * DotProduct(dirCAQ, dirABC);
      double areaCAQ = 0;
      double dirCAQ[3];
      _area(&areaCAQ, dirCAQ, ptC, ptA, qProj);
      wtB = areaCAQ/areaABC * (dirCAQ[0]*dirABC[0] + 
			       dirCAQ[1]*dirABC[1] +
			       dirCAQ[2]*dirABC[2]);

      // wtC = areaABQ / areaABC * DotProduct(dirABQ, dirABC);
      double areaABQ = 0;
      double dirABQ[3];
      _area(&areaABQ, dirABQ, ptA, ptB, qProj);
      wtC = areaABQ/areaABC * (dirABQ[0]*dirABC[0] + 
			       dirABQ[1]*dirABC[1] +
			       dirABQ[2]*dirABC[2]);

      const double tolerance = 1e-06;
      if (wtA >= -tolerance &&
	  wtB >= -tolerance &&
	  wtC >= -tolerance)
	// found 3rd point if weights are positive within tolerance level
	// (i.e. interpolation, not extrapolation)
	break;
    } // if
    ++nearIndexC;
  } // while
  if (nearIndexC >= nearSize)
    throw OutOfBounds("Could not find points for areal interpolation.");
  (*pWeights)[0].wt = wtA;
  (*pWeights)[1].wt = wtB;
  (*pWeights)[2].wt = wtC;
  (*pWeights)[2].nearIndex = nearIndexC;
} // _findAreaPt

// ----------------------------------------------------------------------
void
spatialdata::spatialdb::SimpleDBQuery::_findVolumePt(std::vector<WtStruct>* pWeights)
{ // _findVolumePt
  assert(0 != _db._data);
  assert(0 != pWeights);

  // best case is to use next nearest pt

  const int spaceDim = _db._data->spaceDim();

  const int nearIndexA = (*pWeights)[0].nearIndex;
  const int locIndexA = _nearest[nearIndexA];
  double ptA[3];
  _setPoint3(ptA, _db._data->coordinates(locIndexA), spaceDim);

  const int nearIndexB = (*pWeights)[1].nearIndex;
  const int locIndexB = _nearest[nearIndexB];
  double ptB[3];
  _setPoint3(ptB, _db._data->coordinates(locIndexB), spaceDim);

  const int nearIndexC = (*pWeights)[2].nearIndex;
  const int locIndexC = _nearest[nearIndexC];
  double ptC[3];
  _setPoint3(ptC, _db._data->coordinates(locIndexC), spaceDim);

  double wtA = 0;
  double wtB = 0;
  double wtC = 0;
  double wtD = 0;
  double ptD[3];

  // find nearest pt where we can interpolate
  const int nearSize = _nearest.size();
  int nearIndexD = nearIndexC + 1;
  while (nearIndexD < nearSize) {
    const int locIndexD = _nearest[nearIndexD];
    _setPoint3(ptD, _db._data->coordinates(locIndexD), spaceDim);
    
    // make sure A,B,C,D are not coplanar by checking if volume of
    // tetrahedron ABCD is not a tiny fraction of the distance AB
    
    // volume abcd
    const double abcd = _volume(ptA, ptB, ptC, ptD);
    
    // ab = length(ab)
    const double ab3 = 
      pow(pow(ptA[0] - ptB[0], 2) +
	  pow(ptA[1] - ptB[1], 2) +
	  pow(ptA[2] - ptB[2], 2), 3);

    const double tolerance = 1.0e-06;
    if (fabs(abcd) > tolerance*ab3) {

      // volume pbcd
      const double pbcd = _volume(_q, ptB, ptC, ptD);
      // wtA = vol(pbcd)/vol(abcd)
      wtA = pbcd / abcd;

      // volume apcd
      const double apcd = _volume(ptA, _q, ptC, ptD);
      // wtB = vol(apcd)/vol(abcd)
      wtB = apcd / abcd;

      // volume abpd
      const double abpd = _volume(ptA, ptB, _q, ptD);
      // wtC = vol(abpd)/vol(abcd)
      wtC = abpd / abcd;

      // volume abcp
      const double abcp = _volume(ptA, ptB, ptC, _q);
      // wtD = vol(abcp)/vol(abcd)
      wtD = abcp / abcd;

      const double tolerance = 1e-06;
      if (wtA >= -tolerance &&
	  wtB >= -tolerance &&
	  wtC >= -tolerance &&
	  wtD >= -tolerance)
	// found 4th point if weights are positive within tolerance level
	// (i.e. interpolation, not extrapolation)
	break;
    } // if
    ++nearIndexD;
  } // while
  if (nearIndexD >= nearSize)
    throw OutOfBounds("Could not find points for volumetric interpolation.");
  (*pWeights)[0].wt = wtA;
  (*pWeights)[1].wt = wtB;
  (*pWeights)[2].wt = wtC;
  (*pWeights)[3].wt = wtD;
  (*pWeights)[3].nearIndex = nearIndexD;
} // _findVolumePt

// ----------------------------------------------------------------------
// Set coordiantes of point in 3-D space using coordinates in
// current coordinate system.
void
spatialdata::spatialdb::SimpleDBQuery::_setPoint3(double pt3[3],
						  const double* pt,
						  const int spaceDim)
{ // _setPoint3
  pt3[0] = 0.0;
  pt3[1] = 0.0;
  pt3[2] = 0.0;
  memcpy(pt3, pt, spaceDim*sizeof(double));
} // _setPoint3

// ----------------------------------------------------------------------
// Compute square of distance between points A and B.
double
spatialdata::spatialdb::SimpleDBQuery::_distSquared(const double a[3],
						    const double b[3])
{ // _distSquared
  const double abX = b[0]-a[0];
  const double abY = b[1]-a[1];
  const double abZ = b[2]-a[2];
  const double dist2 = abX*abX + abY*abY + abZ*abZ;
  return dist2;
} // _distSquared

// ----------------------------------------------------------------------
/* Compute area and "direction" of triangle abc. Direction is vector
 * normal to triangular surface.
 */
void
spatialdata::spatialdb::SimpleDBQuery::_area(double* pArea,
					     double dir[3],
					     const double* a,
					     const double* b,
					     const double* c)
{ // _area
  assert(0 != pArea);
  assert(0 != dir);
  
  // AB
  const double abX = b[0] - a[0];
  const double abY = b[1] - a[1];
  const double abZ = b[2] - a[2];
  
  // AC
  const double acX = c[0] - a[0];
  const double acY = c[1] - a[1];
  const double acZ = c[2] - a[2];
  
  dir[0] = abY*acZ - abZ*acY;
  dir[1] = abZ*acX - abX*acZ;
  dir[2] = abX*acY - abY*acX;
  
  *pArea = sqrt(dir[0]*dir[0] + dir[1]*dir[1] + dir[2]*dir[2]);
  if (0 != *pArea) {
    dir[0] /= *pArea;
    dir[1] /= *pArea;
    dir[2] /= *pArea;
  } // if
  *pArea *= 0.5;
} // _area

// ----------------------------------------------------------------------
double
spatialdata::spatialdb::SimpleDBQuery::_volume(const double a[3],
					       const double b[3],
					       const double c[3],
					       const double d[3])
/* Compute volume of tetrahedral defined by four points. */
{ // _volume
  const double det1 = 
    b[0] * (c[1]*d[2] - c[2]*d[1]) +
    b[1] * (c[2]*d[0] - c[0]*d[2]) +
    b[2] * (c[0]*d[1] - c[1]*d[0]);
  const double det2 = 
   -c[0] * (d[1]*a[2] - d[2]*a[1]) - 
    c[1] * (d[2]*a[0] - d[0]*a[2]) - 
    c[2] * (d[0]*a[1] - d[1]*a[0]);
  const double det3 = 
    d[0] * (a[1]*b[2] - a[2]*b[1]) + 
    d[1] * (a[2]*b[0] - a[0]*b[2]) + 
    d[2] * (a[0]*b[1] - a[1]*b[0]);
  const double det4 = 
   -a[0] * (b[1]*c[2] - b[2]*c[1]) - 
    a[1] * (b[2]*c[0] - b[0]*c[2]) - 
    a[2] * (b[0]*c[1] - b[1]*c[0]);
  return (det1 + det2 + det3 + det4) / 6.0;
} // _volume


// End of file 
