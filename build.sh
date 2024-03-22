#!/usr/bin/bash

# This script builds the project, and if --clean argument
# is passed bin and build directories are removed.

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

# Path to the bin directory.
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
        --show-failed)
            SHOW_FAILED=1
            ;;
        --debug)
            DEBUG=1
            ;;
        --release)
            RELEASE=1
            ;;
    esac
done

# Configure and build the project.
cd ${BUILD_DIR}
if [ -z "$DEBUG" ]; then
  cmake .. -DCMAKE_BUILD_TYPE=Debug ..
  make -j4
elif [ -z "$RELEASE" ]; then
  cmake .. -DCMAKE_BUILD_TYPE=Release ..
  make -j4
else
  cmake ..
  make -j4
fi

# If make completes successfully, run ctest
if [ $? -eq 0 ]; then
  cd ${BUILD_DIR}
  if [ -z "$SHOW_FAILED" ]; then
    ctest -C Debug --rerun-failed --output-on-failure
  elif [ -z "$DEBUG" ]; then
    ctest -C Debug --output-on-failure
  elif [ -z "$RELEASE" ]; then
    ctest -C Release
  else
    ctest
  fi
else
  echo -e "\nMake failed, so ctest will not be run."
fi

echo -e "\nExecutable files generated:"
cd "$PROJECT_DIR" && find ./bin -type f -executable
