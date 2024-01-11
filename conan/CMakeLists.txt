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
