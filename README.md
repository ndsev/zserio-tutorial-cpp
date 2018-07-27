# zserio C++ Quick Start Tutorial

This Quick Start tutorial features code generation in C++. Go to the [zserio JAVA tutorial](https://) if you are interested in hands-on JAVA with zserio.

You find the complete tutorial in this example. To follow along the description just clone the repo and check the sources. For convenience and compatibility reasons we have included the runtime in this repository, although we describe how to obtain it below.

## Installation & Prerequisites

Before we start, make sure you have the following components installed:

- JAVA JRE
- CMake

The easiest way of compiling the schema is to download the latest build of the zserio compiler from [zserio Releases](https://github.com/welovemaps/zserio/releases).

If you want to  build from source, please follow the [Build Instructions for zserio Compiler](https://github.com/welovemaps/doc/zserio-compiler.md).

## Set up dev environment and zserio runtime

We start with a common layout of our project/repo where we put all the source files into a `src` folder and all 3rd party stuff into `3rdparty`. For simplicity the zserio schema file stays in the project's root folder.

Download the latest C++ runtime from [zserio Releases](https://github.com/welovemaps/zserio/releases) and store it into a `runtimes` subfolder in `3rdparty`.

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

## Writing a schema

Open up your favorite text editor and start writing your schema. We will use the example from the zserio repo plus some additional structures to showcase some of zserio's features.

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

  Although the `uint8` of field `age` would allow values up to 255, we limit the use already in the schema definition by using a [constraint](https://github.com/welovemaps/zserio/doc/ZserioLanguageOverview/CompoundTypes.md#constraints)
  If we try to write values larger than 65, the generated writers will throw an exception.

- **optional fields**

  The `bonus` field is prefixed with the keyword `optional` which will add a invisible 1-bit bool before that field which indicates whether the field exists. If it is not set then only one bit will be added to the byte stream.
  See [Zserio Invisibles](https://github.com/welovemaps/zserio/doc/ZserioInvisibles.md) for more information.

- **conditions**

    We add programming skills only if the employee is developer.

- **bit sized elements**

  The struct `Experience` uses 1 byte in total. It uses 6 bit to store the years of programming experience and 2 bits for the enum `Language`.

For more details on the features of zserio head over to the [zserio language overview](https://github.com/welovemaps/zserio/doc/ZserioLanguageOverview/ZserioLanguageOverview.md).


We now save the file to disk as `tutorial.zs`.

>Please note that the filename has to be equivalent to the package name inside the zserio file.
The zserio compiler accepts arbitrary file extensions (in this case `*.zs`). But make sure that all imported files also have the same file extension.


## Compiling and generating code

Now we are ready to compile the schema with the zserio compiler. The zserio compiler checks the schema file and its [imported files](https://github.com/welovemaps/zserio/doc/ZserioLanguageOverview/PackagesAndImports.md) and reports errors and warnings.
In addition, the zserio compiler generates code for the supported languages and may generate HTML documentation. For a complete overview of available options, please refer to the [zserio compiler User Guide](https://github.com/welovemaps/zserio/doc/zserioCompilerUserGuide.md).

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

## Serialize using the generated code

> Note: The example code in this repository features the creation of two objects of class Employee: Joe and his boss. We will mostly cover the creation of Joe here.


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
To be able to populate a list of skills, we need to declare a zserio object array template of type Experience:

```cpp
zserio::ObjectArray<tutorial::Experience> skills;
```

You can find a full list of available zserio templates in the [C++ zserio API overview](https://github.com/welovemaps/zserio/doc/ZserioCppAPI.md)

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

After we have set all the fields, we have to declare a BitStream writer and write the stream:

```cpp
zserio::BitStreamWriter writer;
joe.write(writer);
```

You can access the Bitstream writer's buffer by:

```cpp
size_t size;
const uint8_t* buffer = writer.getWriteBuffer(size);
```

and may now write the stream to disk using:

```cpp
std::ofstream os("tutorial.zsb", std::ofstream::binary);
os.write(reinterpret_cast<const char*>(buffer), size);
os.close();
```
You could also use the buffer for any other purpose like sending it over rpc or use it internally.

**Voila!** You have just serialized your first data with zserio.

**Congratulations!**


## Deserialize using the generated code
We already pointed out that Joe has a boss in the code we checked in. In the deserialization code we need to keep an eye on all possible serializations we might have to deal with. So let's quickly look at the differences between Joe and his boss.

Joe's boss is a little older, has a higher salary, gets a bonus but has no programming skills, because our schema definition does not allow team leads to have programming skills ;-)

```cpp
boss.setRole(tutorial::Role::TEAM_LEAD);

/* No programming skills for the boss, but a bonus! */

boss.setBonus(10000);
```
The rest is pretty similar. Check the code to see the rest.


When deserializing the zserio byte stream we start with reading in the file.

```cpp
std::ifstream is("employee.zsb", std::ifstream::binary);
is.seekg(0, is.end);
size_t length = is.tellg();
is.seekg(0, is.beg);
char* buffer = new char[length];
is.read(buffer, length);
```

Then we declare a BitStreamReader to be able to deserialize the buffer. We need to pass the buffer and its length to the constructor.

```cpp
zserio::BitStreamReader reader((const uint8_t*)buffer, length);
```
We declare an object of class Employee and deserialize the buffer with the help of the BitStreamReader we just generated. After this call all the fields within `employee` will be set.

```cpp
tutorial::Employee employee;
employee.read(reader);
```

We can now access the filled employee object via the respective getters. We still need to check for optionals and conditionals whether they have been set.

```cpp
/* Data types that are always available can simply be assigned */
std::string name = employee.getName();
std::uint8_t age = employee.getAge();
std::uint16_t salary = employee.getSalary();

tutorial::Role role = employee.getRole();


/* We have to check for optionals whether they are in the stream */
std::uint16_t bonus = 0;
if(employee.hasBonus())
	bonus = employee.getBonus();

/* We also have to check for conditions if they applied. */
zserio::ObjectArray<tutorial::Experience> skills;
if (employee.hasSkills())
	skills = employee.getSkills();
```

For the rest of the processing please refer to the code. You should have gotten the main point by now.

## Additions you will find in the code

There are some other features that we used in the code in this repo that we would like to point out
briefly:
- zserio runtime exception handling
- some zserio API calls

### zserio runtime exceptions

The zserio runtime throws two exceptions. The `zserio::CppRuntimeException` and the `zserio::BitStreamException`.

Basically it is enough to catch the runtime exception for most scenarios. It makes sense to try-catch all of your writes as we do in our tutorial:

```cpp
try
{
	joe.write(writer);
}
catch (zserio::CppRuntimeException &e)
{
	std::cout << e.what();
}
```

Examples for when an exception will be thrown:
- **Data type range exceptions**

  zserio types get mapped to C++ STL types of a bigger type sometimes (e.g. bit:2 to uint8_t). You may assign values that fit into the STL type which will compile fine, but the BitStreamWriter will throw an exception if it does not fit into the zserio schema.
  The same applies to constraints.
  >(Example: Try to give Joe a programming experience of 100 years or make him 100 years old)

- **Setting fields for which the condition is not met**

  If there are conditions in the schema that require a certain field to be set to specific value, the BitStreamWriter will throw an exception if you try to set the field without the condition being met.
  >Example: Try setting programming skills for Joe's boss.

### zserio API calls

The example uses two smaller features that we would like to explain.

You can simply access the symbol name of any enumeration as a string:
```cpp
tutorial::Language lang = experience.getProgrammingLanguage();

/* Get string representation of Language enum value */
std::string lang_str = lang.toString();
```
Of course checking for the value has better runtime performance once you do comparisons. But for debug purposes or similar this might come handy sometimes.

The other feature is that you can always retrieve the actual bit size of the structures in zserio by calling `bitSizeOf()`.

In the tutorial we use it form plain informational purpose.
```cpp
std::cout << "Bit size of employee: " << (int)employee.bitSizeOf();
```
