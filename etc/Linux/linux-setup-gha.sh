#!/bin/bash

set -x

sudo apt-get update
cmake --version
python --version
sudo apt-get install xorg-dev libglu1-mesa-dev mesa-common-dev mesa-utils xvfb
xvfb-run glxinfo
