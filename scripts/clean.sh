#!/bin/bash

# This script cleans up the source tree leaving it as if a fresh clone of
# the repository was made.

LGREEN='\033[1;32m'
NC='\033[0m'

# Source the project configuration.
source config.sh

# Remove the binary directory.
if [ -d $GA_BIN_DIR ]
then
    echo -e "${LGREEN}Removing '$GA_BIN_DIR'${NC}"
    rm -r $GA_BIN_DIR
fi

# Remove the CMake build directory.
if [ -d $GA_BUILD_DIR ]
then
    echo -e "${LGREEN}Removing '$GA_BUILD_DIR'${NC}"
    rm -r $GA_BUILD_DIR
fi
