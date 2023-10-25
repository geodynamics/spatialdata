# SimpleDB

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.SimpleDB`
:Journal name: `simpledb`

Simple spatial database for points with arbitrary layout.
Use SimpleGridDB for points on a logically rectangular grid aligned with the coordinate axes.

Implements `SpatialDB`.

## Pyre Facilities

* `iohandler`: I/O handler for database.
  - **current value**: 'simpleioascii', from {default}
  - **configurable as**: simpleioascii, iohandler

## Pyre Properties

* `description`=\<str\>: Description for database.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateDescription at 0x102e94dc0>
* `query_type`=\<str\>: Type of query to perform.
  - **default value**: 'nearest'
  - **current value**: 'nearest', from {default}
  - **validator**: (in ['nearest', 'linear'])

## Example

Example of setting `SimpleDB` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[db]
description = Material properties
query_type = linear
iohandler.filename = mat_elastic.spatialdb
:::

