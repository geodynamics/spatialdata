% -*- markdown -*-
% -*- coding: utf-8 -*-
%
% This code is part of SpatialData, developed through the Computational Infrastructure
% for Geodynamics (https://github.com/geodynamics/spatialdata).
%
% Copyright (c) 2010-2026 The SpatialData authors and contributors
% SPDX-License-Identifier: MIT

# TimeHistory

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.TimeHistory`
:Journal name: `timehistory`

Time history object for specifying temporal variation in a field.

## Pyre Properties

* `description`=\<str\>: Description for time history.
  - **default value**: 'temporal database'
  - **current value**: 'temporal database', from {default}
* `filename`=\<str\>: Name of file for time history.
  - **default value**: 'timehistory.timedb'
  - **current value**: 'timehistory.timedb', from {default}
  - **validator**: <function validateFilename at 0x102e4f7f0>

## Example

Example of setting `TimeHistory` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[timehistory]
description = Time history for Dirichlet boundary condition
filename = displacement.timedb
:::

% End of file
