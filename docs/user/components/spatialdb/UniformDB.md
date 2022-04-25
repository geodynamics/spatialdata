# UniformDB

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.UniformDB`

Spatial database with uniform values.

Implements `SpatialDB`.

## Pyre Properties

* `data`=\<list\>: Values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}
* `description`=\<str\>: Descriptive description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x11c2979d0>
* `values`=\<list\>: Names of values in spatial database.
  - **default value**: []
  - **current value**: [], from {default}

## Example

Example of setting `UniformDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
label = Uniform material properties
values = [density, vp, vs]
data = [2000*kg/m**3, 2.0*km/s, 1000*m/s]
:::

