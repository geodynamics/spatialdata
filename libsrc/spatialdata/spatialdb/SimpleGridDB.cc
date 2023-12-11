// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================

#include <portinfo>

#include "SimpleGridDB.hh" // Implementation of class methods

#include "SimpleGridAscii.hh" // USES SimpleGridAscii

#include "spatialdata/geocoords/CoordSys.hh" // HASA CoordSys
#include "spatialdata/geocoords/Converter.hh" // USES Converter
#include "spatialdata/utils/LineParser.hh" // USES LineParser

#include <cmath> // USES std::floor()

#include <fstream> // USES std::ifstream
#include <sstream> // USES std::ostringstream
#include <stdexcept> // USES std::logic_error
#include <cstring> // USES memcpy()
#include <strings.h> // USES strcasecmp()
#include <assert.h> // USES assert()

// ----------------------------------------------------------------------
// Constructor
spatialdata::spatialdb::SimpleGridDB::SimpleGridDB(void) :
    _data(NULL),
    _x(NULL),
    _y(NULL),
    _z(NULL),
    _queryValues(NULL),
    _querySize(0),
    _numX(0),
    _numY(0),
    _numZ(0),
    _dataDim(0),
    _spaceDim(0),
    _numValues(0),
    _names(NULL),
    _units(NULL),
    _filename(""),
    _cs(NULL),
    _converter(new spatialdata::geocoords::Converter),
    _queryType(NEAREST) {}


// ----------------------------------------------------------------------
// Destructor
spatialdata::spatialdb::SimpleGridDB::~SimpleGridDB(void) {
    delete[] _data;_data = NULL;
    delete[] _x;_x = NULL;
    delete[] _y;_y = NULL;
    delete[] _z;_z = NULL;
    _numX = 0;
    _numY = 0;
    _numZ = 0;
    _numValues = 0;
    delete[] _names;_names = NULL;
    delete[] _units;_units = NULL;
    delete[] _queryValues;_queryValues = NULL;
    _querySize = 0;

    delete _cs;_cs = NULL;
    delete _converter;_converter = NULL;
} // destructor


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::SimpleGridDB::setFilename(const char* value) {
    _filename = value;
} // setFilename


// ----------------------------------------------------------------------
// Open the database and prepare for querying.
void
spatialdata::spatialdb::SimpleGridDB::open(void) {
    SimpleGridAscii::read(this);

    // Convert to SI units
    const size_t numLocs = (3 == _spaceDim) ? _numX * _numY * _numZ : (2 == _spaceDim) ? _numX * _numY : _numX;
    try {
        SpatialDB::_convertToSI(_data, _units, numLocs, _numValues);
    } catch (const std::exception& err) {
        std::ostringstream msg;
        msg << "Error parsing units for spatial database '" << getDescription() << "':\n"
            << err.what();
        throw std::runtime_error(msg.str().c_str());
    } // try/catch

    // Default query values is all values.
    _querySize = _numValues;
    delete[] _queryValues;_queryValues = (_querySize > 0) ? new size_t[_querySize] : NULL;
    for (size_t i = 0; i < _querySize; ++i) {
        _queryValues[i] = i;
    } // for
} // open


// ----------------------------------------------------------------------
// Close the database.
void
spatialdata::spatialdb::SimpleGridDB::close(void) {
    delete[] _data;_data = NULL;
    delete[] _x;_x = NULL;
    delete[] _y;_y = NULL;
    delete[] _z;_z = NULL;
    _numX = 0;
    _numY = 0;
    _numZ = 0;

    _numValues = 0;
    delete[] _names;_names = NULL;
    delete[] _units;_units = NULL;

    _querySize = 0;
    delete[] _queryValues;_queryValues = NULL;
} // close


// ----------------------------------------------------------------------
// Set query type.
void
spatialdata::spatialdb::SimpleGridDB::setQueryType(const QueryEnum value) {
    _queryType = value;
} // setQueryType


