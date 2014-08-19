// -*- C++ -*-
//
// ----------------------------------------------------------------------
//
// Brad T. Aagaard, U.S. Geological Survey
//
// This code was developed as part of the Computational Infrastructure
// for Geodynamics (http://geodynamics.org).
//
// Copyright (c) 2010-2014 University of California, Davis
//
// See COPYING for license information.
//
// ----------------------------------------------------------------------
//

// DO NOT EDIT THIS FILE
// This file was generated from python application simpledbdatavolume3D.

#if !defined(spatialdata_spatialdb_simpledbtestdatavolume3d_hh)
#define spatialdata_spatialdb_simpledbtestdatavolume3d_hh

#include "SimpleDBTestData.hh"

namespace spatialdata {
  namespace spatialdb {
     class SimpleDBTestDataVolume3D;
  } // spatialdata
} // spatialdb

class spatialdata::spatialdb::SimpleDBTestDataVolume3D : public SimpleDBTestData
{

public: 

  /// Constructor
  SimpleDBTestDataVolume3D(void);

  /// Destructor
  ~SimpleDBTestDataVolume3D(void);

private:

  static const int _numLocs;

  static const int _spaceDim;

  static const int _numVals;

  static const int _dataDim;

  static const int _numQueries;

  static const double _dbCoords[];

  static const double _dbData[];

  static const char* _names[];

  static const char* _units[];

  static const double _queryNearest[];

  static const double _queryLinear[];

  static const int _errFlags[];

};

#endif // spatialdata_spatialdb_simpledbtestdatavolume3d_hh

// End of file
