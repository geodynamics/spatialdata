# SimpleIOAscii

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.SimpleIOAscii`

ASCII writer for a simple spatial database (SimpleDB).

Implements `SimpleIO`.

## Pyre Properties

* `filename`=\<str\>: Name of database file.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateFilename at 0x11e502040>

## Example

Example of setting `SimpleIOAscii` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[dbio]
filename = mat_elastic.spatialdb
:::