// ----------------------------------------------------------------------
// Get names of values in spatial database.
void
spatialdata::spatialdb::SimpleGridDB::getNamesDBValues(const char*** valueNames,
                                                       size_t* numValues) const {
    if (valueNames) {
        *valueNames = (_numValues > 0) ? new const char*[_numValues] : NULL;
        for (size_t i = 0; i < _numValues; ++i) {
            (*valueNames)[i] = _names[i].c_str();
        } // for
    }
    if (numValues) {
        *numValues = _numValues;
    } // if
} // getNamesDBValues


// ----------------------------------------------------------------------
// Set values to be returned by queries.
void
spatialdata::spatialdb::SimpleGridDB::setQueryValues(const char* const* names,
                                                     const size_t numVals) {
    assert(_data);
    if (0 == numVals) {
        std::ostringstream msg;
        msg
            << "Number of values for query in spatial database " << getDescription()
            << "\n must be positive.\n";
        throw std::invalid_argument(msg.str());
    } // if
    assert(names && 0 < numVals);

    _querySize = numVals;
    delete[] _queryValues;_queryValues = new size_t[numVals];
    for (size_t iVal = 0; iVal < numVals; ++iVal) {
        size_t iName = 0;
        const size_t numNames = _numValues;
        while (iName < numNames) {
            if (0 == strcasecmp(names[iVal], _names[iName].c_str())) {
                break;
            } // if
            ++iName;
        } // while
        if (iName >= numNames) {
            std::ostringstream msg;
            msg << "Could not find value '" << names[iVal] << "' in spatial database '"
                << getDescription() << "'. Available values are:";
            for (size_t iName = 0; iName < numNames; ++iName) {
                msg << "\n  " << _names[iName];
            } // for
            msg << "\n";
            throw std::out_of_range(msg.str());
        } // if
        _queryValues[iVal] = iName;
    } // for
} // queryVals


