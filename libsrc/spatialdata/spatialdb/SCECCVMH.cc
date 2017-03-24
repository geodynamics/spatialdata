// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2017 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

#include <portinfo>

#include "SCECCVMH.hh" // Implementation of class methods

#include "GocadVoxet.hh" // USES GocadVoxet

#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES pow()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <string.h> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SCECCVMH::SCECCVMH(void) :
  SpatialDB("SCEC CVM-H"),
  _dataDir("."),
  _laLowResVp(0),
  _laLowResTag(0),
  _laHighResVp(0),
  _laHighResTag(0),
  _crustMantleVp(0),
  _crustMantleVs(0),
  _crustMantleTag(0),
  _topoElev(0),
  _baseDepth(0),
  _mohoDepth(0),
  _csUTM(new geocoords::CSGeoProj),
  _squashLimit(-2000.0),
  _minVs(0.0),
  _queryVals(0),
  _querySize(0),
  _squashTopo(false)
{ // constructor
  geocoords::Projector proj;
  proj.projection("utm");
  proj.units("m");
  proj.projOptions("+zone=11");

  _csUTM->datumHoriz("NAD27");
  _csUTM->datumVert("mean sea level");
  _csUTM->ellipsoid("clrk66");
  _csUTM->projector(proj);
  _csUTM->initialize();
} // constructor

// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SCECCVMH::~SCECCVMH(void)
{ // destructor
  delete _laLowResVp; _laLowResVp = 0;
  delete _laLowResTag; _laLowResTag = 0;
  delete _laHighResVp; _laHighResVp = 0;
  delete _laHighResTag; _laHighResTag = 0;
  delete _crustMantleVp; _crustMantleVp = 0;
  delete _crustMantleVs; _crustMantleVs = 0;
  delete _crustMantleTag; _crustMantleTag = 0;
  delete _topoElev; _topoElev = 0;
  delete _baseDepth; _baseDepth = 0;
  delete _mohoDepth; _mohoDepth = 0;
  delete _csUTM; _csUTM = 0;

  _squashLimit = 0.0;
  _minVs = 0.0;
  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;
  _squashTopo = 0;
} // destructor

// ----------------------------------------------------------------------
// Set minimum shear wave speed.
void
spatialdata::spatialdb::SCECCVMH::minVs(const double value)
{ // minVs
  if (value < 0.0) {
    std::ostringstream msg;
    msg << "Value for minimum shear wave speed (" << value 
	<< ") must be non-negative.";
    throw std::runtime_error(msg.str());
  } // if
  _minVs = value;
} // minVs

// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::SCECCVMH::open(void)
{ // open
  if (0 == _laLowResVp)
    _laLowResVp = new GocadVoxet;
  _laLowResVp->read(_dataDir.c_str(), "LA_LR.vo", "\"VINT1D\"");

  if (0 == _laLowResTag)
    _laLowResTag = new GocadVoxet;
  _laLowResTag->read(_dataDir.c_str(), "LA_LR.vo", "\"flag\"");

  if (0 == _laHighResVp)
    _laHighResVp = new GocadVoxet;
  _laHighResVp->read(_dataDir.c_str(), "LA_HR.vo", "\"vp\"");
  if (0 == _laHighResTag)
    _laHighResTag = new GocadVoxet;
  _laHighResTag->read(_dataDir.c_str(), "LA_HR.vo", "\"tag\"");

  if (0 == _crustMantleVp)
    _crustMantleVp = new GocadVoxet;
  _crustMantleVp->read(_dataDir.c_str(), "CM.vo", "\"cvp\"");
  if (0 == _crustMantleVs)
    _crustMantleVs = new GocadVoxet;
  _crustMantleVs->read(_dataDir.c_str(), "CM.vo", "\"cvs\"");
  if (0 == _crustMantleTag)
    _crustMantleTag = new GocadVoxet;
  _crustMantleTag->read(_dataDir.c_str(), "CM.vo", "\"tag\"");

  if (0 == _topoElev)
    _topoElev = new GocadVoxet;
  _topoElev->read(_dataDir.c_str(), "topo.vo", "\"topo\"");

  if (0 == _baseDepth)
    _baseDepth = new GocadVoxet;
  _baseDepth->read(_dataDir.c_str(), "base.vo", "\"base\"");

  if (0 == _mohoDepth)
    _mohoDepth = new GocadVoxet;
  _mohoDepth->read(_dataDir.c_str(), "moho.vo", "\"moho\"");
} // open

// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::SCECCVMH::close(void)
{ // close
  delete _laLowResVp; _laLowResVp = 0;
  delete _laLowResTag; _laLowResTag = 0;
  delete _laHighResVp; _laHighResVp = 0;
  delete _laHighResTag; _laHighResTag = 0;
  delete _crustMantleVp; _crustMantleVp = 0;
  delete _crustMantleVs; _crustMantleVs = 0;
  delete _crustMantleTag; _crustMantleTag = 0;
  delete _topoElev; _topoElev = 0;
  delete _baseDepth; _baseDepth = 0;
  delete _mohoDepth; _mohoDepth = 0;
} // close

// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SCECCVMH::queryVals(const char* const* names,
					    const int numVals)
{ // queryVals
  if (0 == numVals) {
    std::ostringstream msg;
    msg
      << "Number of values for query in spatial database " << label()
      << "\n must be positive.\n";
    throw std::runtime_error(msg.str());
  } // if
  assert(0 != names && 0 < numVals);
  
  _querySize = numVals;
  delete[] _queryVals; _queryVals = new int[numVals];
  for (int iVal=0; iVal < numVals; ++iVal) {
    if (0 == strcasecmp(names[iVal], "vp"))
      _queryVals[iVal] = QUERY_VP;
    else if (0 == strcasecmp(names[iVal], "vs"))
      _queryVals[iVal] = QUERY_VS;
    else if (0 == strcasecmp(names[iVal], "density"))
      _queryVals[iVal] = QUERY_DENSITY;
    else if (0 == strcasecmp(names[iVal], "topo-elev"))
      _queryVals[iVal] = QUERY_TOPOELEV;
    else if (0 == strcasecmp(names[iVal], "basement-depth"))
      _queryVals[iVal] = QUERY_BASEDEPTH;
    else if (0 == strcasecmp(names[iVal], "moho-depth"))
      _queryVals[iVal] = QUERY_MOHODEPTH;
    else if (0 == strcasecmp(names[iVal], "vp-tag"))
      _queryVals[iVal] = QUERY_VPTAG;
    else {
      std::ostringstream msg;
      msg
	<< "Could not find value '" << names[iVal] << "' in spatial database '"
	<< label() << "'. Available values are:\n"
	<< "vp, vs, density, topo-elev, basement-depth, moho-depth, vp-tag.";
      throw std::runtime_error(msg.str());
    } // else
  } // for
} // queryVals

// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SCECCVMH::query(double* vals,
					const int numVals,
					const double* coords,
					const int numDims,
					const spatialdata::geocoords::CoordSys* csQuery)
{ // query
  if (0 == _querySize) {
    std::ostringstream msg;
    msg
      << "Values to be returned by spatial database " << label() << "\n"
      << "have not been set. Please call queryVals() before query().\n";
    throw std::runtime_error(msg.str());
  } else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } else if (3 != numDims) {
    std::ostringstream msg;
    msg
      << "Spatial dimension (" << numDims
      << ") when querying SCEC CVM-H must be 3.";
    throw std::runtime_error(msg.str());
  } // if

  // Convert coordinates to UTM
  memcpy(_xyzUTM, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyzUTM, 1, numDims, 
					     _csUTM, csQuery);

  bool haveTopo = false;
  double topoElev = 0;
  if (_squashTopo && _xyzUTM[2] > _squashLimit) {
    _topoElev->queryNearest(&topoElev, _xyzUTM);
    haveTopo = true;
    _xyzUTM[2] += topoElev;
  } // if

  int outsideVoxet = 0;
  int queryFlag = 0;
  bool haveVp = false;
  double vp = 0.0;
  for (int iVal=0; iVal < numVals; ++iVal)
    switch (_queryVals[iVal])
      { // switch
      case QUERY_VP :
	outsideVoxet = _queryVp(&vals[iVal]);
	if (outsideVoxet)
	  queryFlag |= outsideVoxet;
	haveVp = true;
	vp = vals[iVal];
	break;
      case QUERY_DENSITY :
	if (!haveVp) {
	  outsideVoxet = _queryVp(&vp);
	  haveVp = true;
	  if (outsideVoxet)
	    queryFlag |= outsideVoxet;
	} // if
	vals[iVal] = _calcDensity(vp);
	break;
      case QUERY_VS :
	if (!haveVp) {
	  outsideVoxet = _queryVp(&vp);
	  haveVp = true;
	  if (outsideVoxet)
	    queryFlag |= outsideVoxet;
	} // if
	vals[iVal] = _calcVs(vp);
	break;
      case QUERY_TOPOELEV :
	if (!haveTopo) {
	  assert(0 != _topoElev);
	  outsideVoxet = _topoElev->queryNearest(&vals[iVal], _xyzUTM);
	  if (outsideVoxet)
	    queryFlag |= outsideVoxet;
	} else
	  vals[iVal] = topoElev;
	break;
      case QUERY_BASEDEPTH :
	assert(0 != _baseDepth);
	outsideVoxet = _baseDepth->queryNearest(&vals[iVal], _xyzUTM);
	if (outsideVoxet)
	  queryFlag |= outsideVoxet;
	break;
      case QUERY_MOHODEPTH :
	assert(0 != _mohoDepth);
	outsideVoxet = _mohoDepth->queryNearest(&vals[iVal], _xyzUTM);
	if (outsideVoxet)
	  queryFlag |= outsideVoxet;
	break;
      case QUERY_VPTAG :
	outsideVoxet = _queryTag(&vals[iVal]);
	if (outsideVoxet)
	  queryFlag |= outsideVoxet;
	break;
      default:
	assert(0);
      } // switch

  return queryFlag;
} // query

