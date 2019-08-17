#!/bin/sh

# Build docs
doxygen Doxyfile

# Commit changes and push to origin
git add -f docs/
COMMIT_MESSAGE= "Travis: Updating docs for build #${TRAVIS_BUILD_NUMBER}"
git commit -m $COMMIT_MESSAGE
REPO="https://llcoolsouder:${GH_TOKEN}@github.com/Llcoolsouder/OpenGLPlayground.git"
git push $REPO master