// ----------------------------------------------------------------------
// Query the database.
int
spatialdata::spatialdb::SimpleGridDB::query(double* vals,
                                            const size_t numVals,
                                            const double* coords,
                                            const size_t numDims,
                                            const spatialdata::geocoords::CoordSys* csQuery) {
    const size_t querySize = _querySize;

    if (0 == querySize) {
        std::ostringstream msg;
        msg << "Values to be returned by spatial database " << getDescription() << "\n"
            << "have not been set. Please call setQueryValues() before query().\n";
        throw std::logic_error(msg.str());
    } else if (numVals != querySize) {
        std::ostringstream msg;
        msg << "Number of values to be returned by spatial database "
            << getDescription() << "\n"
            << "(" << querySize << ") does not match size of array provided ("
            << numVals << ").\n";
        throw std::invalid_argument(msg.str());
    } else if (numDims != _spaceDim) {
        std::ostringstream msg;
        msg << "Spatial dimension (" << numDims
            << ") does not match spatial dimension of spatial database (" << _spaceDim << ").";
        throw std::invalid_argument(msg.str());
    } // if

    // Convert coordinates
    assert(numDims <= 3);
    memcpy(_xyz, coords, numDims*sizeof(double));
    assert(_converter);
    _converter->convert(_xyz, 1, numDims, _cs, csQuery);

    int queryFlag = 0;
    const int spaceDim = _spaceDim;

    double index0 = 0.0;
    double index1 = 0.0;
    double index2 = 0.0;
    size_t size0 = 0;
    size_t size1 = 0;
    size_t size2 = 0;
    if (3 == spaceDim) {
        index0 = _search(_xyz[0], _x, _numX);
        index1 = _search(_xyz[1], _y, _numY);
        index2 = _search(_xyz[2], _z, _numZ);
        _reindex3d(&index0, &size0, &index1, &size1, &index2, &size2);
    } else if (2 == spaceDim) {
        index0 = _search(_xyz[0], _x, _numX);
        index1 = _search(_xyz[1], _y, _numY);
        _reindex2d(&index0, &size0, &index1, &size1);
    } else { // else
        assert(1 == spaceDim);
        index0 = _search(_xyz[0], _x, _numX);
        size0 = _numX;
    } // if/else

    switch (_queryType) {
    case LINEAR:
        if (( index0 < 0.0) || (( index0 > 0) && ( index0 > size0-1.0) ) ||
            ( index1 < 0.0) || (( index1 > 0) && ( index1 > size1-1.0) ) ||
            ( index2 < 0.0) || (( index2 > 0) && ( index2 > size2-1.0) )) {
            queryFlag = 1;
            return queryFlag;
        } // if

        switch (_dataDim) {
        case 1:
            _interpolate1D(vals, numVals, index0, size0);
            break;
        case 2:
            _interpolate2D(vals, numVals, index0, size0, index1, size1);
            break;
        case 3:
            _interpolate3D(vals, numVals, index0, index1, index2);
            break;
        default:
            assert(false);
            throw std::logic_error("Unsupported data dimension in SimpleGridDB::query().");
        } // switch
        break;
    case NEAREST: {
        index0 = std::min(index0, size0-1.0);
        index0 = std::max(index0, 0.0);
        index1 = std::min(index1, size1-1.0);
        index1 = std::max(index1, 0.0);
        index2 = std::min(index2, size2-1.0);
        index2 = std::max(index2, 0.0);
        const size_t indexNearest0 = size_t(std::floor(index0+0.5));
        const size_t indexNearest1 = size_t(std::floor(index1+0.5));
        const size_t indexNearest2 = size_t(std::floor(index2+0.5));
        const size_t indexData = _getDataIndex(indexNearest0, size0, indexNearest1, size1, indexNearest2, size2);

        for (size_t iVal = 0; iVal < querySize; ++iVal) {
            vals[iVal] = _data[indexData+_queryValues[iVal]];
#if 0 // DEBUGGING
            std::cout << "val["<<iVal<<"]: " << vals[iVal]
                      << ", indexData: " << indexData
                      << ", index0: " << index0
                      << ", index1: " << index1
                      << ", index2: " << index2
                      << std::endl;
#endif
        } // for
        break;
    } // NEAREST
    default:
        assert(false);
        throw std::logic_error("Unsupported query type in SimpleGridDB::query().");
    } // switch

    return queryFlag;
} // query


// ----------------------------------------------------------------------
// Allocate data.
void
spatialdata::spatialdb::SimpleGridDB::allocate(const size_t numX,
                                               const size_t numY,
                                               const size_t numZ,
                                               const size_t numValues,
                                               const size_t spaceDim,
                                               const size_t dataDim) {
    _numX = numX;
    _numY = numY;
    _numZ = numZ;
    _numValues = numValues;
    _spaceDim = spaceDim;
    _dataDim = dataDim;

    _checkCompatibility();

    const size_t numLocs = (3 == spaceDim) ? _numX * _numY * _numZ : (2 == spaceDim) ? _numX * _numY : _numX;
    delete[] _data;_data = (numLocs*numValues > 0) ? new double[numLocs*numValues] : NULL;

    delete[] _x;_x = (numX > 0) ? new double[numX] : NULL;
    delete[] _y;_y = (numY > 0) ? new double[numY] : NULL;
    delete[] _z;_z = (numZ > 0) ? new double[numZ] : NULL;
} // allocate


// ----------------------------------------------------------------------
// Set coordinates along x-axis;
void
spatialdata::spatialdb::SimpleGridDB::setX(const double* values,
                                           const size_t size) {
    if (size != _numX) {
        std::ostringstream msg;
        msg << "Mismatch in size (" << _numX << " != " << size
            << ") for number of values along x-axis in simple grid spatial database.";
        throw std::length_error(msg.str());
    } // if
    if (!_x) {
        _x = (size > 0) ? new double[size] : NULL;
    } // if

    assert(_x);
    for (size_t i = 0; i < size; ++i) {
        _x[i] = values[i];
    } // for
} // setD


