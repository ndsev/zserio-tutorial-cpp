cmake_minimum_required (VERSION 3.5 FATAL_ERROR)
project (ZserioTutorialCppPmr)

option(REGENERATE_CPP_SOURCES "Regenerate C++ sources using the latest zserio from GitHub release" OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake")
include(zserio_download)

download_zserio("${CMAKE_CURRENT_BINARY_DIR}/download" ZSERIO_JAR ZSERIO_RUNTIME_DIR)

set(TUTORIAL_ZSERIO_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (REGENERATE_CPP_SOURCES)
    find_package(Java REQUIRED)

    MESSAGE(STATUS "Compiling zserio tutorial schema")
    execute_process(COMMAND ${Java_JAVA_EXECUTABLE} -jar "${ZSERIO_JAR}"
            -cpp ${TUTORIAL_ZSERIO_GEN_DIR} -src ${CMAKE_CURRENT_SOURCE_DIR}/.. tutorial.zs
            -setCppAllocator polymorphic
        OUTPUT_VARIABLE ZSERIO_OUTPUT
        RESULT_VARIABLE ZSERIO_RESULT_CODE)
    if (ZSERIO_RESULT_CODE)
        message(FATAL_ERROR "Zserio tool failed!")
    endif ()
endif ()

add_subdirectory(${ZSERIO_RUNTIME_DIR} runtime)

file(GLOB_RECURSE SOURCES_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.cpp")
file(GLOB_RECURSE HEADERS_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.h")

add_library(ZserioTutorialCppPmrLib STATIC ${SOURCES_TUTORIAL_API} ${HEADERS_TUTORIAL_API})

set_target_properties(ZserioTutorialCppPmrLib PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
target_include_directories(ZserioTutorialCppPmrLib PUBLIC "${TUTORIAL_ZSERIO_GEN_DIR}")
target_link_libraries(ZserioTutorialCppPmrLib ZserioCppRuntime)

add_executable(ZserioTutorialCppPmr src/Main.cpp)

set_target_properties(ZserioTutorialCppPmr PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES CXX_EXTENSIONS NO)
target_link_libraries(ZserioTutorialCppPmr ZserioTutorialCppPmrLib)
