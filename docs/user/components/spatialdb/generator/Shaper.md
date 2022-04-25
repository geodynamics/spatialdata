# Shaper

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.generator.Shaper`

Object for shaping spatial distribution of data while generating database.

## Pyre Facilities

* `db`: Database containing value defining shaper.
  - **current value**: 'simpledb', from {default}
  - **configurable as**: simpledb, db

## Pyre Properties

* `db_value`=\<str\>: Name of value supplied in spatial database.
  - **default value**: ''
  - **current value**: '', from {default}
* `default`=\<float\>: Default value for shaper.
  - **default value**: 0.0
  - **current value**: 0.0, from {default}
* `operand`=\<str\>: Operand to use in applying shaper.
  - **default value**: 'multiply'
  - **current value**: 'multiply', from {default}
  - **validator**: (in ['add', 'subtract', 'multiply', 'divide'])

## Example

Example of setting `Shaper` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[gensimpledb.values.density]
shapers = [bg, add]

[gensimpledb.values.one.shapers.bg]
default = 0.0
db_value = density
operand = add
db = spatialdata.spatialdb.UniformDB
db.value = [density]
db.data = [2500*kg/m**3]

[gensimpledb.values.one.shapers.add]
default = 0.0
db_value = density
operand = add
db = spatialdata.spatialdb.SimpleGridDB
db.filename = density_perturbation.spatialdb
:::