// ----------------------------------------------------------------------
// Set coordinates along y-axis;
void
spatialdata::spatialdb::SimpleGridDB::setY(const double* values,
                                           const size_t size) {
    if (size != _numY) {
        std::ostringstream msg;
        msg << "Mismatch in size (" << _numY << " != " << size
            << ") for number of values along y-axis in simple grid spatial database.";
        throw std::length_error(msg.str());
    } // if
    if (!_y) {
        _y = (size > 0) ? new double[size] : NULL;
    } // if

    assert(_y);
    for (size_t i = 0; i < size; ++i) {
        _y[i] = values[i];
    } // for
} // setY


// ----------------------------------------------------------------------
// Set coordinates along z-axis;
void
spatialdata::spatialdb::SimpleGridDB::setZ(const double* values,
                                           const size_t size) {
    if (size != _numZ) {
        std::ostringstream msg;
        msg << "Mismatch in size (" << _numZ << " != " << size
            << ") for number of values along z-axis in simple grid spatial database.";
        throw std::length_error(msg.str());
    } // if
    if (!_z) {
        _z = (size > 0) ? new double[size] : NULL;
    } // if

    assert(_z);
    for (size_t i = 0; i < size; ++i) {
        _z[i] = values[i];
    } // for
} // setZ


// ----------------------------------------------------------------------
// Set data values.
void
spatialdata::spatialdb::SimpleGridDB::setData(const double* coords,
                                              const size_t numLocs,
                                              const size_t spaceDim,
                                              const double* values,
                                              const size_t numLocs2,
                                              const size_t numValues) {
    if (numLocs != numLocs2) {
        std::ostringstream msg;
        msg << "Mismatch in number of locations (" << numLocs << " != " << numLocs2
            << ") for number of locations in simple grid spatial database.";
        throw std::invalid_argument(msg.str());
    } // if
    if (spaceDim != _spaceDim) {
        std::ostringstream msg;
        msg << "Mismatch in coordinate dimension (" << _spaceDim << " != " << spaceDim
            << ") for locations in simple grid spatial database.";
        throw std::invalid_argument(msg.str());
    } // if
    if (numValues != _numValues) {
        std::ostringstream msg;
        msg << "Mismatch in number of values (" << _numValues << " != " << numValues
            << ") for simple grid spatial database.";
        throw std::invalid_argument(msg.str());
    } // if

    if (!_data) {
        const size_t size = numLocs*numValues;
        _data = (size > 0) ? new double[size] : NULL;
    } // if

    assert(_data);
    for (size_t iLoc = 0; iLoc < numLocs; ++iLoc) {
        const size_t indexData = _getDataIndex(&coords[iLoc*spaceDim], spaceDim);
        const size_t jj = iLoc*numValues;
        for (size_t iV = 0; iV < numValues; ++iV) {
            _data[indexData+iV] = values[jj+iV];
        } // for
    } // for
} // setData


// ----------------------------------------------------------------------
// Set names of data values.
void
spatialdata::spatialdb::SimpleGridDB::setNames(const char* const* values,
                                               const size_t numValues) {
    assert(values);
    if (numValues != _numValues) {
        std::ostringstream msg;
        msg << "Mismatch in number of values (" << _numValues << " != " << numValues
            << ") for names of values in simple grid spatial database.";
        throw std::invalid_argument(msg.str());
    } // if
    delete[] _names;_names = (numValues > 0) ? new std::string[numValues] : NULL;
    for (size_t i = 0; i < numValues; ++i) {
        _names[i] = values[i];
    } // for
} // setNames


