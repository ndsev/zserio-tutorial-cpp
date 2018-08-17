cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (ZserioTutorialCpp)

add_subdirectory(3rdparty/runtime)

file(GLOB_RECURSE SOURCES_TUTORIAL_API "${CMAKE_CURRENT_SOURCE_DIR}/src/tutorial/*.cpp")
file(GLOB_RECURSE HEADERS_TUTORIAL_API "${CMAKE_CURRENT_SOURCE_DIR}/src/tutorial/*.h")

add_library(ZserioTutorialCpplLib STATIC ${SOURCES_TUTORIAL_API} ${HEADERS_TUTORIAL_API})

target_include_directories(ZserioTutorialCpplLib PUBLIC src)
target_link_libraries(ZserioTutorialCpplLib ZserioCppRuntime)

add_executable(ZserioTutorialCpp src/Main.cpp)

target_link_libraries(ZserioTutorialCpp ZserioTutorialCpplLib)
