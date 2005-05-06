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

#include "SpatialDB.h" // USES SimpleDB
#include "SimpleDB.h" // USES SimpleDB

#include "SimpleDBQuery.h" // implementation of class methods

#include "SimpleDBTypes.h" // USEs SimpleDB::DataStruct

#include <stdexcept> // USES std::runtime_error, std::exception
#include <sstream> // USES std::ostringsgream
#include <algorithm> // USES std::fill(), std::lower_bound(), std::distance

#include <math.h> // USES MAXFLOAT
#if !defined(MAXFLOAT)
#define MAXFLOAT 1e+30
#endif

#if !defined(NO_PYTHIA)
#include "journal/firewall.h" // USES FIREWALL
#include "pythiautil/FireWallUtil.h" // USES FIREWALL
#else
#define FIREWALL assert
#endif

// ----------------------------------------------------------------------
// Default constructor.
spatial::SimpleDBQuery::SimpleDBQuery(const SimpleDB& db) :
  mQueryType(SimpleDB::LINEAR),
  mDB(db),
  mQueryVals(0),
  mQuerySize(0)
{ // constructor
} // constructor

// ----------------------------------------------------------------------
// Default destructor.
spatial::SimpleDBQuery::~SimpleDBQuery(void)
{ // destructor
  delete[] mQueryVals; mQueryVals = 0;
  mQuerySize = 0;
} // destructor
  
// ----------------------------------------------------------------------
// Set query type.
void
spatial::SimpleDBQuery::QueryType(const SimpleDB::QueryEnum queryType)
{ // QueryType
  mQueryType = queryType;
} // QueryType

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatial::SimpleDBQuery::QueryVals(const char** names,
				  const int numVals)
{ // QueryVals
  FIREWALL(0 != mDB.mpData);
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << mDB.Label()
      << "\n must be positive.";
    throw std::runtime_error(msg.str());
  } // if
  FIREWALL(0 != names && 0 < numVals);
  
  mQuerySize = numVals;
  delete[] mQueryVals; mQueryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    int iName = 0;
    const int numNames = mDB.mpData->NumVals;
    while (iName < numNames) {
      if (0 == strcasecmp(names[iVal], mDB.mpData->ValNames[iName].c_str()))
	break;
      ++iName;
    } // while
    if (iName == numNames) {
      std::ostringstream msg;
      msg
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< mDB.Label() << ". Available values are:";
      for (int iName=0; iName < numNames; ++iName)
	msg << "\n  " << mDB.mpData->ValNames[iName];
      throw std::runtime_error(msg.str());
    } // if
    mQueryVals[iVal] = iName;
  } // for
} // QueryVals

// ----------------------------------------------------------------------
// Query the database.
void
spatial::SimpleDBQuery::Query(double** pVals,
			      const int numVals,
			      const double x,
			      const double y,
			      const double z)
{ // Query
  if (0 == mQuerySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << mDB.Label() << "\n"
      << "have not been set. Please call QueryVals() before Query().";
    throw std::runtime_error(msg.str());
  } // if
  else if (numVals != mQuerySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << mDB.Label() << "\n"
      << "(" << mQuerySize << ") does not match size of array provided ("
      << numVals << ").";
    throw std::runtime_error(msg.str());
  } // if
  mQ[0] = x;
  mQ[1] = y;
  mQ[2] = z;
  switch (mQueryType)
    { // switch
    case SimpleDB::LINEAR :
      QueryLinear(pVals, numVals);
      break;
    case SimpleDB::NEAREST :
      QueryNearest(pVals, numVals);
      break;
    default :
      throw std::runtime_error("Could not find requested query type.");
    } // switch
} // Query

// ----------------------------------------------------------------------
// Query database using nearest neighbor algorithm.
void
spatial::SimpleDBQuery::QueryNearest(double** pVals,
				     const int numVals)
{ // QueryNearest
  FIREWALL(0 != pVals);
  FIREWALL(0 != mDB.mpData);
  FIREWALL(numVals == mQuerySize);

  int iNear = 0;
  double nearDist = 
    DistSquared(mQ, SimpleDBTypes::DataCoords(*mDB.mpData, iNear));
  const int numLocs = mDB.mpData->NumLocs;
  for (int iLoc=1; iLoc < numLocs; ++iLoc) {
    const double dist = 
      DistSquared(mQ, SimpleDBTypes::DataCoords(*mDB.mpData, iLoc));
    if (dist < nearDist) {
      nearDist = dist;
      iNear = iLoc;
    } // if
  } // for
  const double* nearVals = SimpleDBTypes::DataVals(*mDB.mpData, iNear);
  const int querySize = mQuerySize;
  for (int iVal=0; iVal < querySize; ++iVal)
    (*pVals)[iVal] = nearVals[mQueryVals[iVal]];
} // QueryNearest

