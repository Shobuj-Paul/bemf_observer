#!/usr/bin/bash

# This script is used to build the project.

# Path to the project root directory.
PROJECT_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"

# Path to the build directory.
BUILD_DIR=${PROJECT_DIR}/build
if [ -d "$BUILD_DIR" ]; then
    echo "Build directory exists."
else
    echo "Build directory does not exist."
    echo "Creating build directory..."
    mkdir -p ${BUILD_DIR}
fi
cd ${BUILD_DIR}

# Configure and build the project.
cmake ${PROJECT_DIR}
make -j4

# Create an executable directory.
EXEC_DIR=${PROJECT_DIR}/bin
if [ -d "$EXEC_DIR" ]; then
    echo "Executable directory exists."
else
    echo "Executable directory does not exist."
    echo "Creating executable directory..."
    mkdir -p ${EXEC_DIR}
fi

# Copy executables to the executable directory.
for entry in "$BUILD_DIR"/*
do
    if [ -x "$entry" ]; then
        cp "$entry" "$EXEC_DIR" > /dev/null 2>&1 || :
    else
        :
    fi
done
echo "Created executables in $EXEC_DIR."

# List executables in the executable directory in logs.
for entry in "$EXEC_DIR"/*
do
    if [ -x "$entry" ]; then
        echo "Executable: $(basename $entry) is in $EXEC_DIR" >> ${BUILD_DIR}/build.log
    else
        :
    fi
done

# Clean the executables from build directory.
make clean
