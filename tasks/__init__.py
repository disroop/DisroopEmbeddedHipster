# !/usr/bin/env python
"""
The build.py is the single point containing the build logic. Thus this script can be used to build locally or
methods from the file can be used in the github actions.
The github actions shall just call methods from this file so we are not locked in the the build server solution.
"""

import pathlib

from invoke import Collection

from tasks import vscode, jlink, doc
from tasks import vscode, jlink, doc, project


ns = Collection.from_module(project)
ns.add_collection(Collection.from_module(vscode, name="code"))
ns.add_collection(Collection.from_module(jlink))
ns.add_collection(Collection.from_module(doc))
