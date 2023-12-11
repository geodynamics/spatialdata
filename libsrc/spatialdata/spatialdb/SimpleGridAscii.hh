// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2023, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "SimpleGridDB.hh" // ISA SimpleGridDB

#include <iosfwd> // USES std::istream

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleGridAscii { // SimpleGridAscii
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    // Using default constructor.

    // Using default destructor.

    // Using default copy constructor

    /** Read the database.
     *
     * @param db Spatial database.
     */
    static
    void read(SimpleGridDB* db);

    /** Write the database.
     *
     * @param db Spatial database.
     */
    static
    void write(const SimpleGridDB& db);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    /** Read data file header.
     *
     * @param filein Input stream.
     * @param db Spatial database.
     */
    static
    void _readHeader(std::istream& filein,
                     SimpleGridDB* const db);

    /** Read data values.
     *
     * @param filein Input stream.
     * @param db Spatial database.
     */
    static
    void _readData(std::istream& filein,
                   SimpleGridDB* const db);

    /** Write the data file header.
     *
     * @param fileout Output stream.
     * @param db Spatial database.
     */
    static
    void _writeHeader(std::ostream& fileout,
                      const SimpleGridDB& db);

    /** Write data values.
     *
     * @param fileout Output stream.
     * @param db Spatial database.
     */
    static
    void _writeData(std::ostream& fileout,
                    const SimpleGridDB& db);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    /** Magic header in ascii files */
    static const char* FILEHEADER;

}; // class SimpleGridAscii

// End of file
