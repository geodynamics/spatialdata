# UniformDB

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.UniformDB`
:Journal name: `uniformdb`

Spatial database with uniform values.

Implements `SpatialDB`.

## Pyre Properties

* `data`=\<list\>: Values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}
* `description`=\<str\>: Description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x102e94dc0>
* `values`=\<list\>: Names of values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}

## Example

Example of setting `UniformDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
description = Uniform material properties
values = [density, vp, vs]
data = [2000*kg/m**3, 2.0*km/s, 1000*m/s]
:::

