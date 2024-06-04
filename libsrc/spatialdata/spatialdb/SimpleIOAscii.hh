// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2024, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "SimpleIO.hh" // ISA SimpleIO

#include <iosfwd> // USES std::istream

// ----------------------------------------------------------------------
class spatialdata::spatialdb::SimpleIOAscii : public SimpleIO { // SimpleIOAscii
public:

    // PUBLIC METHODS /////////////////////////////////////////////////////

    // Using default constructor.

    // Using default destructor.

    // Using default copy constructor

    /** Clone object.
     *
     * @returns Pointer copy of this.
     */
    SimpleIO* clone(void) const;

    /** Read the database.
     *
     * @param pData Database data
     * @param ppCS Pointer to coordinate system
     */
    void read(SimpleDBData* pData,
              spatialdata::geocoords::CoordSys** ppCS);

    /** Write the database.
     *
     * @param data Database data
     * @param pCS Pointer to coordinate system
     */
    void write(const SimpleDBData& data,
               const spatialdata::geocoords::CoordSys* pCS);

private:

    // PRIVATE METHODS ////////////////////////////////////////////////////

    /** Read database version 1 file.
     *
     * @param pData Database data
     * @param ppCS Pointer to coordinate system
     * @param filein File input stream
     */
    static void _readV1(SimpleDBData* pData,
                        spatialdata::geocoords::CoordSys** ppCS,
                        std::istream& filein);

private:

    // PRIVATE MEMBERS ////////////////////////////////////////////////////

    /** Magic header in ascii files */
    static const char* HEADER;

}; // class SimpleIOAscii

#include "SimpleIOAscii.icc" // inline methods

// version
// $Id$

// End of file
