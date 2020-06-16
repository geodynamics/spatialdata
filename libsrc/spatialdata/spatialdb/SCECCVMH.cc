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

#include "spatialdata/geocoords/CSGeo.hh" // USES CSGeo
#include "spatialdata/geocoords/Converter.hh" // USES Converter

#include <math.h> // USES pow()
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <cstring> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <cassert> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SCECCVMH::SCECCVMH(void) :
    SpatialDB("SCEC CVM-H"),
    _dataDir("."),
    _laLowResVp(NULL),
    _laLowResTag(NULL),
    _laHighResVp(NULL),
    _laHighResTag(NULL),
    _crustMantleVp(NULL),
    _crustMantleVs(NULL),
    _crustMantleTag(NULL),
    _topoElev(NULL),
    _baseDepth(NULL),
    _mohoDepth(NULL),
    _csUTM(new geocoords::CSGeo),
    _squashLimit(-2000.0),
    _minVs(0.0),
    _queryValues(NULL),
    _querySize(0),
    _squashTopo(false) {
    assert(_csUTM);
    _csUTM->setString("+proj=utm +zone=11 +datum=NAD27 +units=m +type=crs");
} // constructor


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SCECCVMH::~SCECCVMH(void) {
    delete _laLowResVp;_laLowResVp = NULL;
    delete _laLowResTag;_laLowResTag = NULL;
    delete _laHighResVp;_laHighResVp = NULL;
    delete _laHighResTag;_laHighResTag = NULL;
    delete _crustMantleVp;_crustMantleVp = NULL;
    delete _crustMantleVs;_crustMantleVs = NULL;
    delete _crustMantleTag;_crustMantleTag = NULL;
    delete _topoElev;_topoElev = NULL;
    delete _baseDepth;_baseDepth = NULL;
    delete _mohoDepth;_mohoDepth = NULL;
    delete _csUTM;_csUTM = NULL;

    _squashLimit = 0.0;
    _minVs = 0.0;
    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;
    _squashTopo = 0;
} // destructor


