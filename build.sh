#!/usr/bin/bash

# This script builds the project, and if --clean argument
# is passed bin and build directories are removed.

# Path to the project root directory.
PROJECT_DIR="$(cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd)"

# Path to the build directory.
BUILD_DIR=${PROJECT_DIR}/build
BIN_DIR=${PROJECT_DIR}/bin

# Check if --clean flag is passed
for arg in "$@"
do
    case $arg in
        --clean)
            echo "Cleaning build and bin directories..."
            rm -rf ${BUILD_DIR}
            rm -rf ${BIN_DIR}
            exit 0
            ;;
    esac
done

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
make

# Executable directory.
EXEC_DIR=${PROJECT_DIR}/bin

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
