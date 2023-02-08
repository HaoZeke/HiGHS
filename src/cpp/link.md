There are several ways the HiGHS library can be used within another C++ project. 

## Use HiGHS from another CMake Project

Make sure HiGHS is installed locally with the correct CMake flags:

``` bash
cd HiGHS
mkdir build
cd build
cmake -DFAST_BUILD=ON -DCMAKE_INSTALL_PREFIX=/path_to_highs_install/ ..   
cmake --build . 
cmake --install .
```

This installs HiGHS in `/path_to_highs_install/`.

Suppose another C++ CMake project has executable code in some file `main.cpp`, which includes `Highs.h`. To use the HiGHS library, edit the `CMakeLists.txt` as follows:

```
project(LOAD_HIGHS LANGUAGES CXX)

set(HIGHS_DIR path_to_highs_install/lib/cmake/highs)

find_package(HIGHS REQUIRED)
find_package(Threads REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main highs::highs)
```

The line 
```
set(HIGHS_DIR path_to_highs_install/lib/cmake/highs)
```
adds the HiGHS installation path to `HIGHS_DIR`. This is equivalent to building this project with
```
cmake -DHIGHS_DIR=path_to_highs_install/lib/cmake/highs ..
```

Alternatively, if you wish to include the code of HiGHS within your project, FetchContent is also available as follows: 

```
project(LOAD_HIGHS LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    highs
    GIT_REPOSITORY "https://github.com/ERGO-Code/HiGHS.git"
    GIT_TAG        "bazel"
)
set(FAST_BUILD ON CACHE INTERNAL "Fast Build")

FetchContent_MakeAvailable(highs)

add_executable(main call_from_cpp.cc)
target_link_libraries(main highs::highs)
```

### Compiling and linking without CMake

An executable defined in the file `use_highs.cpp` is linked with the HiGHS library as follows. Make sure HiGHS is installed in `install_folder` following the [installation guide](https://ergo-code.github.io/HiGHS/get-started.html#Install). Afterwards, compile and run with

`g++ -o use_highs use_highs.cpp -I install_folder/include/ -L install_folder/lib/ -lhighs`

`LD_LIBRARY_PATH=install_folder/lib/ ./use_highs`