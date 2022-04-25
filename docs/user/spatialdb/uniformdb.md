# UniformDB

If the values for a field a uniform (same everywhere), then a `UniformDB` or `SimpleDB` should be used.
The main difference between the two is that a `UniformDB` is specified programatically, whereas a `SimpleDB` is specified using a data file.
If the values are used in multiple places, then it is usually easier to create a `SimpleDB` data file and reuse it rather than creating a `UniformDB` programatically each time.

:::{admonition} Pyre User Interface
See [UniformDB component](../components/spatialdb/UniformDB.md).
:::

## ZeroDB

PyLith provides a special case of a `UniformDB`, called `ZeroDB`, with values set to zero for Dirichlet boundary conditions.

## Examples

We create a `UniformDB` specifying a density of 2500 kg/m$^3$ and a shear modulus of 30 GPa.

::::{tab-set}

:::{tab-item} C++

```{code-block} c++
---
caption: Creating a `UniformDB` using C++. 
---
// Data to populate UniformDB.
const size_t numValues = 2;
const char* names[numValues] = { "density", "shear_modulus" };
const char* units[numValues] = { "kg/m**3", "GPa" };
const double values[numValues] = { 2500.0, 30.0 };

// Create UniformDB 'db; and set the values.
spatialdata::spatialdb::UniformDB db;
db.setData(names, units, values, numValues);
```

:::

:::{tab-item} Python
Python applications should use the Pyre framework for creating the `UniformDB`.
We show how to do it programatically in Python for completeness.

```{code-block} python
---
caption: Creating a `UniformDB` using Python.
---
from spatialdata.spatialdb.UniformDB import UniformDB
db = UniformDB()
db.values = ["density", "shear_modulus"]
db.data = ["2500*kg/m**3", "30.0*GPa"]
db._configure()
```

:::

::::
