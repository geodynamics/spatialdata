# AnalyticDB

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.AnalyticDB`
:Journal name: `AnalyticDB`

Spatial database with uniform values.

Implements `SpatialDB`.

## Pyre Facilities

* `coordsys`: Coordinate system.
  - **current value**: 'cscart', from {default}
  - **configurable as**: cscart, coordsys

## Pyre Properties

* `description`=\<str\>: Description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x1061fcc10>
* `expressions`=\<list\>: Analytical expressions for values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}
* `units`=\<list\>: Units for values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}
* `values`=\<list\>: Names of values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}

## Example

Example of setting `AnalyticDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
description = Uniform material properties
values = [density, vp, vs]
units = [kg/m**3, km/s, m/s]
expressions = [2.0*x-y, 2.0x*x/(y*y), -2.0*z]
:::

