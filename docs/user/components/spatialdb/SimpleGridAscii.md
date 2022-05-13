# SimpleGridAscii

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.SimpleGridAscii`
:Journal name: `simplegridascii`

ASCII writer for a simple grid spatial database.

## Pyre Properties

* `filename`=\<str\>: Name of database file.
  - **default value**: ''
  - **current value**: '', from {default}
  - **validator**: <function validateFilename at 0x11d1be0d0>

## Example

Example of setting `SimpleGridAscii` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[dbio]
dbio.filename = mat_elastic.spatialdb
:::