// ----------------------------------------------------------------------
// Query database using linear interpolation algorithm.
void
spatial::SimpleDBQuery::QueryLinear(double** pVals,
				    const int numVals)
{ // QueryLinear
  FIREWALL(0 != pVals);
  FIREWALL(0 != mDB.mpData);
  FIREWALL(numVals == mQuerySize);

  if (SimpleDB::POINT == mDB.mpData->Topology) {
    const int index = 0;
    const double* nearVals = SimpleDBTypes::DataVals(*mDB.mpData, index);
    const int querySize = mQuerySize;
    for (int iVal=0; iVal < querySize; ++iVal)
      (*pVals)[iVal] = nearVals[mQueryVals[iVal]];
  } else { // else
    // Find nearest locations in database
    FindNearest();

    // Get interpolation weights
    std::vector<WtStruct> weights;
    GetWeights(&weights);

    // Interpolate values
    const int numWts = weights.size();
    const int querySize = mQuerySize;
    for (int iVal=0; iVal < querySize; ++iVal) {
      double val = 0;
      for (int iWt=0; iWt < numWts; ++iWt) {
	const int iLoc = mNearest[weights[iWt].NearIndex];
	const double* locVals = SimpleDBTypes::DataVals(*mDB.mpData, iLoc);
	val += weights[iWt].Wt * locVals[mQueryVals[iVal]];
      } // for
      (*pVals)[iVal] = val;
    } // for
  } // else
} // QueryLinear

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::FindNearest(void)
{ // FindNearest
  FIREWALL(0 != mDB.mpData);

  const int maxnear = 100;
  const int numLocs = mDB.mpData->NumLocs;
  const int nearSize = (numLocs < maxnear) ? numLocs : maxnear;
  mNearest.resize(nearSize);
  std::fill(mNearest.begin(), mNearest.end(), -1);

  std::vector<double> nearestDist(nearSize);
  std::fill(nearestDist.begin(), nearestDist.end(), MAXFLOAT);
  
  // find closest nearSize points
  for (int iLoc=0; iLoc < numLocs; ++iLoc) {
    // use square of distance to find closest
    const double dist2 = 
      DistSquared(mQ, SimpleDBTypes::DataCoords(*mDB.mpData, iLoc));

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
	mNearest[moveIndex] = mNearest[moveIndex-1];
      } // for
      if (index < nearSize) {
	// insert current
	nearestDist[index] = dist2;
	mNearest[index] = iLoc;
      } // if
    } // if
  } // for
} // FindNearest

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::GetWeights(std::vector<WtStruct>* pWeights)
{ // GetWeights
  FIREWALL(0 != mDB.mpData);
  FIREWALL(0 != pWeights);

  /* Start with nearest point. Add next nearest points as necessary
   * to obtain appropriate interpolation. For example, adding 1 point
   * results in linear interpolation, adding 2 results in areal
   * interpolation, etc.
   */
  
  switch (mDB.mpData->Topology)
    { // switch
    case SimpleDB::POINT : {
      const int numWts = 1;
      pWeights->resize(numWts);
      FindPointPt(pWeights);
      break;
    } // POINT
    case SimpleDB::LINE : {
      const int numWts = 2;
      pWeights->resize(numWts);
      FindPointPt(pWeights);
      FindLinePt(pWeights);
      break;
    } // LINE
    case SimpleDB::AREA : {
      const int numWts = 3;
      pWeights->resize(numWts);
      FindPointPt(pWeights);
      FindLinePt(pWeights);
      FindAreaPt(pWeights);
      break;
    } // AREA
    case SimpleDB::VOLUME : {
      const int numWts = 4;
      pWeights->resize(numWts);
      FindPointPt(pWeights);
      FindLinePt(pWeights);
      FindAreaPt(pWeights);
      FindVolumePt(pWeights);
      break;
    } // VOLUME
    default :
      throw std::runtime_error("Could not set weights for unknown "
			       "topology type.");
    } // switch
} // GetWeights

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::FindPointPt(std::vector<WtStruct>* pWeights)
{ // FindPointPt
  FIREWALL(0 != mDB.mpData);
  FIREWALL(0 != pWeights);

  (*pWeights)[0].Wt = 1.0;
  (*pWeights)[0].NearIndex = 0;
} // FindPointPt

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::FindLinePt(std::vector<WtStruct>* pWeights)
{ // FindPointPt
  FIREWALL(0 != mDB.mpData);
  FIREWALL(0 != pWeights);

  // best case is to use next nearest pt
  const int nearIndexA = (*pWeights)[0].NearIndex;
  int nearIndexB = nearIndexA + 1;

  const int locIndexA = mNearest[nearIndexA];
  const double* ptA = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexA);

  double wtA = 0;
  double wtB = 0;

  // find nearest pt where we can interpolate
  const int nearSize = mNearest.size();
  while (nearIndexB < nearSize) {
    const int locIndexB = mNearest[nearIndexB];
    const double* ptB = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexB);

    // wtA = DotProduct(pb, ab) / DotProduct(ab, ab)
    // wtB = DotProduct(ap, ab) / DotProduct(ab, ab)
    const double abX = ptB[0] - ptA[0];
    const double abY = ptB[1] - ptA[1];
    const double abZ = ptB[2] - ptA[2];
    const double abdotab = abX*abX + abY*abY + abZ*abZ;
    const double pbdotab = 
      (ptB[0]-mQ[0])*abX + (ptB[1]-mQ[1])*abY + (ptB[2]-mQ[2])*abZ;
    const double apdotab = 
      (mQ[0]-ptA[0])*abX + (mQ[1]-ptA[1])*abY + (mQ[2]-ptA[2])*abZ;
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
  if (nearSize == nearIndexB) { // if
    // if couldn't find points for interpolation
    std::ostringstream msg;
    msg
      << "Could not find points to use linear interpolation for point:\n("
      << mQ[0] << ", " << mQ[1] << ", " << mQ[2] << ").";
    throw std::runtime_error(msg.str());
  } // if
  (*pWeights)[0].Wt = wtA;
  (*pWeights)[1].Wt = wtB;
  (*pWeights)[1].NearIndex = nearIndexB;
} // FindLinePt

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::FindAreaPt(std::vector<WtStruct>* pWeights)
{ // FindAreaPt
  FIREWALL(0 != mDB.mpData);
  FIREWALL(0 != pWeights);

  const int numCoords = 3;

  // best case is to use next nearest pt
  const int nearIndexA = (*pWeights)[0].NearIndex;
  const int locIndexA = mNearest[nearIndexA];
  const double* ptA = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexA);

  const int nearIndexB = (*pWeights)[1].NearIndex;
  const int locIndexB = mNearest[nearIndexB];
  const double* ptB = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexB);

  double wtA = 0;
  double wtB = 0;
  double wtC = 0;

  // find nearest pt where we can interpolate
  const int nearSize = mNearest.size();
  int nearIndexC = nearIndexB + 1;
  while (nearIndexC < nearSize) {
    const int locIndexC = mNearest[nearIndexC];
    const double* ptC = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexC);

    // make sure A,B,C are not collinear by checking if area of
    // triangle ABC is not a tiny fraction of the distance AB

    double areaABC = 0;
    double dirABC[numCoords];
    Area(&areaABC, dirABC, ptA, ptB, ptC);

    // length(ab)^2
    const double ab2 = ptA[0]*ptB[0] + ptA[1]*ptB[1] + ptA[2]*ptB[2];

    const double tolerance = 1.0e-06;
    if (areaABC > tolerance*ab2) {
      // project P onto abc plane
      double qProj[numCoords];
      const double qmod = 
	dirABC[0]*mQ[0] + dirABC[1]*mQ[1] + dirABC[2]*mQ[2];
      qProj[0] = mQ[0] - dirABC[0]*qmod;
      qProj[1] = mQ[1] - dirABC[1]*qmod;
      qProj[2] = mQ[2] - dirABC[2]*qmod;

      // wtA = areaBCQ / areaABC * DotProduct(dirBCQ, dirABC);
      double areaBCQ = 0;
      double dirBCQ[numCoords];
      Area(&areaBCQ, dirBCQ, ptB, ptC, qProj);
      wtA = areaBCQ/areaABC * (dirBCQ[0]*dirABC[0] + 
			       dirBCQ[1]*dirABC[1] +
			       dirBCQ[2]*dirABC[2]);

      // wtB = areaCAQ / areaABC * DotProduct(dirCAQ, dirABC);
      double areaCAQ = 0;
      double dirCAQ[numCoords];
      Area(&areaCAQ, dirCAQ, ptC, ptA, qProj);
      wtB = areaCAQ/areaABC * (dirCAQ[0]*dirABC[0] + 
			       dirCAQ[1]*dirABC[1] +
			       dirCAQ[2]*dirABC[2]);

      // wtC = areaABQ / areaABC * DotProduct(dirABQ, dirABC);
      double areaABQ = 0;
      double dirABQ[numCoords];
      Area(&areaABQ, dirABQ, ptA, ptB, qProj);
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
  if (nearSize == nearIndexC) { // if
    // if couldn't find points for interpolation
    std::ostringstream msg;
    msg
      << "Could not find points to use areal interpolation for point:\n("
      << mQ[0] << ", " << mQ[1] << ", " << mQ[2] << ").";
    throw std::runtime_error(msg.str());
  } // if
  (*pWeights)[0].Wt = wtA;
  (*pWeights)[1].Wt = wtB;
  (*pWeights)[2].Wt = wtC;
  (*pWeights)[2].NearIndex = nearIndexC;
} // FindAreaPt

