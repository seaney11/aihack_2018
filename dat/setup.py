from distutils.core import setup
from distutils.extension import Extension

gwas_loader = Extension(
    'gwas_loader',
    sources=['main.cpp'],
    libraries=['boost_python3-mt'],
)

setup(
    name='gwas_loader',
    version='0.1',
    ext_modules=[gwas_loader])
