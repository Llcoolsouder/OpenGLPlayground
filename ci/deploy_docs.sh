#!/bin/sh

# Build docs
doxygen Doxyfile

# Commit changes and push to origin
git add -f docs/*
COMMIT_MESSAGE="Travis: Updating docs for build #${TRAVIS_BUILD_NUMBER} [skip ci]"
git commit -m "$COMMIT_MESSAGE"
git remote rm origin
git remote add origin "https://llcoolsouder:${GH_TOKEN}@github.com/Llcoolsouder/OpenGLPlayground.git" > /dev/null 2>&1
git push --quiet --force origin master