// ----------------------------------------------------------------------
// Perform query for Vp.
int
spatialdata::spatialdb::SCECCVMH::_queryVp(double* vp)
{ // _queryVp
  int outsideVoxet = 0;

  // Try first querying low-res model
  outsideVoxet = _laLowResVp->query(vp, _xyzUTM);
  if (!outsideVoxet) {
    // if inside low-res, try high-res model
    double vpHR = 0.0;
    outsideVoxet = _laHighResVp->query(&vpHR, _xyzUTM);
    if (!outsideVoxet) // if inside high-res model, use it
      *vp = vpHR;
    else // not in high-res model, so use low-res value
      outsideVoxet = 0;
  } else
    outsideVoxet = _crustMantleVp->queryNearest(vp, _xyzUTM);

  if (!outsideVoxet) {
    const double minVp = _minVp();
    if (*vp < minVp)
      *vp = minVp;
  } // if

  return outsideVoxet;
} // _queryVp

// ----------------------------------------------------------------------
// Perform query for tag.
int
spatialdata::spatialdb::SCECCVMH::_queryTag(double* tag)
{ // _queryTag
  int outsideVoxet = 0;
  double tagHR = 0.0;

  outsideVoxet = _laLowResTag->query(tag, _xyzUTM);
  if (!outsideVoxet) {
    outsideVoxet = _laHighResTag->query(&tagHR, _xyzUTM);
    if (!outsideVoxet)
      *tag = tagHR;
    else
      outsideVoxet = 0; // use low-res value
  } else
    outsideVoxet = _crustMantleTag->queryNearest(tag, _xyzUTM);

  return outsideVoxet;
} // _queryTag

// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcDensity(const double vp) const
{ // _calcDensity
  const double minVp = _minVp();
  const double vpAdj = (vp < minVp) ? minVp : vp;

  double density = vpAdj / 3.0 + 1280.0;
  if (vpAdj < 2160.0) {
    if (vpAdj != 1480.0) // if not water
      density = 2000.0;
    else
      density = 1000.0; // water
  } // if

  return density;
} // _calcDensity

// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcVs(const double vp) const
{ // _calcVs
  double vs = (vp < 4250.0) ?
    (vp - 1360.0) / 1.16 :
    785.8 - 1.2344*vp + 794.9 * pow(vp/1000.0,2) 
    - 123.8 * pow(vp/1000.0,3) + 6.4 * pow(vp/1000.0,4);
  if (vp < 1500.0) {
    if (vp != 1480.0) { // if not water
      vs = (1500.0-1360.0)/1.16;
    } else {
      vs = 0.0; // water
    } // if/else
  } // if

  if (vs < _minVs) {
    vs = _minVs;
  } // if

  return vs;
} // _calcVs


// End of file
