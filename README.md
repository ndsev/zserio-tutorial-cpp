# zserio C++ Quick Start Tutorial

This Quick Start tutorial features code generation in C++. Go to the [zserio JAVA tutorial](doc/JavaTutorial.md) if you are interested in hands-on JAVA with zserio.

### Installation & Prerequisites

Before we start, make sure you have the following components installed:

- JAVA JRE
- CMake

The easiest way of compiling the schema is to download the latest build of the zserio compiler from [Releases](https://github.com/welovemaps/zserio/releases).

If you want to  build from source, please follow the [Build Instructions for zserio Compiler](doc/zserio-compiler.md).

### Set up dev environment and zserio runtime

We start with a common layout of our project/repo where we put all the source files into a `src` folder and all 3rd party stuff into `3rdparty`. For simplicity the zserio schema file stays in the project's root folder.

Download the latest C++ runtime from [Releases](https://github.com/welovemaps/zserio/releases) and store it into a `runtimes` subfolder in `3rdparty`.

So our folder structure looks like this:
```
.
├───3rdparty
│   └───runtimes
│       └───zserio
│           └───inspector
└───src
```
The CMakeLists.txt of zserio stays in `3rdparty/runtimes`.

In addition to the zserio schema file and the zserio compiler we add the following CMakeLists.txt to the project folder:

```cmake
cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (zserio-tutorial)

add_subdirectory (3rdparty/runtimes)
set_property (TARGET ZserioCppRuntime PROPERTY POSITION_INDEPENDENT_CODE ON)

file (GLOB_RECURSE SOURCES_TUTORIAL_API "${CMAKE_CURRENT_SOURCE_DIR}/src/tutorial/*.cpp")
file (GLOB_RECURSE HEADERS_TUTORIAL_API "${CMAKE_CURRENT_SOURCE_DIR}/src/tutorial/*.h")

add_library (tutoriallib STATIC
  ${SOURCES_TUTORIAL_API}
  ${HEADERS_TUTORIAL_API}
  )

target_include_directories (tutoriallib PUBLIC src)
target_link_libraries (tutoriallib ZserioCppRuntime)
set_property (TARGET tutoriallib PROPERTY POSITION_INDEPENDENT_CODE ON)

add_executable (zserio-tutorial
  src/main.cpp
  )

target_link_libraries (zserio-tutorial tutoriallib)
```

Now we only need to generate the code, populate the main.cpp and we are done.

But before we can generate code, we need to write the schema definition of our data.

### Writing a schema

Open up your favorite text editor and start writing your schema. We will use the example from above plus some additional structures to showcase some of zserio's features.

```
package tutorial;

struct Employee
{
  uint8           age : age <= 65; // max age is 65
  string          name;
  uint16          salary;
  optional uint16 bonus;
  Role            role;

  // if employee is a developer, list programming skill

  Experience       skills[] if role == Role.DEVELOPER;
};

struct Experience
{
  bit:6     yearsOfExperience;
  Language  programmingLanguage;
};

enum bit:2 Language
{
  CPP     = 0,
  JAVA    = 1,
  PYTHON  = 3,
  JS      = 4
};

enum uint8 Role
{
  DEVELOPER = 0,
  TEAM_LEAD = 1,
  CTO       = 2,
};
```
We have added some of zserio's features above. Let's quickly take a look:

- **constraints**

  Although the `uint8` of field `age` would allow values up to 255, we limit the use already in the schema definition by using a [constraint](doc/ZserioLanguageOverview/CompoundTypes.md#constraints)
  If we try to write values larger than 65, the generated writers will throw an exception.

- **optional fields**

  The `bonus` field is prefixed with the keyword `optional` which will add a invisible 1-bit bool before that field which indicates whether the field exists. If it is not set then only one bit will be added to the byte stream.
  See [Zserio Invisibles](doc/ZserioInvisibles.md) for more information.

- **conditions**

    We add programming skills only if the employee is developer.

For more details on the features of zserio head over to the [zserio language overview](doc/ZserioLanguageOverview/ZserioLanguageOverview.md).


We now save the file to disk as `tutorial.zs`.

>Please note that the filename has to be equivalent to the package name inside the zserio file.
The zserio compiler accepts arbitrary file extensions (in this case `*.zs`). But make sure that all imported files have also the same file extension.


### Compiling and generating code

We now are ready to compile the schema with the zserio compiler. The zserio compiler checks the schema file and its [imported files](doc/ZserioLanguageOverview/PackagesAndImports.md) and reports errors and warnings.
In addition, the zserio compiler generates code for the supported languages and may generate HTML documentation. For a complete overview of available options, please refer to the [zserio compiler User Guide](doc/zserioCompilerUserGuide.md).

So let's generate some C++ code:

```
java -jar zserio.jar -cpp src tutorial.zs
```
This command generates C++ code and puts it into the `src` folder. It actually creates subfolders for each package in the schema.

So after generating the code our folder structure looks like this:

```
.
├───3rdparty
│   └───runtimes
│       └───zserio
│           └───inspector
└───src
    └───tutorial
```

Let's take a quick look what has been generated. In the `src/tutorial` folder you now find the following files:

```
Employee.h  Experience.h  Language.h  Role.h  Tutorial.cpp
```
There is one header file for each struct or enum and one amalgamated cpp file.

We now have everything ready to serialize and deserialize our data.

### Serialize/deserialize using the generated

Before we start programming, let's have cmake generate our project:

```
touch src/main.cpp
mkdir build
cd build
cmake ..
```

Then open up your favorite IDE and start using the zserio classes by including the root element from the schema that we want to use.

```cpp
#include <tutorial/Employee.h>
```

Let's declare an employee Joe and fill in some data:

```cpp
tutorial::Employee joe;
joe.setAge(32);
joe.setName("Joe Smith");
joe.setSalary(5000);
joe.setRole(tutorial::Role::DEVELOPER);
```
To be able to populate a list of skill, we need to declare a zserio object array template of type Experience:

```cpp
zserio::ObjectArray<tutorial::Experience> skills;
```

You can find a full list of available zserio templates in the [C++ zserio API overview](doc/ZserioCppAPI.md)

So now let's generate two entries for the skills list:

First we add C++ experience:
```
tutorial::Experience skill1;
skill1.setYearsOfExperience(8);
skill1.setProgrammingLanguage(tutorial::Language::CPP);
skills.push_back(skill1);
```
and then also some Python experience:

```
tutorial::Experience skill2;
skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
skill2.setYearsOfExperience(4);
skills.push_back(skill2);
```

Don't forget to set Joe's experience:

```cpp
joe.setSkills(skills);
```

So after we have set all the fields, we have to declare a BitStream writer and write the stream:

```cpp
zserio::BitStreamWriter writer;
joe.write(writer);
```

You can access the Bitstream writer's buffer by:

```cpp
size_t size;
const uint8_t* buffer = writer.getWriteBuffer(size);
```

We may now write the stream to disk using:

```cpp
std::ofstream os("tutorial.zsb", std::ofstream::binary);
os.write(reinterpret_cast<const char*>(buffer), size);
os.close();
```
Or use the buffer for any other purposes like sending it over rpc or use it internally.

Voila! You have just serialized your first data with zserio. Congratulations!
