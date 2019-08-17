#!/bin/sh

# Build docs
doxygen Doxyfile

# Commit changes and push to origin
git add -f docs/*
COMMIT_MESSAGE="Travis: Updating docs for build #${TRAVIS_BUILD_NUMBER} [skip ci]"
git commit --allow-empty -m "${COMMIT_MESSAGE}"
git remote add origin-travis "https://llcoolsouder:${GH_TOKEN}@${GH_REF}"
git push --set-upstream origin-travis master
