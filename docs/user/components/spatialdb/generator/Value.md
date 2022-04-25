# Value

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.spatialdb.generator.Value`

Value generated in spatial database.

## Pyre Facilities

* `shapers`: Shapers/filters used to construct spatial distribution.
  - **current value**: 'sigleshaper', from {default}
  - **configurable as**: sigleshaper, shapers

## Pyre Properties

* `name`=\<str\>: Name of value.
  - **default value**: ''
  - **current value**: '', from {default}
* `units`=\<str\>: Units associated with value.
  - **default value**: 'none'
  - **current value**: 'none', from {default}

## Example

Example of setting `Value` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[gensimpledb]
values = [vp, vs]

[gensimpledb.values.vp]
name = Vp
units = m/s
shapers = [bg, perturbation]
:::

