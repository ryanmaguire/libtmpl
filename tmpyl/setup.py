from distutils.core import setup, Extension
import os, platform
import numpy

if (platform.system() == "Darwin"):
    os.environ["CFLAGS"] = "-mmacosx-version-min=%s" % platform.mac_ver()[0]

setup(name='tmpyl',
      version='0.1',
      description='Common math and physics functions',
      author='Ryan Maguire',
      ext_modules=[
          Extension('special_functions',
                    ['rss_ringoccs/src/special_functions_module.c'],
                    include_dirs=[numpy.get_include()],
                    library_dirs=['/usr/local/lib'],
                    libraries=['rssringoccs'])
        ]
     )