// ----------------------------------------------------------------------
void
spatial::SimpleDBQuery::FindVolumePt(std::vector<WtStruct>* pWeights)
{ // FindVolumePt
  FIREWALL(0 != mDB.mpData);
  FIREWALL(0 != pWeights);

  // best case is to use next nearest pt

  const int nearIndexA = (*pWeights)[0].NearIndex;
  const int locIndexA = mNearest[nearIndexA];
  const double* ptA = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexA);

  const int nearIndexB = (*pWeights)[1].NearIndex;
  const int locIndexB = mNearest[nearIndexB];
  const double* ptB = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexB);

  const int nearIndexC = (*pWeights)[2].NearIndex;
  const int locIndexC = mNearest[nearIndexC];
  const double* ptC = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexC);


  double wtA = 0;
  double wtB = 0;
  double wtC = 0;
  double wtD = 0;

  // find nearest pt where we can interpolate
  const int nearSize = mNearest.size();
  int nearIndexD = nearIndexC + 1;
  while (nearIndexD < nearSize) {
    const int locIndexD = mNearest[nearIndexD];
    const double* ptD = SimpleDBTypes::DataCoords(*mDB.mpData, locIndexD);
    
    // make sure A,B,C,D are not coplanar by checking if volume of
    // tetrahedron ABCD is not a tiny fraction of the distance AB
    
    // volume abcd
    const double abcd = Volume(ptA, ptB, ptC, ptD);
    
    // ab = length(ab)
    const double ab3 = 
      pow(pow(ptA[0] - ptB[0], 2) +
	  pow(ptA[1] - ptB[1], 2) +
	  pow(ptA[2] - ptB[2], 2), 3);

    const double tolerance = 1.0e-06;
    if (fabs(abcd) > tolerance*ab3) {

      // volume pbcd
      const double pbcd = Volume(mQ, ptB, ptC, ptD);
      // wtA = vol(pbcd)/vol(abcd)
      wtA = pbcd / abcd;

      // volume apcd
      const double apcd = Volume(ptA, mQ, ptC, ptD);
      // wtB = vol(apcd)/vol(abcd)
      wtB = apcd / abcd;

      // volume abpd
      const double abpd = Volume(ptA, ptB, mQ, ptD);
      // wtC = vol(abpd)/vol(abcd)
      wtC = abpd / abcd;

      // volume abcp
      const double abcp = Volume(ptA, ptB, ptC, mQ);
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
  if (nearSize == nearIndexD) { // if
    // if couldn't find points for interpolation
    std::ostringstream msg;
    msg
      << "Could not find points to use volumetric interpolation for point:\n("
      << mQ[0] << ", " << mQ[1] << ", " << mQ[2] << ").";
    throw std::runtime_error(msg.str());
  } // if
  (*pWeights)[0].Wt = wtA;
  (*pWeights)[1].Wt = wtB;
  (*pWeights)[2].Wt = wtC;
  (*pWeights)[3].Wt = wtD;
  (*pWeights)[3].NearIndex = nearIndexD;
} // FindVolumePt

// ----------------------------------------------------------------------
// Compute square of distance between points A and B.
double
spatial::SimpleDBQuery::DistSquared(const double a[3],
				    const double b[3])
{ // DistSquared
  const double abX = b[0]-a[0];
  const double abY = b[1]-a[1];
  const double abZ = b[2]-a[2];
  const double dist2 = abX*abX + abY*abY + abZ*abZ;
  return dist2;
} // DistSquared

// ----------------------------------------------------------------------
/* Compute area and "direction" of triangle abc. Direction is vector
 * normal to triangular surface.
 */
void
spatial::SimpleDBQuery::Area(double* pArea,
			     double dir[3],
			     const double* a,
			     const double* b,
			     const double* c)
{ // Area
  FIREWALL(0 != pArea);
  FIREWALL(0 != dir);
  
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
} // Area

// ----------------------------------------------------------------------
double
spatial::SimpleDBQuery::Volume(const double a[3],
			       const double b[3],
			       const double c[3],
			       const double d[3])
/* Compute volume of tetrahedral defined by four points. */
{ // Volume
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
} // Volume

// version
// $Id: SimpleDBQuery.cc,v 1.3 2005/05/05 20:31:29 baagaard Exp $

// End of file 
