# CompositeDB

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.CompositeDB`

Virtual spatial database implemented as a combination of two spatial databases.
This spatial database is useful when you need to provide additional values beyond those present in an existing spatial database or some values have a different layout than others.

Implements `SpatialDB`.

## Pyre Facilities

* `db_A`: Spatial database A.
  - **current value**: 'uniformdb', from {default}
  - **configurable as**: uniformdb, db_A
* `db_B`: Spatial database B.
  - **current value**: 'uniformdb', from {default}
  - **configurable as**: uniformdb, db_B

## Pyre Properties

* `description`=\<str\>: Descriptive description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x11c2979d0>
* `values_A`=\<list\>: Names of values to query with database A.
  - **default value**: []
  - **current value**: [], from {default}
* `values_B`=\<list\>: Names of values to query with database B.
  - **default value**: []
  - **current value**: [], from {default}

## Example

Example of setting `CompositeDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
values_A = [density]
values_B = [vp, vs]

db_A = spatialdata.spatialdb.UniformDB
db_A.label = Density spatial database.
db_A.values = [density]
db_A.data = [3000*kg/m**3]

db_B = spatialdata.spatialdb.SimpleDB
db_B.label = Wave speed spatial database.
db_B.iohandler.filename = vpvs.spatialdb
:::

