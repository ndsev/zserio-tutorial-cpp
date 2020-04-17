# Zserio C++ Quick Start Tutorial

This Quick Start tutorial features code generation in C++. Go to the
[Zserio Java tutorial](https://github.com/ndsev/zserio-tutorial-java#zserio-java-quick-start-tutorial) or
[Zserio Python tutorial](https://github.com/ndsev/zserio-tutorial-python#zserio-python-quick-start-tutorial)
if you are interested in hands-on Java or Python with zserio.

You find the complete tutorial in this example. To follow along the description just clone this repo and check
the sources. For convenience and compatibility reasons, we have included the zserio.jar compiler and
the corresponded runtime in this repository. The zserio compiler is located in the project's root folder and
the runtime library is in subfolder `3rdparty`.

The latest build of the zserio compiler and runtime library can be get from
[Zserio Releases](https://github.com/ndsev/zserio/releases).

If you want to build from source, please follow the
[Zserio Compiler Build Instructions](https://github.com/ndsev/zserio/blob/master/doc/ZserioBuildInstructions.md#zserio-compiler-build-instructions).

## Installation & Prerequisites

Before we start, make sure you have the following components installed:

- Java JRE
- CMake

## Set up dev environment

> Everything has been already set up for you in this repository. If you are very impatient, just go to the
> project's root folder and have a quick look to the schema `tutorial.zs`. Then, run the following commands:
>
> ```
> mkdir build
> cd build
> cmake ..
> cmake --build .
> ```
>
> Now, start to play with tutorial executable `ZserioTutorialCpp` created in `build` directory.


We start with a common layout of our project/repo where we put all the source files into a `src` folder and all
3rd party stuff into `3rdparty`. For simplicity the zserio schema file stays in the project's root folder.

So our folder structure looks like this:

```
.
├───3rdparty
│   └───runtime
│       └───zserio
└───src
```

The CMakeLists.txt of zserio C++ runtime library stays in `3rdparty/runtime`.

In addition to the zserio schema file and the zserio compiler we add the following CMakeLists.txt to the project
folder:

```cmake
cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (ZserioTutorialCpp)

set(TUTORIAL_ZSERIO_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/runtime")
set(TUTORIAL_ZSERIO_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${TUTORIAL_ZSERIO_RUNTIME_DIR} runtime)

file(GLOB_RECURSE SOURCES_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.cpp")
file(GLOB_RECURSE HEADERS_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.h")

add_library(ZserioTutorialCpplLib STATIC ${SOURCES_TUTORIAL_API} ${HEADERS_TUTORIAL_API})

target_include_directories(ZserioTutorialCpplLib PUBLIC "${TUTORIAL_ZSERIO_GEN_DIR}")
target_link_libraries(ZserioTutorialCpplLib ZserioCppRuntime)

add_executable(ZserioTutorialCpp src/Main.cpp)

target_link_libraries(ZserioTutorialCpp ZserioTutorialCpplLib)
```

Now we only need to generate the code, populate the Main.cpp and we are done.

But before we can generate code, we need to write the schema definition of our data.

## Writing a schema

Open up your favorite text editor and start writing your schema. We will use the example from the zserio repo
plus some additional structures to showcase some of zserio's features.

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
    Experience      skills[] if role == Role.DEVELOPER;
};

struct Experience
{
    bit:6       yearsOfExperience;
    Language    programmingLanguage;
};

enum bit:2 Language
{
    CPP     = 0,
    JAVA    = 1,
    PYTHON  = 2,
    JS      = 3
};

enum uint8 Role
{
    DEVELOPER = 0,
    TEAM_LEAD = 1,
    CTO       = 2
};
```

We have added some of zserio's features above. Let's quickly take a look:

- **Constraints**

  Although the `uint8` of field `age` would allow values up to 255, we limit the use already in the schema
  definition by using
  a [constraint](https://github.com/ndsev/zserio/blob/master/doc/ZserioLanguageOverview.md#constraints).
  If we try to write values larger than 65, the generated writers will throw an exception.

- **Optional fields**

  The `bonus` field is prefixed with the keyword `optional` which will add a invisible 1-bit bool before that
  field which indicating whether the field exists. If it is not set then only one bit will be added to the bit
  stream. See
  [Zserio Invisibles](https://github.com/ndsev/zserio/blob/master/doc/ZserioInvisibles.md#optional-keyword)
  for more information.

- **Conditions**

    We add programming skills only if the employee is developer.

- **Bit sized elements**

  The struct `Experience` uses 1 byte in total. It uses 6 bit to store the years of programming experience and
  2 bits for the enum `Language`.

For more details on the features of zserio head over to the
[Zserio Language Overview](https://github.com/ndsev/zserio/blob/master/doc/ZserioLanguageOverview.md).

We now save the file to disk as `tutorial.zs`.

> Please note that the filename has to be equivalent to the package name inside the zserio file.
> The zserio compiler accepts arbitrary file extensions (in this case `*.zs`). But make sure that all imported
> files also have the same file extension.

## Compiling and generating code

Now we are ready to compile the schema with the zserio compiler. The zserio compiler checks the schema file and
its [imported files](https://github.com/ndsev/zserio/blob/master/doc/ZserioLanguageOverview.md#packages-and-imports)
and reports errors and warnings. In addition, the zserio compiler generates code for the supported languages
and may generate HTML documentation. For a complete overview of available options, please refer to the
[Zserio Compiler User Guide](https://github.com/ndsev/zserio/blob/master/doc/ZserioUserGuide.md#zserio-compiler-user-guide).

So let's generate some C++ code. Because zserio compiler is not available in the repository, we have 
prepared CMakeLists.txt which will download the latest zserio compiler release together with corresponded C++
runtime library from GitHub and generate C++ code. So, it's enough just to run the following command:

```
mkdir build
cd build
cmake .. -DREGENERATE_ZSERIO_SOURCES=ON
cd ..
```

After download, you can find out the latest zserio compiler in directory `build/download` and regenerate
the C++ code by hand using the command:

```
java -jar build/download/zserio.jar -cpp src tutorial.zs
```

This command generates C++ code and puts it into the `src` folder. It actually creates subfolders for each
package in the schema.

So after generating the code our folder structure looks like this:

```
.
├───3rdparty
│   └───runtime
│       └───zserio
└───src
    └───tutorial
```

Let's take a quick look what has been generated. In the `src/tutorial` folder you now find the following files:

```
Employee.h  Experience.h  Language.h  Role.h  Tutorial.cpp
```

There is one header file for each struct or enum and one amalgamated cpp file. If you don't like amalgamated
cpp file, you might use zserio command line argument `-withoutSourcesAmalgamation`.

We now have everything ready to serialize and deserialize our data.

## Serialize using the generated code

> Note: The example code in this repository features the creation of two objects of class Employee: Joe and
> his boss. We will mostly cover the creation of Joe here.

Before we start programming, let's have cmake generate our project:

```
mkdir build
cd build
cmake ..
```

Then open up your favorite IDE and start using the zserio classes by including the root element from the schema
that we want to use.

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

To be able to populate a list of skills, we need to declare an array template of type Experience:

```cpp
std::vector<tutorial::Experience> skills;
```

So now let's generate two entries for the skills list:

First we add C++ experience:

```cpp
tutorial::Experience skill1;
skill1.setYearsOfExperience(8);
skill1.setProgrammingLanguage(tutorial::Language::CPP);
skills.push_back(skill1);
```

and then also some Python experience:

```cpp
tutorial::Experience skill2;
skill2.setYearsOfExperience(4);
skill2.setProgrammingLanguage(tutorial::Language::PYTHON);
skills.push_back(skill2);
```

Don't forget to set Joe's skills:

```cpp
joe.setSkills(skills);
```

After we have set all the fields, we have to declare a BitStreamWriter and write the stream:

```cpp
zserio::BitStreamWriter writer;
joe.write(writer);
```

You may now write the stream to the disk using:

```cpp
writer.writeBufferToFile("employee.zsb");
```

You might as well access the BitstreamWriter's buffer by:

```cpp
size_t size;
const uint8_t* buffer = writer.getWriteBuffer(size);
```

You could also use the buffer for any other purpose like sending it over rpc or use it internally.

**Voila!** You have just serialized your first data with zserio.

**Congratulations!**

## Deserialize using the generated code

We already pointed out that Joe has a boss in the code we checked in. In the deserialization code we need to
keep an eye on all possible serializations we might have to deal with. So let's quickly look at the differences
between Joe and his boss.

Joe's boss is a little older, has a higher salary, gets a bonus but has no programming skills, because our
schema definition does not allow team leads to have programming skills. ;-)

```cpp
boss.setRole(tutorial::Role::TEAM_LEAD);

/* no programming skills for the boss, but a bonus! */
boss.setBonus(10000);
```

The rest is pretty similar. Check the code to see the rest.

When deserializing the zserio bit stream, we start with reading the file using BitStreamReader declaration:

```cpp
zserio::BitStreamReader reader("employee.zsb");
```

We declare an object of class Employee and deserialize the buffer with the help of the BitStreamReader we just
created. After this call all the fields within `employee` will be set.

```cpp
tutorial::Employee employee;
employee.read(reader);
```

We can now access the filled employee object via the respective getters. We still need to check for optionals
and conditionals whether they have been set.

```cpp
/* data types that are always available can simply be printed out */
std::cout << "Name: " << employee.getName() << std::endl;
std::cout << "Age: " << static_cast<unsigned int>(employee.getAge()) << std::endl;
std::cout << "Salary: " << employee.getSalary() << std::endl;
std::cout << "Role: " << zserio::enumToString(employee.getRole()) << std::endl;

/* we have to check for optionals whether they are in the stream */
if (employee.hasBonus())
    std::cout << "Bonus: " << employee.getBonus() << std::endl;
```

For the rest of the processing please refer to the code. You should have gotten the main point by now.

## Additions you will find in the code

There are some other features that we used in the code in this repo that we would like to point out briefly:

- zserio runtime exception handling
- some zserio API calls

### Zserio runtime exceptions

The zserio runtime throws three exceptions. The `zserio::CppRuntimeException`, the `zserio::BitStreamException`
and the `zserio::ConstraintException`. The last two exceptions are specialization of
`zserio::CppRuntimeException` only, so basically it is enough to catch the runtime exception for most scenarios.

It makes sense to try-catch all of your writes and reads as we do in our tutorial:

```cpp
try
{
    // read or write
}
catch (const zserio::CppRuntimeException& e)
{
    std::cout << e.what();
}
```

Examples for when an exception will be thrown:

- **Data type range exceptions**

  Zserio types get mapped to C++ native types of a bigger type sometimes (e.g. `bit:2` to `uint8_t`). You may
  assign values that fit into the C++ native type which will compile fine, but the zserio runtime will throw
  an exception if it does not fit into the zserio schema.

  > Example: Try to give Joe a programming experience of 100 years.

- **Constraint exceptions**

  If there is a constrain in the schema that requires a certain field to be set to specific value, the
  zserio runtime will throw an exception if you try to set the field without the constraint being met.

  > Example: Try to make Joe 100 years old.

### Zserio API calls

The example uses two smaller features that we would like to explain.

You can simply access the symbol name of any enumeration as a string:

```cpp
const tutorial::Language language = it->getProgrammingLanguage();

/* get string representation of Language enum value */
const std::string languageString = language.toString();
```

Of course checking for the value has better runtime performance once you do comparisons. But for debug purposes
or similar this might come handy sometimes.

The other feature is that you can always retrieve the actual bit size of the structures in zserio by calling
`bitSizeOf()`.

In the tutorial we use it for plain informational purpose only.

```cpp
std::cout << "Bit size of employee: " << employee.bitSizeOf() << std::endl;
```