// ----------------------------------------------------------------------
// Set units of data values.
void
spatialdata::spatialdb::SimpleGridDB::setUnits(const char* const* values,
                                               const size_t numValues) {
    assert(values);
    if (numValues != _numValues) {
        std::ostringstream msg;
        msg << "Mismatch in number of values (" << _numValues << " != " << numValues
            << ") for units of values in simple grid spatial database.";
        throw std::invalid_argument(msg.str());
    } // if
    delete[] _units;_units = (numValues > 0) ? new std::string[numValues] : NULL;
    for (size_t i = 0; i < numValues; ++i) {
        _units[i] = values[i];
    } // for
} // setUnits


// ----------------------------------------------------------------------
// Set filename containing data.
void
spatialdata::spatialdb::SimpleGridDB::setCoordSys(const geocoords::CoordSys& cs) {
    delete _cs;_cs = cs.clone();assert(_cs);
} // setCoordSys


// ----------------------------------------------------------------------
// Check compatibility of spatial database parameters.
void
spatialdata::spatialdb::SimpleGridDB::_checkCompatibility(void) const {
    const size_t spaceDim = _spaceDim;
    const size_t dataDim = _dataDim;
    std::ostringstream msg;

    const size_t numX = _numX;
    const size_t numY = _numY;
    const size_t numZ = _numZ;

    int count1 = 0;
    if (( 0 == numX) || ( 1 == numX) ) {
        count1 += 1;
    } // if
    if (( 0 == numY) || ( 1 == numY) ) {
        count1 += 1;
    } // if
    if (( 0 == numZ) || ( 1 == numZ) ) {
        count1 += 1;
    } // if

    if (( 0 == dataDim) && ( 3 != count1) ) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") is incompatible with dimensions of a 0-D grid  ("
            << numX << "," << numY << "," << numZ << ").";
        throw std::domain_error(msg.str());

    } else if (( 1 == dataDim) && ( 2 != count1) ) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") is incompatible with dimensions of a 1-D grid  ("
            << numX << "," << numY << "," << numZ << ").";
        throw std::domain_error(msg.str());

    } else if (( 2 == dataDim) && ( 1 != count1) ) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") is incompatible with dimensions of a 2-D grid  ("
            << numX << "," << numY << "," << numZ << ").";
        throw std::domain_error(msg.str());

    } else if (( 3 == dataDim) && ( 0 != count1) ) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") is incompatible with dimensions of a 3-D grid  ("
            << numX << "," << numY << "," << numZ << ").";
        throw std::domain_error(msg.str());
    } // if/else

    if (dataDim > spaceDim) {
        msg << "Dimension of data in spatial distribution (" << dataDim
            << ") exceeds the number of dimensions of the coordinates ("
            << spaceDim << ").";
        throw std::domain_error(msg.str());
    } // if

    assert(_cs);
    if (spaceDim != _cs->getSpaceDim()) {
        msg << "Number of dimensions in coordinates of spatial distribution ("
            << spaceDim << ") does not match number of dimensions in coordinate "
            << "system (" << _cs->getSpaceDim() << ")";
        throw std::domain_error(msg.str());
    } // if
} // _checkCompatibility


// ----------------------------------------------------------------------
// Bilinear search for coordinate.
double
spatialdata::spatialdb::SimpleGridDB::_search(const double target,
                                              const double* vals,
                                              const size_t nvals) const {
    if (1 == nvals) {
        return 0.0;
    } // if

    assert(vals);
    assert(nvals > 0);

    double index = -1.0;
    size_t indexL = 0;
    size_t indexR = nvals - 1;
    const double tolerance = 1.0e-6;
    if (( target >= vals[indexL]-tolerance) && ( target <= vals[indexR]+tolerance) ) {
        while (indexR - indexL > 1) {
            size_t indexM = indexL + (indexR-indexL) / 2;
            if (target < vals[indexM]) {
                indexR = indexM;
            } else {
                indexL = indexM;
            } // if/else
        } // while
        assert(target >= vals[indexL]-tolerance);
        assert(vals[indexR] > vals[indexL]);
        index = double(indexL) + (target - vals[indexL]) / (vals[indexR] - vals[indexL]);
    } else if (_queryType == NEAREST) {
        if (target <= vals[indexL]) {
            index = 0.0;
        } else {
            index = double(nvals-1);
        } // if/else
    } // if/else

    return index;
} // _search


// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 1-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate1D(double* vals,
                                                     const size_t numVals,
                                                     const double indexX,
                                                     const size_t numX) const {
    assert(numX >= 2);
    const size_t indexX0 = std::min(numX-2, size_t(std::floor(indexX)));
    const double wtX0 = 1.0 - (indexX - indexX0);
    const size_t indexX1 = indexX0 + 1;
    const double wtX1 = 1.0 - wtX0;
    assert(0 <= indexX0 && indexX0 < numX);
    assert(0 <= indexX1 && indexX1 < numX);

    const size_t index000 = _getDataIndex(indexX0, numX, 0, 0, 0, 0);
    const size_t index100 = _getDataIndex(indexX1, numX, 0, 0, 0, 0);

    const double wt000 = wtX0;
    const double wt100 = wtX1;

    const size_t querySize = _querySize;
    for (size_t iVal = 0; iVal < querySize; ++iVal) {
        const size_t qVal = _queryValues[iVal];
        vals[iVal] =
            wt000 * _data[index000+qVal] +
            wt100 * _data[index100+qVal];
#if 0 // DEBUGGING
        std::cout << "val["<<iVal<<"]: " << vals[iVal]
                  << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
                  << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
                  << std::endl;
#endif
    } // for

} // _interpolate1D


// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 2-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate2D(double* vals,
                                                     const size_t numVals,
                                                     const double indexX,
                                                     const size_t numX,
                                                     const double indexY,
                                                     const size_t numY) const {
    assert(numX >= 2);
    const size_t indexX0 = std::min(numX-2, size_t(std::floor(indexX)));
    const double wtX0 = 1.0 - (indexX - indexX0);
    const size_t indexX1 = indexX0 + 1;
    const double wtX1 = 1.0 - wtX0;
    assert(0 <= indexX0 && indexX0 < numX);
    assert(0 <= indexX1 && indexX1 < numX);

    assert(numY >= 2);
    const size_t indexY0 = std::min(numY-2, size_t(std::floor(indexY)));
    const double wtY0 = 1.0 - (indexY - indexY0);
    const size_t indexY1 = indexY0 + 1;
    const double wtY1 = 1.0 - wtY0;
    assert(0 <= indexY0 && indexY0 < numY);
    assert(0 <= indexY1 && indexY1 < numY);

    const size_t index000 = _getDataIndex(indexX0, numX, indexY0, numY, 0, 0);
    const size_t index010 = _getDataIndex(indexX0, numX, indexY1, numY, 0, 0);
    const size_t index100 = _getDataIndex(indexX1, numX, indexY0, numY, 0, 0);
    const size_t index110 = _getDataIndex(indexX1, numX, indexY1, numY, 0, 0);

    const double wt000 = wtX0 * wtY0;
    const double wt010 = wtX0 * wtY1;
    const double wt100 = wtX1 * wtY0;
    const double wt110 = wtX1 * wtY1;

    const size_t querySize = _querySize;
    for (size_t iVal = 0; iVal < querySize; ++iVal) {
        const size_t qVal = _queryValues[iVal];
        vals[iVal] =
            wt000 * _data[index000+qVal] +
            wt010 * _data[index010+qVal] +
            wt100 * _data[index100+qVal] +
            wt110 * _data[index110+qVal];
#if 0 // DEBUGGING
        std::cout << "val["<<iVal<<"]: " << vals[iVal]
                  << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
                  << ", wt010: " << wt010 << ", data: " << _data[index010+qVal]
                  << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
                  << ", wt110: " << wt110 << ", data: " << _data[index110+qVal]
                  << std::endl;
#endif
    } // for

} // _interpolate2D


