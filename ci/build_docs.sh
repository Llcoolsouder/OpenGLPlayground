#!/bin/sh

# Build docs
doxygen Doxyfile
rm -rf docs/latex
cp -r docs/html/* docs/
rm -rf docs/html
