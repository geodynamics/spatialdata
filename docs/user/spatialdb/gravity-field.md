# Gravity Field

The `GravityField` spatial database is a specialized spatial database for specifying gravitational body forces.
It specifies the direction and gravitational acceleration with reasonable default values.

:::{admonition} Pyre User Interface
See [GravityField component](../components/spatialdb/GravityField.md).
:::

## Examples

We specify the gravitational field to be in the -y direction for a 2D Cartesian coordinate system.
The defaults provide a gravitation field for a 3D Cartesian coordinate system.

### C++

```{code-block} c++
---
caption: Creating a `GravityField` in C++.
---
spatialdata::spatialdb::GravityField gravity;
gravityField.setGravityDir(0.0, -1.0, 0.0);
```


### Python

Python applications should use the Pyre framework for creating the `CompositeDB`.
We show how to do it programatically in Python for completeness.

```{code-block} python
---
caption: Creating `GravityField` using Python.
---
from spatialdata.spatialdb.GravityField import GravityField

gravity = GravityField()
gravity.gravityDir = [0.0, -1.0, 0.0]
gravity._configure()
```
