#!/bin/sh

# Commit changes and push to origin
git add -f TODO.md docs/*
COMMIT_MESSAGE="Travis: Updating docs for build #${TRAVIS_BUILD_NUMBER} [skip ci]"
git commit -m "${COMMIT_MESSAGE}"
git remote add origin-travis "https://${GH_TOKEN}@${GH_REF}"
git push --set-upstream origin-travis master