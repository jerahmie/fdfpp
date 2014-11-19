#!/usr/bin/env python
"""
setup.py file for SWIG fdf module
"""

from distutils.core import setup, Extension
import sys

if (sys.platform == 'linux2' or sys.platform == 'linux3') :
    fdfpp_module = Extension('_fdfpp',
    define_macros = [('MAJOR_VERSION', '0'),
                     ('MINOR_VERSION', '1')],
    include_dirs = ['/usr/local/include',
                    '/usr/include/'],
    library_dirs = ['/usr/local/lib'],
    sources=['fdfpp_wrap.cxx',
             'src/fdf.c',
             'src/fdfpp.cpp'],
    libraries=['fdf','fdfpp'],
    extra_compile_args = ['-O2' ],
    extra_link_args = '-shard'])

setup (name = 'fdfppPackage',
       version = '0.1',
       description = 'Fast data format python module',
       author = 'Jerahmie W. Radder',
       author_email = 'jerahmie@uwalumni.com',
       long_description = '''
FDF Python module.
''',
       ext_modules = [fdfpp_module])
