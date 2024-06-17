~/src/cig/pythia/bin/pyre_doc_components.py --package=SpatialData --src-path=$PYENV/pylith-debug/lib/python3.12/site-packages/spatialdata --output-path=./ --manual-toc=toc.json
cat index.md | sed -e "s#apps/index.md#implementations.md\\napps/index.md#g" > tmp.md && mv -f tmp.md index.md
