#!/bin/sh

# Install lcov
git clone https://github.com/linux-test-project/lcov.git
cd lcov
git checkout v1.14
sudo make install
cd ..

# Generate report
lcov --directory . --capture --output-file coverage.info
lcov --remove coverage.info '/usr/*' "${HOME}"'/.cache/*' --output-file coverage.info
lcov --list coverage.info
bash <(curl -s https://codecov.io/bash) -f coverage.info || echo "Codecov did not collect coverage reports"