// ----------------------------------------------------------------------
// Interpolate to get values at target location defined by indices in 3-D.
void
spatialdata::spatialdb::SimpleGridDB::_interpolate3D(double* vals,
                                                     const size_t numVals,
                                                     const double indexX,
                                                     const double indexY,
                                                     const double indexZ) const {
    const size_t numX = _numX;
    const size_t numY = _numY;
    const size_t numZ = _numZ;

    assert(numX >= 2);
    const size_t indexX0 = std::min(numX-2, size_t(std::floor(indexX)));
    const double wtX0 = 1.0 - (indexX - indexX0);
    const size_t indexX1 = indexX0 + 1;
    const double wtX1 = 1.0 - wtX0;
    assert(0 <= indexX0 && indexX0 < numX);
    assert(0 <= indexX1 && indexX1 < numX);

    assert(numY >= 2);
    const size_t indexY0 = std::min(numY-2, size_t(std::floor(indexY)));
    const double wtY0 = 1.0 - (indexY - indexY0);
    const size_t indexY1 = indexY0 + 1;
    const double wtY1 = 1.0 - wtY0;
    assert(0 <= indexY0 && indexY0 < numY);
    assert(0 <= indexY1 && indexY1 < numY);

    assert(numZ >= 2);
    const size_t indexZ0 = std::min(numZ-2, size_t(std::floor(indexZ)));
    const double wtZ0 = 1.0 - (indexZ - indexZ0);
    const size_t indexZ1 = indexZ0 + 1;
    const double wtZ1 = 1.0 - wtZ0;
    assert(0 <= indexZ0 && indexZ0 < numZ);
    assert(0 <= indexZ1 && indexZ1 < numZ);

    const size_t index000 = _getDataIndex(indexX0, numX, indexY0, numY, indexZ0, numZ);
    const size_t index001 = _getDataIndex(indexX0, numX, indexY0, numY, indexZ1, numZ);
    const size_t index010 = _getDataIndex(indexX0, numX, indexY1, numY, indexZ0, numZ);
    const size_t index011 = _getDataIndex(indexX0, numX, indexY1, numY, indexZ1, numZ);
    const size_t index100 = _getDataIndex(indexX1, numX, indexY0, numY, indexZ0, numZ);
    const size_t index101 = _getDataIndex(indexX1, numX, indexY0, numY, indexZ1, numZ);
    const size_t index110 = _getDataIndex(indexX1, numX, indexY1, numY, indexZ0, numZ);
    const size_t index111 = _getDataIndex(indexX1, numX, indexY1, numY, indexZ1, numZ);

    const double wt000 = wtX0 * wtY0 * wtZ0;
    const double wt001 = wtX0 * wtY0 * wtZ1;
    const double wt010 = wtX0 * wtY1 * wtZ0;
    const double wt011 = wtX0 * wtY1 * wtZ1;
    const double wt100 = wtX1 * wtY0 * wtZ0;
    const double wt101 = wtX1 * wtY0 * wtZ1;
    const double wt110 = wtX1 * wtY1 * wtZ0;
    const double wt111 = wtX1 * wtY1 * wtZ1;

    const size_t querySize = _querySize;
    for (size_t iVal = 0; iVal < querySize; ++iVal) {
        const size_t qVal = _queryValues[iVal];
        vals[iVal] =
            wt000 * _data[index000+qVal] +
            wt001 * _data[index001+qVal] +
            wt010 * _data[index010+qVal] +
            wt011 * _data[index011+qVal] +
            wt100 * _data[index100+qVal] +
            wt101 * _data[index101+qVal] +
            wt110 * _data[index110+qVal] +
            wt111 * _data[index111+qVal];
#if 0 // DEBUGGING
        std::cout << "val["<<iVal<<"]: " << vals[iVal]
                  << ", wt000: " << wt000 << ", data: " << _data[index000+qVal]
                  << ", wt001: " << wt001 << ", data: " << _data[index001+qVal]
                  << ", wt010: " << wt010 << ", data: " << _data[index010+qVal]
                  << ", wt011: " << wt011 << ", data: " << _data[index011+qVal]
                  << ", wt100: " << wt100 << ", data: " << _data[index100+qVal]
                  << ", wt101: " << wt101 << ", data: " << _data[index101+qVal]
                  << ", wt110: " << wt110 << ", data: " << _data[index110+qVal]
                  << ", wt111: " << wt111 << ", data: " << _data[index111+qVal]
                  << std::endl;
#endif
    } // for

} // _interpolate3D


