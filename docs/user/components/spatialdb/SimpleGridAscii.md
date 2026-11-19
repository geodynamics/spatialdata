% -*- markdown -*-
% -*- coding: utf-8 -*-
%
% This code is part of SpatialData, developed through the Computational Infrastructure
% for Geodynamics (https://github.com/geodynamics/spatialdata).
%
% Copyright (c) 2010-2026 The SpatialData authors and contributors
% SPDX-License-Identifier: MIT

# SimpleGridAscii

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.SimpleGridAscii`
:Journal name: `simplegridascii`

ASCII writer for a simple grid spatial database.

## Pyre Properties

* `filename`=\<str\>: Name of database file.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateFilename at 0x102e968c0>

## Example

Example of setting `SimpleGridAscii` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[dbio]
dbio.filename = mat_elastic.spatialdb
:::

% End of file
