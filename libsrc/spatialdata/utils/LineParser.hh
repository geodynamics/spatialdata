// =================================================================================================
// This code is part of SpatialData, developed through the Computational Infrastructure
// for Geodynamics (https://github.com/geodynamics/spatialdata).
//
// Copyright (c) 2010-2025, University of California, Davis and the SpatialData Development Team.
// All rights reserved.
//
// See https://mit-license.org/ and LICENSE.md and for license information.
// =================================================================================================
#pragma once

#include "utilsfwd.hh"

#include <string> // HASA std::string
#include <iosfwd> // USES std::istream

class spatialdata::utils::LineParser { // LineParser
    // PUBLIC METHODS ///////////////////////////////////////////////////////
public:

    /** Constructor.
     *
     * @param sin Input stream.
     * @param delimiter Comment that marks beginning of comment.
     * @param bufsize Maximum size of line
     */
    LineParser(std::istream& sin,
               const char* delimiter="#",
               const size_t bufsize=1024);

    // Destructor.
    ~LineParser(void);

    /** Get next non-comment line from file.
     *
     * @returns String with next non-comment information.
     */
    const std::string& next(void);

    /** Ignore input until character read.
     *
     * @param Character flagging to stop reading.
     */
    void ignore(const char marker);

    /** Set eating whitespace flag.
     *
     * @param flag True if whitespace should be ignored in fetching next
     * data.
     */
    void eatwhitespace(const bool flag);

    /** Putback string.
     *
     * @param buffer Buffer containing characters to put back.
     */
    void putback(const std::string& buffer);

    // NOT IMPLEMENTED //////////////////////////////////////////////////////
private:

    LineParser(const LineParser&); ///< Not implemented
    const LineParser& operator=(const LineParser&); ///< Not implemented

    // PRIVATE MEMBERS //////////////////////////////////////////////////////
private:

    std::istream& _in; ///< Input stream.
    std::string _value; ///< Value for output.
    std::string _delimiter; ///< Comment delimiter.
    const int _bufsize; ///< Size of buffer for line input.
    char* _buffer; ///< Buffer for line input.
    bool _eatwhitespace; ///< Flag indicating to eat whitespace before fetching.

}; // LineParser

// End of file
