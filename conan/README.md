# Zserio C++ Quick Start Tutorial - Instructions for Conan Users

## Installation & Prerequisites

Before we start, make sure you have the following components installed:

- Java JRE 8+
- [Conan](https://docs.conan.io/2/) 2.0+

> Don't forget to prepare conan profile - e.g. run `conan profile detect` if you are using Conan for
> the first time.

## Building

Everything has been already set up for you in the `conan` folder within this repository. Conan reads the
`conanfile.py` recipe and generates and builds the C++ project defined by the `CMakeLists.txt`.

```python
from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain

class ZserioTutorialCppRecipe(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("zserio/2.13.0")

    def build_requirements(self):
        self.tool_requires("cmake/[>=3.15]")

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False # disable CMakeUserPresets.json generation
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
```

```cmake
cmake_minimum_required(VERSION 3.15)

project(ZserioTutorialCpp)

find_package(zserio REQUIRED CONFIG) # find zserio package installed in conan's local cache

# static library which will compile generated sources
add_library(tutorial_zs STATIC ../tutorial.zs)
# generate zserio sources and add them as sources to the tutorial_zs target
# (automatically sets the zserio sources to trigger CMake re-configuration when they are modified)
zserio_generate_cpp(
    TARGET tutorial_zs
    SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/..
    MAIN_ZS tutorial.zs # can be omitted when exactly matches the path used in add_library above
    GEN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../src
)
target_link_libraries(tutorial_zs PUBLIC zserio::ZserioCppRuntime)
target_include_directories(tutorial_zs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../src)

add_executable(ZserioTutorialCpp ../src/Main.cpp)
target_link_libraries(ZserioTutorialCpp PRIVATE tutorial_zs) # link the library compiled from generated sources

```

Just go to the `conan` folder and run the following command:
```
conan --build . --output=build --build=missing
```

Zserio conan package is automatically installed (`--build=missing`), zserio sources are generated
(`zserio_generate_cpp`), compiled to the static library `tutorial_zs` and linked to
the `ZserioTutorialCpp` executable.

## Play with the compiled tutorial

You can find the compiled `ZserioTutorialCpp` executable in the `conan/build` folder.

```bash
build/ZserioTutorialCpp # prints usage
build/ZserioTutorialCpp write_joe # creates the employee.zsb which contains serialized Joe's data
build/zserioTutorialCpp read # deserializes the employee.zsb and prints out info about the employee
```

## Acquiring the zserio compiler installed via Conan

Conan puts path to the zserio compiler to environment variable `ZSERIO_JAR_FILE`. But conan build environment
must be sourced first to make the variable available.

```bash
source build/conanbuild.sh
java -jar ${ZSERIO_JAR_FILE} -src .. tutorial.zs -cpp ../src # generates the C++ sources from the schema
build/deactivate_conanbuild.sh # restore environment
```

> Check the main [README.md](../README.md#writing-a-schema) for generic info.
