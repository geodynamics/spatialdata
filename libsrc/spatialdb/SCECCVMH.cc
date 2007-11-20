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

//#include <portinfo>

#include "SCECCVMH.hh" // Implementation of class methods

#include "GocadVoxet.hh" // USES GocadVoxet

#include "spatialdata/geocoords/CSGeoProj.hh" // USES CSGeoProj
#include "spatialdata/geocoords/Projector.hh" // USES Projector
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES pow()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <assert.h> // USES assert()

#include <iostream> // TEMPORARY

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
  _queryVals(0),
  _querySize(0)
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

  delete[] _queryVals; _queryVals = 0;
  _querySize = 0;
} // destructor

// ----------------------------------------------------------------------
// Set directory containing SCEC CVM-H data files.
void
spatialdata::spatialdb::SCECCVMH::dataDir(const char* dir)
{ // dataDir
  _dataDir = dir;
} // dataDir

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
spatialdata::spatialdb::SCECCVMH::queryVals(const char** names,
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
	<< "Could not find value " << names[iVal] << " in spatial database\n"
	<< label() << ". Available values are:\n"
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
  } // if
  else if (numVals != _querySize) {
    std::ostringstream msg;
    msg
      << "Number of values to be returned by spatial database "
      << label() << "\n"
      << "(" << _querySize << ") does not match size of array provided ("
      << numVals << ").\n";
    throw std::runtime_error(msg.str());
  } // if

  // Convert coordinates to UTM
  memcpy(_xyzUTM, coords, numDims*sizeof(double));
  spatialdata::geocoords::Converter::convert(_xyzUTM, 1, numDims, 
					     _csUTM, csQuery);

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
	  queryFlag = outsideVoxet;
	haveVp = true;
	vp = vals[iVal];
	break;
      case QUERY_VPTAG :
	outsideVoxet = _queryTag(&vals[iVal]);
	if (outsideVoxet)
	  queryFlag = outsideVoxet;
	break;
      case QUERY_DENSITY :
	if (!haveVp) {
	  outsideVoxet = _queryVp(&vp);
	  haveVp = true;
	  if (outsideVoxet)
	    queryFlag = outsideVoxet;
	} // if
	vals[iVal] = _calcDensity(vp);
	break;
      case QUERY_VS :
	if (!haveVp) {
	  outsideVoxet = _queryVp(&vp);
	  haveVp = true;
	  if (outsideVoxet)
	    queryFlag = outsideVoxet;
	} // if
	vals[iVal] = _calcVs(vp);
	break;
      case QUERY_TOPOELEV :
	assert(0 != _topoElev);
	outsideVoxet = _topoElev->query(&vals[iVal], _xyzUTM);
	if (outsideVoxet)
	  queryFlag = outsideVoxet;
	break;
      case QUERY_BASEDEPTH :
	assert(0 != _baseDepth);
	outsideVoxet = _baseDepth->query(&vals[iVal], _xyzUTM);
	if (outsideVoxet)
	  queryFlag = outsideVoxet;
	break;
      case QUERY_MOHODEPTH :
	assert(0 != _mohoDepth);
	outsideVoxet = _mohoDepth->query(&vals[iVal], _xyzUTM);
	if (outsideVoxet)
	  queryFlag = outsideVoxet;
	break;
      default:
	assert(0);
      } // switch
} // query

// ----------------------------------------------------------------------
// Perform query for Vp.
int
spatialdata::spatialdb::SCECCVMH::_queryVp(double* vp)
{ // _queryVp
  int outsideVoxet = 0;
  double vpHR = 0.0;

  outsideVoxet = _laLowResVp->query(vp, _xyzUTM);
  if (!outsideVoxet) {
    outsideVoxet = _laHighResVp->query(&vpHR, _xyzUTM);
    if (!outsideVoxet)
      *vp = vpHR;
    else
      outsideVoxet = 0; // reset outsideVoxet flag to low-res value
  } else
    outsideVoxet = _crustMantleVp->query(vp, _xyzUTM);

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
      outsideVoxet = 0; // reset outsideVoxet flag to low-res value
  } else
    outsideVoxet = _crustMantleTag->query(tag, _xyzUTM);

  return outsideVoxet;
} // _queryTag

// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcDensity(const double vp)
{ // _calcDensity
  double density = vp / 3.0 + 1280.0;
  if (vp < 2160.0) {
    if (vp > 1480.0)
      density = 2000.0;
    else if (1480.0 == vp)
      density = 1000.0;
    else
      density = -99999.0;
  } // if

  return density;
} // _calcDensity

// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcVs(const double vp)
{ // _calcVs
  double vs = (vp < 4250.0) ?
    (vp - 1360.0) / 1.16 :
    785.8 - 1.2344*vp + 794.9 * pow(vp/1000.0,2) 
    - 123.8 * pow(vp/1000.0,3) + 6.4 * pow(vp/1000.0,4);
  if (vp < 1500.0)
    if (vp > 1480.0) 
      vs = (1500.0-1360.0)/1.16;
    else if (1480.0 == vp)
      vs = 0.0;
    else
      vs = -99999.0;

  return vs;
} // _calcVs


// End of file