// ----------------------------------------------------------------------
// Adjust indices to account for optimizations for lower dimension
// distribution.
void
spatialdata::spatialdb::SimpleGridDB::_reindex2d(double* const index0,
                                                 size_t* const size0,
                                                 double* const index1,
                                                 size_t* const size1) const {
    assert(index0);
    assert(index1);
    assert(size0);
    assert(size1);

    *size0 = _numX;
    *size1 = _numY;
    if (( 1 == _dataDim) && ( 1 == _numX) ) {
        *index0 = *index1;
        *size0 = *size1;
        *index1 = 0;
        *size1 = 1;
    } // if
} // _reindex2d


// ----------------------------------------------------------------------
// Adjust indices to account for optimizations for lower dimension
// distribution.
void
spatialdata::spatialdb::SimpleGridDB::_reindex3d(double* const index0,
                                                 size_t* const size0,
                                                 double* const index1,
                                                 size_t* const size1,
                                                 double* const index2,
                                                 size_t* const size2) const {
    assert(index0);
    assert(index1);
    assert(index2);
    assert(size0);
    assert(size1);
    assert(size2);

    *size0 = _numX;
    *size1 = _numY;
    *size2 = _numZ;
    if (2 == _dataDim) {
        if (1 == _numX) {
            *index0 = *index1;
            *size0 = *size1;
            *index1 = *index2;
            *size1 = *size2;
            *index2 = 0;
            *size2 = 1;
        } else if (1 == _numY) {
            *index1 = *index2;
            *size1 = *size2;
            *index2 = 0;
            *size2 = 1;
        } // if/else
    } else if (1 == _dataDim) {
        if (_numY > 1) {
            *index0 = *index1;
            *size0 = *size1;
            *index1 = 0;
            *size1 = 1;
            *index2 = 0;
            *size2 = 1;
        } else if (_numZ > 1) {
            *index0 = *index2;
            *size0 = *size2;
            *index1 = 0;
            *size1 = 1;
            *index2 = 0;
            *size2 = 1;
        } // if
    } // if/else
} // _reindex3d


// ----------------------------------------------------------------------
// Get index into data array.
size_t
spatialdata::spatialdb::SimpleGridDB::_getDataIndex(const double* const coords,
                                                    const size_t spaceDim) const {
    assert(coords);

    double index0 = 0;
    double index1 = 0;
    double index2 = 0;
    size_t size0 = 0;
    size_t size1 = 0;
    size_t size2 = 0;
    if (spaceDim > 2) {
        index0 = std::floor(_search(coords[0], _x, _numX)+0.5);
        index1 = std::floor(_search(coords[1], _y, _numY)+0.5);
        index2 = std::floor(_search(coords[2], _z, _numZ)+0.5);
        _reindex3d(&index0, &size0, &index1, &size1, &index2, &size2);
    } else if (spaceDim > 1) {
        index0 = std::floor(_search(coords[0], _x, _numX)+0.5);
        index1 = std::floor(_search(coords[1], _y, _numY)+0.5);
        _reindex2d(&index0, &size0, &index1, &size1);
    } else {
        assert(1 == spaceDim);
        index0 = std::floor(_search(coords[0], _x, _numX)+0.5);
    } // if

    const size_t indexData = _getDataIndex(size_t(index0), size0, size_t(index1), size1, size_t(index2), size2);
    return indexData;
} // _getDataIndex


// End of file
