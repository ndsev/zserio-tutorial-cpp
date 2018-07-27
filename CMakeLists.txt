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


