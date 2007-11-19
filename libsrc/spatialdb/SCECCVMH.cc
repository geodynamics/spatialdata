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
  _csUTM(new geocoords::CSGeoProj)
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
  // Convert coordinates to UTM
  for (int i=0; i < numDims; ++i)
    _xyzUTM[i] = coords[i];
  spatialdata::geocoords::Converter::convert(_xyzUTM, 1, numDims, 
					     _csUTM, csQuery);

  assert(0 != _topoElev);
  double elev = 0.0;
  double baseDepth = 0.0;
  double mohoDepth = 0.0;
  double vp = 0.0;
  double vs = 0.0;
  double density = 0.0;

  int outsideVoxet =_topoElev->query(&elev, _xyzUTM);
  outsideVoxet = _baseDepth->query(&baseDepth, _xyzUTM);
  outsideVoxet = _mohoDepth->query(&mohoDepth, _xyzUTM);

  outsideVoxet = _laLowResVp->query(&vp, _xyzUTM);
  if (!outsideVoxet) {
    double vpHR = 0.0;
    outsideVoxet = _laHighResVp->query(&vpHR, _xyzUTM);
    if (!outsideVoxet) {
      vp = vpHR;
    } // if
    if (vp != 1480.0) {
      if (vp < 4250.0)
	vs = (vp > 1500.0) ? (vp-1360.0/1.16) : (1500.0-1360.0)/1.16;
      else 
        vs = 785.8 - 1.2344*vp + 794.9 * pow(vp/1000.0,2) 
	  -123.8 * pow(vp/1000.0,3) + 6.4 * pow(vp/1000.0,4);
      if (vp > 2160.0)
        density = vp / 3.0 + 1280.0;
      else
        density = 2000.0;
    } else
      density = 1000.0;
  } else {
    outsideVoxet = _crustMantleVp->query(&vp, _xyzUTM);
    if (!outsideVoxet) {
      outsideVoxet = _crustMantleVs->query(&vs, _xyzUTM);
      density = vp / 3.0 + 1280.0;
    } else {
      vs = vp; // No data value
      density = vp; // No data value
    } // else
  } // if/else

  std::cout << "elev: " << elev
	    << ", basement depth: " << baseDepth
	    << ", moho depth: " << mohoDepth
	    << ", vp: " << vp
	    << ", vs: " << vs
	    << ", density: " << density << std::endl;
} // query


// End of file
