# SimpleGridDB

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.SimpleGridDB`

Simple spatial database on a logically rectangular grid aligned with the coordinate axes.
Points along the coordinate axes do not have to be uniformly spaced.

Implements `SpatialDB`.

## Pyre Properties

* `description`=\<str\>: Descriptive description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x11c2979d0>
* `filename`=\<str\>: Name for data file.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateFilename at 0x11e502c10>
* `query_type`=\<str\>: Type of query to perform.
  - **default value**: 'nearest'
  - **current value**: 'nearest', from {default}
  - **validator**: (in ['nearest', 'linear'])

## Example

Example of setting `SimpleGridDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
label = Material properties
filename = mat_elastic.spatialdb
query_type = linear
:::

