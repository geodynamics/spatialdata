# GenSimpleDBApp

% WARNING: Do not edit; this is a generated file!
:Full name: `spatialdata.spatialdb.generator.GenSimpleDBApp`
:Journal name: `gensimpledb`

Application to generate simple spatial database.

## Pyre Facilities

* `geometry`: Object defining geometry of region covered by database.
  - **current value**: 'geometry', from {default}
  - **configurable as**: geometry
* `values`: Values in database.
  - **current value**: 'siglevalue', from {default}
  - **configurable as**: siglevalue, values
* `weaver`: the pretty printer of my configuration as an XML document
  - **current value**: 'weaver', from {default}
  - **configurable as**: weaver

## Pyre Properties

* `filename`=\<str\>: Filename for generated ASCII SimpleDB.
  - **default value**: ''
  - **current value**: '/Users/baagaard/src/cig/pythia/bin/pyre_doc_components.py', from {file='/Users/baagaard/software/unix/py39-venv/pylith-debug/lib/python3.9/site-packages/pythia/pyre/inventory/ConfigurableClass.py', line=26, function='__set__'}
  - **validator**: <function validateFilename at 0x11d1fa1f0>
* `typos`=\<str\>: specifies the handling of typos in the names of properties and facilities
  - **default value**: 'strict'
  - **current value**: 'strict', from {default}
  - **validator**: (in ['relaxed', 'strict', 'pedantic'])

## Example

Example of setting `GenSimpleDBApp` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
# Create a spatial dabaset with values `Vp` and `Vs`.
#
# Vp is generated from a background value given in `vp_background.spatialdb`
# plus a perturbation given in `vp_perturbation.spatialdb`.
# 
# Vs is generatef from a backgorund value given in `vs_background.spatialdb`
# multiplied by a value given in `vs_scaling.spatialdb`.
[gensimpledb.geometry]
reader = read_geometry
data_dim = 2
coordsys.space_dim = 2

[gensimpledb]
values = [vp, vs]

[gensimpledb.values.vp]
name = Vp
units = m/s
shapers = [bg, add]

[gensimpledb.values.vp.shapers.bg]
default = 0.0
operand = add
db_value = Vp
db.description = Background
db.query_type = linear
db.iohandler.filename = vp_background.spatialdb

[gensimpledb.values.vp.shapers.add]
default = 1.0
operand = add
db_value = Vp
db.description = Add
db.query_type = linear
db.iohandler.filename = vp_perturbation.spatialdb

[gensimpledb.values.vs]
name = Vs
units = m/s
shapers = [bg, multiply]

[gensimpledb.values.vs.shapers.bg]
default = 0.0
operand = add
db_value = Vs
db.description = Background
db.query_type = linear
db.iohandler.filename = vs_background.spatialdb

[gensimpledb.values.vs.shapers.add]
default = 1.0
operand = multiply
db_value = Vs
db.description = Multiply
db.query_type = linear
db.iohandler.filename = vs_scaling.spatialdb
:::

