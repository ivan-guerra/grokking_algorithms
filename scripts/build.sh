#!/bin/bash

# This script builds all Grokking Algorithms code samples and exercise
# solutions. build.sh can process a number of commandline parameters.
# Run 'build.sh -h' to see all the options.

# Print a help message to the console.
Help()
{
    echo "Build the GA samples and exercises."
    echo
    echo "usage: build.sh [OPTION]..."
    echo "options:"
    echo -e "\tg    Enable debug info (default OFF)."
    echo -e "\th    Print this help message."
}

BUILD_TYPE="RELEASE"

while getopts ":hg" flag
do
    case "${flag}" in
        g) BUILD_TYPE="DEBUG";;
        h) Help
           exit;;
       \?) echo "Error: Invalid option"
           Help
           exit;;
    esac
done

# Source the project configuration.
source config.sh

# Create the build directory if it does not already exist.
if [ ! -d $GA_BUILD_DIR ]
then
    mkdir -pv $GA_BUILD_DIR
fi

# Build and install the source.
pushd $GA_BUILD_DIR
    cmake ../                                 \
          -DCMAKE_BUILD_TYPE=${BUILD_TYPE} && \
    make -j$(nproc) all                    && \
    make install

    # Exit if any of the above commands fails.
    if [ $? -ne 0 ];
    then
        exit 1
    fi
popd
