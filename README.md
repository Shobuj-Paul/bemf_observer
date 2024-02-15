# Optimized Back EMF Observer

### Dependencies
- C++ 17 compiler (GCC)
- cmake 3.15
- pre-commit
- clang-format-14

### Building the project
1. Open a shell and navigate to project root folder
2. Run the build bash script. This calls the underlying cmake command and runs tests.
```
./build.sh
```
3. Binaries are made in the bin folder. Run any executable from the bin folder.
```
./bin/pi_test
```
4. To clean the build and bin files, pass `--clean` flag to the build script.
```
./build.sh --clean
```
