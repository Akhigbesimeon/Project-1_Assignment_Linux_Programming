from setuptools import setup, Extension

module = Extension('fast_calc', sources=['fast_calc.c'])

setup(
    name='FastCalc',
    version='1.0',
    description='C Extension for fast numeric computation',
    ext_modules=[module]
)
