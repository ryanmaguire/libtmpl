from distutils.core import setup, Extension
import os, platform
import numpy

if (platform.system() == "Darwin"):
    os.environ["CFLAGS"] = "-mmacosx-version-min=%s" % platform.mac_ver()[0]

source_files = []

for filename in os.listdir("./"):
    if filename.endswith(".c"):
        source_files.append(filename)
    else:
        continue

setup(name='tmpyl',
      version='0.1',
      description='Common math and physics functions',
      author='Ryan Maguire',
      ext_modules=[
          Extension('special_functions',
                    source_files,
                    include_dirs=[numpy.get_include()],
                    library_dirs=['/usr/local/lib'],
                    libraries=['tmpl'])
        ]
     )

