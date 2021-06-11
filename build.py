import pathlib
from io import StringIO

from invoke import task

FILE_PATH = pathlib.Path(__file__).parent.absolute()

import requests, zipfile


@task
def get_st_link_reflash(c):
    zip_file_url = "https://www.segger.com/downloads/jlink/STLinkReflash"
    r = requests.get(zip_file_url, stream=True)
    z = zipfile.ZipFile(StringIO.StringIO(r.content))
    z.extractall()
# https://www.segger.com/downloads/jlink/STLinkReflash
