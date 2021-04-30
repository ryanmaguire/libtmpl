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

for filename in os.listdir("./common/"):
    if filename.endswith(".c"):
        source_files.append("./common/%s" % filename)
    else:
        continue

for filename in os.listdir("./special_functions/"):
    if filename.endswith(".c"):
        source_files.append("./special_functions/%s" % filename)
    else:
        continue

setup(name='tmpyl',
      version='0.1',
      description='Common math and physics functions',
      author='Ryan Maguire',
      ext_modules=[
          Extension('tmpyl',
                    source_files,
                    include_dirs=[numpy.get_include()],
                    library_dirs=['/usr/local/lib'],
                    libraries=['tmpl'])
        ]
     )

