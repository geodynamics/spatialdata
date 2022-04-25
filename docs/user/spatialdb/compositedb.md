# CompositeDB

For some use cases, it is advantageous to combine two spatial databases into one.
For example, you may want to combine elastic properties from a seismic velocity model with viscoelatic properties.
Rather than creating an entirely new spatial database with elastic and viscoelatic properties, a `CompositeDB` allows you to combine the spatial databases with elastic properties with a separate spatial database with viscoelastic properties.

Another case when a `CompositeDB` is advantaneous is when the fields within a spatial database have different layouts of the points.
`SimpleDB` and `SimpleGridDB` both require the same layout of points for all values, so you cannot specify different layouts of points for different values.
However, you can use a `CompositeDB` to combine spatial databases with different point layouts.
For example, in specifying elastic properties the density might vary with depth, whereas the shear modulus varies in both the horizontal and vertical directions.
In such a case, you could use one spatial database with a set of points in the vertical direction for the density and another spatial database with a set of points distributed in a volume for the shear modulus.

:::{warning}
The current implementation of the `CompositeDB` combines two spatial databases.
It could be extended to allow combining an arbitrary number of spatial databases, but we have not encountered sufficient uses cases to implement this feature.
:::

:::{admonition} Pyre User Interface
See [CompositeDB component](../components/spatialdb/CompositeDB.md).
:::

## Examples

We create a `CompositeDB` with density, dilatational wave speed (Vp), and shear wave speed (Vs) from a `SimpleGridDB`  spatial database and viscosity from a `SimpleDB` spatial database.

::::{tab-set}

:::{tab-item} C++

```{code-block} c++
---
caption: Creating a `CompositeDB` in C++ that combines a `SimpleGridDB` with a `SimpleDB`.
---
spatialdata::spatialdb::SimpleGridDB dbElastic;
dbElastic.setFilename("elastic.spatialdb");
const size_t numElastic = 3;
const char* namesElastic[numElastic] = { "density", "Vp", "Vs" };

spatialdata::spatialdb::SimpleDB dbViscoelastic;
spatialdata::spatialdb::SimpleIOAscii ioViscoelastic;
ioViscoelastic.setFilename("viscoelastic.spatialdb");
dbViscoelastic.setIOHandler(&ioViscoelastic);
const size_t numViscoelastic = 1;
const char* namesViscoelastic[numViscoelastic] = { "viscosity" };

spatialdata::spatialdb::CompositeDB dbComposite;
dbComposite.setDBA(&dbElastic, namesElastic, numElastic);
dbComposite.setDBB(&dbViscoelastic, namesViscoelastic, numViscoelastic);
```

:::

:::{tab-item} Python

Python applications should use the Pyre framework for creating the `CompositeDB`.
We show how to do it programatically in Python for completeness.

```{code-block} python
---
caption: Creating a `CompositeDB` using Python.
---
from spatialdata.spatialdb.SimpleGridDB import SimpleGridDB
from spatialdata.spatialdb.SimpleDB import SimpleDB
from spatialdata.spatialdb.SimpleIOAscii import SimpleIOAscii
from spatialdata.spatialdb.CompositeDB import CompositeDB

dbElastic = SimpleGridDB()
dbElastic.filename = "elastic.spatialdb"

dbViscoelastic = SimpleDB()
dbViscoelastic.iohandler = SimpleIOAscii()
dbViscoelastic.iohandler.filename = "viscoelastic.spatialdb"
dbViscoelastic.iohandler._configure()
dbViscoelastic._configure()

dbComposite = CompositeDB()
dbComposite.namesA = ["density", "Vp", "Vs"]
dbComposite.dbA = dbElastic
dbComposite.namesB = ["viscosity"]
dbComposite.dbB = dbViscoelastic
dbCompsite._configure()
```

:::

::::