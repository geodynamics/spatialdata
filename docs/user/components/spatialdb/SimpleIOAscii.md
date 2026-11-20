% -*- markdown -*-
% -*- coding: utf-8 -*-
%
% This code is part of SpatialData, developed through the Computational Infrastructure
% for Geodynamics (https://github.com/geodynamics/spatialdata).
%
% Copyright (c) 2010-2026 The SpatialData authors and contributors
% SPDX-License-Identifier: MIT

# SimpleIOAscii

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.SimpleIOAscii`
:Journal name: `simpleioascii`

ASCII writer for a simple spatial database (SimpleDB).

Implements `SimpleIO`.

## Pyre Properties

* `filename`=\<str\>: Name of database file.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateFilename at 0x102e97b50>

## Example

Example of setting `SimpleIOAscii` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[dbio]
filename = mat_elastic.spatialdb
:::

% End of file
