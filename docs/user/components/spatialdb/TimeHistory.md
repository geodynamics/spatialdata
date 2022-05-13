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
  - **validator**: <function validateFilename at 0x11d0dbdc0>

## Example

Example of setting `TimeHistory` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[timehistory]
description = Time history for Dirichlet boundary condition
filename = displacement.timedb
:::