// ----------------------------------------------------------------------
// Set minimum shear wave speed.
void
spatialdata::spatialdb::SCECCVMH::setMinVs(const double value) {
    if (value < 0.0) {
        std::ostringstream msg;
        msg << "Value for minimum shear wave speed (" << value << ") must be non-negative.";
        throw std::invalid_argument(msg.str());
    } // if
    _minVs = value;
} // setMinVs


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::SCECCVMH::open(void) {
    if (0 == _laLowResVp) {
        _laLowResVp = new GocadVoxet;
    }
    _laLowResVp->read(_dataDir.c_str(), "LA_LR.vo", "\"VINT1D\"");

    if (0 == _laLowResTag) {
        _laLowResTag = new GocadVoxet;
    }
    _laLowResTag->read(_dataDir.c_str(), "LA_LR.vo", "\"flag\"");

    if (0 == _laHighResVp) {
        _laHighResVp = new GocadVoxet;
    }
    _laHighResVp->read(_dataDir.c_str(), "LA_HR.vo", "\"vp\"");
    if (0 == _laHighResTag) {
        _laHighResTag = new GocadVoxet;
    }
    _laHighResTag->read(_dataDir.c_str(), "LA_HR.vo", "\"tag\"");

    if (0 == _crustMantleVp) {
        _crustMantleVp = new GocadVoxet;
    }
    _crustMantleVp->read(_dataDir.c_str(), "CM.vo", "\"cvp\"");
    if (0 == _crustMantleVs) {
        _crustMantleVs = new GocadVoxet;
    }
    _crustMantleVs->read(_dataDir.c_str(), "CM.vo", "\"cvs\"");
    if (0 == _crustMantleTag) {
        _crustMantleTag = new GocadVoxet;
    }
    _crustMantleTag->read(_dataDir.c_str(), "CM.vo", "\"tag\"");

    if (0 == _topoElev) {
        _topoElev = new GocadVoxet;
    }
    _topoElev->read(_dataDir.c_str(), "topo.vo", "\"topo\"");

    if (0 == _baseDepth) {
        _baseDepth = new GocadVoxet;
    }
    _baseDepth->read(_dataDir.c_str(), "base.vo", "\"base\"");

    if (0 == _mohoDepth) {
        _mohoDepth = new GocadVoxet;
    }
    _mohoDepth->read(_dataDir.c_str(), "moho.vo", "\"moho\"");
} // open


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::SCECCVMH::close(void) {
    delete _laLowResVp;_laLowResVp = NULL;
    delete _laLowResTag;_laLowResTag = NULL;
    delete _laHighResVp;_laHighResVp = NULL;
    delete _laHighResTag;_laHighResTag = NULL;
    delete _crustMantleVp;_crustMantleVp = NULL;
    delete _crustMantleVs;_crustMantleVs = NULL;
    delete _crustMantleTag;_crustMantleTag = NULL;
    delete _topoElev;_topoElev = NULL;
    delete _baseDepth;_baseDepth = NULL;
    delete _mohoDepth;_mohoDepth = NULL;
} // close


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::SCECCVMH::getNamesDBValues(const char*** valueNames,
                                                   size_t* numValues) const {
    const size_t dbNumValues = 7;
    const char* dbNamesValues[dbNumValues] = {
        "vp",
        "vs",
        "density",
        "topo-elev",
        "basement-depth",
        "moho-depth",
        "vp-tag",
    };
    if (valueNames) {
        *valueNames = (dbNumValues > 0) ? new const char*[dbNumValues] : NULL;
        for (size_t i = 0; i < dbNumValues; ++i) {
            (*valueNames)[i] = dbNamesValues[i];
        } // for
    }
    if (numValues) {
        *numValues = dbNumValues;
    } // if
} // getNamesDBValues


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SCECCVMH::setQueryValues(const char* const* names,
                                                 const size_t numVals) {
    if (0 == numVals) {
        std::ostringstream msg;
        msg << "Number of values for query in spatial database " << getLabel()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryValues;_queryValues = new size_t[numVals];
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        if (0 == strcasecmp(names[iVal], "vp")) {
            _queryValues[iVal] = QUERY_VP;
        } else if (0 == strcasecmp(names[iVal], "vs")) {
            _queryValues[iVal] = QUERY_VS;
        } else if (0 == strcasecmp(names[iVal], "density")) {
            _queryValues[iVal] = QUERY_DENSITY;
        } else if (0 == strcasecmp(names[iVal], "topo-elev")) {
            _queryValues[iVal] = QUERY_TOPOELEV;
        } else if (0 == strcasecmp(names[iVal], "basement-depth")) {
            _queryValues[iVal] = QUERY_BASEDEPTH;
        } else if (0 == strcasecmp(names[iVal], "moho-depth")) {
            _queryValues[iVal] = QUERY_MOHODEPTH;
        } else if (0 == strcasecmp(names[iVal], "vp-tag")) {
            _queryValues[iVal] = QUERY_VPTAG;
        } else {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << getLabel() << "'. Available values are:\n"
                << "vp, vs, density, topo-elev, basement-depth, moho-depth, vp-tag.";
            throw std::out_of_range(msg.str());
        } // else
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SCECCVMH::query(double* vals,
                                        const size_t numVals,
                                        const double* coords,
                                        const size_t numDims,
                                        const spatialdata::geocoords::CoordSys* csQuery) {
    if (0 == _querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << getLabel() << "\n"
            << "have not been set. Please call setQueryValues() before query().\n";
        throw std::logic_error(msg.str());
    } else if (numVals != _querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getLabel() << "\n"
            << "(" << _querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::invalid_argument(msg.str());
    } else if (3 != numDims) {
        std::ostringstream msg;
        msg << "Spatial dimension (" << numDims << ") when querying SCEC CVM-H must be 3.";
        throw std::invalid_argument(msg.str());
    } // if

    // Convert coordinates to UTM
    memcpy(_xyzUTM, coords, numDims*sizeof(double));
    spatialdata::geocoords::Converter::convert(_xyzUTM, 1, numDims, _csUTM, csQuery);

    bool haveTopo = false;
    double topoElev = 0;
    if (_squashTopo && ( _xyzUTM[2] > _squashLimit) ) {
        _topoElev->queryNearest(&topoElev, _xyzUTM);
        haveTopo = true;
        _xyzUTM[2] += topoElev;
    } // if

    int outsideVoxet = 0;
    int queryFlag = 0;
    bool haveVp = false;
    double vp = 0.0;
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        switch (_queryValues[iVal]) {
        case QUERY_VP:
            outsideVoxet = _queryVp(&vals[iVal]);
            if (outsideVoxet) {
                queryFlag |= outsideVoxet;
            }
            haveVp = true;
            vp = vals[iVal];
            break;
        case QUERY_DENSITY:
            if (!haveVp) {
                outsideVoxet = _queryVp(&vp);
                haveVp = true;
                if (outsideVoxet) {
                    queryFlag |= outsideVoxet;
                }
            } // if
            vals[iVal] = _calcDensity(vp);
            break;
        case QUERY_VS:
            if (!haveVp) {
                outsideVoxet = _queryVp(&vp);
                haveVp = true;
                if (outsideVoxet) {
                    queryFlag |= outsideVoxet;
                }
            } // if
            vals[iVal] = _calcVs(vp);
            break;
        case QUERY_TOPOELEV:
            if (!haveTopo) {
                assert(0 != _topoElev);
                outsideVoxet = _topoElev->queryNearest(&vals[iVal], _xyzUTM);
                if (outsideVoxet) {
                    queryFlag |= outsideVoxet;
                }
            } else {
                vals[iVal] = topoElev;
            }
            break;
        case QUERY_BASEDEPTH:
            assert(0 != _baseDepth);
            outsideVoxet = _baseDepth->queryNearest(&vals[iVal], _xyzUTM);
            if (outsideVoxet) {
                queryFlag |= outsideVoxet;
            }
            break;
        case QUERY_MOHODEPTH:
            assert(0 != _mohoDepth);
            outsideVoxet = _mohoDepth->queryNearest(&vals[iVal], _xyzUTM);
            if (outsideVoxet) {
                queryFlag |= outsideVoxet;
            }
            break;
        case QUERY_VPTAG:
            outsideVoxet = _queryTag(&vals[iVal]);
            if (outsideVoxet) {
                queryFlag |= outsideVoxet;
            }
            break;
        default:
            assert(0);
        } // switch

    }
    return queryFlag;
} // query


// ----------------------------------------------------------------------
// Perform query for Vp.
int
spatialdata::spatialdb::SCECCVMH::_queryVp(double* vp) {
    int outsideVoxet = 0;

    // Try first querying low-res model
    outsideVoxet = _laLowResVp->query(vp, _xyzUTM);
    if (!outsideVoxet) {
        // if inside low-res, try high-res model
        double vpHR = 0.0;
        outsideVoxet = _laHighResVp->query(&vpHR, _xyzUTM);
        if (!outsideVoxet) { // if inside high-res model, use it
            *vp = vpHR;
        } else { // not in high-res model, so use low-res value
            outsideVoxet = 0;
        }
    } else {
        outsideVoxet = _crustMantleVp->queryNearest(vp, _xyzUTM);
    }

    if (!outsideVoxet) {
        const double minVp = _minVp();
        if (*vp < minVp) {
            *vp = minVp;
        }
    } // if

    return outsideVoxet;
} // _queryVp


// ----------------------------------------------------------------------
// Perform query for tag.
int
spatialdata::spatialdb::SCECCVMH::_queryTag(double* tag) {
    int outsideVoxet = 0;
    double tagHR = 0.0;

    outsideVoxet = _laLowResTag->query(tag, _xyzUTM);
    if (!outsideVoxet) {
        outsideVoxet = _laHighResTag->query(&tagHR, _xyzUTM);
        if (!outsideVoxet) {
            *tag = tagHR;
        } else {
            outsideVoxet = 0; // use low-res value
        }
    } else {
        outsideVoxet = _crustMantleTag->queryNearest(tag, _xyzUTM);
    }

    return outsideVoxet;
} // _queryTag


// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcDensity(const double vp) const {
    const double minVp = _minVp();
    const double vpAdj = (vp < minVp) ? minVp : vp;

    double density = vpAdj / 3.0 + 1280.0;
    if (vpAdj < 2160.0) {
        if (vpAdj != 1480.0) { // if not water
            density = 2000.0;
        } else {
            density = 1000.0; // water
        }
    } // if

    return density;
} // _calcDensity


// ----------------------------------------------------------------------
// Compute density from Vp.
double
spatialdata::spatialdb::SCECCVMH::_calcVs(const double vp) const {
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
