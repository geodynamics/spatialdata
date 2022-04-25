# PointsStream

% WARNING: Do not edit; this is a generated file!
Full name: `spatialdata.utils.PointsStream`

Object for reading/writing points from stdin/stdout.

## Pyre Properties

* `comment_flag`=\<str\>: String identifying comment.
  - **default value**: '#'
  - **current value**: '#', from {default}
* `filename`=\<str\>: Name of file for input/output.
  - **default value**: ''
  - **current value**: '', from {default}
* `number_format`=\<str\>: C style string specifying number format.
  - **default value**: '%14.5e'
  - **current value**: '%14.5e', from {default}

## Example

Example of setting `PointsStream` Pyre properties and facilities in a parameter file.

:::{code-block} cfg
[points_writer]
filename = points.txt
comment_flag = #
number_format = %14.5e
:::

