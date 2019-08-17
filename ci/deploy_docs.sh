#!/bin/sh

git checkout master

# Build docs
doxygen Doxyfile
rm -rf docs/latex
cp docs/html/* docs/
rm -rf docs/html

# Commit changes and push to origin
git status
git add -f docs/*
git status
COMMIT_MESSAGE="Travis: Updating docs for build #${TRAVIS_BUILD_NUMBER} [skip ci]"
git commit -m "${COMMIT_MESSAGE}"
git status
git remote add origin-travis "https://llcoolsouder:${GH_TOKEN}@${GH_REF}"
git push --set-upstream origin-travis master
