#!/bin/bash

# This script configures the default search paths for many of the binaries
# and configuration files used by the project. Other scripts may source this
# file to find the resources that they need.

CWD=$(pwd)

# Root directory.
GA_PROJECT_PATH=$(dirname ${CWD})

# Scripts directory.
GA_SCRIPTS_PATH="${GA_PROJECT_PATH}/scripts"

# Binary directory.
GA_BIN_DIR="${GA_PROJECT_PATH}/bin"

# CMake build files (see build.sh for more info).
GA_BUILD_DIR="${GA_PROJECT_PATH}/build"
