cmake_minimum_required (VERSION 3.2 FATAL_ERROR)
project (ZserioTutorialCpp)

option(REGENERATE_ZSERIO_SOURCES "Regenerate Zserio sources from the latest GitHub release" OFF)

set(TUTORIAL_ZSERIO_RUNTIME_DIR "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/runtime")
set(TUTORIAL_ZSERIO_GEN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

if (REGENERATE_ZSERIO_SOURCES)
    find_package(Java REQUIRED)
    
    function(download_file URL_PATH LOCAL_FILE_FULL_NAME MESSAGE_DETAIL)
        if (NOT EXISTS "${LOCAL_FILE_FULL_NAME}")
            MESSAGE(STATUS "Downloading ${MESSAGE_DETAIL}")
            file(DOWNLOAD "${URL_PATH}" "${LOCAL_FILE_FULL_NAME}" STATUS DOWNLOAD_RESULT)
            list(GET DOWNLOAD_RESULT 0 DOWNLOAD_RESULT_CODE)
            if (DOWNLOAD_RESULT_CODE)
                file(REMOVE "${LOCAL_FILE_FULL_NAME}")
                MESSAGE(FATAL_ERROR "${MESSAGE_DETAIL} download failed!")
            endif ()
        endif()
    endfunction()
    
    function(unzip_file LOCAL_FILE_DIR LOCAL_FILE_NAME MESSAGE_DETAIL)
        set(LOCAL_FILE_FULL_NAME "${LOCAL_FILE_DIR}/${LOCAL_FILE_NAME}")
        MESSAGE(STATUS "Unzipping ${MESSAGE_DETAIL}")
        execute_process(COMMAND ${CMAKE_COMMAND} -E tar -xf "${LOCAL_FILE_FULL_NAME}"
            WORKING_DIRECTORY "${LOCAL_FILE_DIR}"
            RESULT_VARIABLE TAR_RESULT_CODE)
        if (TAR_RESULT_CODE)
            message(FATAL_ERROR "Unzipping failed!")
        endif ()
    endfunction()
    
    function(get_latest_zserio_version DOWNLOAD_DIR OUTPUT_VERSION_VAR_NAME)
        set(LATEST_RELEASE_JSON_FULL_NAME "${DOWNLOAD_DIR}/latest_release.json")
        download_file("https://api.github.com/repos/ndsev/zserio/releases/latest"
            "${LATEST_RELEASE_JSON_FULL_NAME}"
            "zserio latest release json")
        file(READ "${LATEST_RELEASE_JSON_FULL_NAME}" LATEST_RELEASE_JSON)
        string(REGEX MATCH "\"tag_name\": \"v([0-9\.]+)\""
            REGEX_RESULT ${LATEST_RELEASE_JSON})
        set(${OUTPUT_VERSION_VAR_NAME} "${CMAKE_MATCH_1}" PARENT_SCOPE)
    endfunction()
    
    set(TUTORIAL_DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/download")
    file(MAKE_DIRECTORY "${TUTORIAL_DOWNLOAD_DIR}") 
    
    get_latest_zserio_version("${TUTORIAL_DOWNLOAD_DIR}" LATEST_ZSERIO_VERSION)
    
    set(GITHUB_HTTPS_DOWNLOAD "https://github.com/ndsev/zserio/releases/download")
    set(ZSERIO_BIN_ZIP_NAME "zserio-${LATEST_ZSERIO_VERSION}-bin.zip")
    set(ZSERIO_RUNTIME_LIBS_ZIP_NAME "zserio-${LATEST_ZSERIO_VERSION}-runtime-libs.zip")
    
    download_file("${GITHUB_HTTPS_DOWNLOAD}/v${LATEST_ZSERIO_VERSION}/${ZSERIO_BIN_ZIP_NAME}"
        "${TUTORIAL_DOWNLOAD_DIR}/${ZSERIO_BIN_ZIP_NAME}"
        "zserio v${LATEST_ZSERIO_VERSION} binaries")
    unzip_file("${TUTORIAL_DOWNLOAD_DIR}"
        "${ZSERIO_BIN_ZIP_NAME}"
        "zserio v${LATEST_ZSERIO_VERSION} binaries")
    download_file("${GITHUB_HTTPS_DOWNLOAD}/v${LATEST_ZSERIO_VERSION}/${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
        "${TUTORIAL_DOWNLOAD_DIR}/${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
        "zserio v${LATEST_ZSERIO_VERSION} runtime libraries")
    unzip_file("${TUTORIAL_DOWNLOAD_DIR}"
        "${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
        "zserio v${LATEST_ZSERIO_VERSION} runtime libraries")
    file(COPY "${TUTORIAL_DOWNLOAD_DIR}/runtime_libs/cpp/" DESTINATION "${TUTORIAL_ZSERIO_RUNTIME_DIR}")
    
    MESSAGE(STATUS "Compiling zserio tutorial schema")
    execute_process(COMMAND ${Java_JAVA_EXECUTABLE} -jar "${TUTORIAL_DOWNLOAD_DIR}/zserio.jar"
            -cpp ${TUTORIAL_ZSERIO_GEN_DIR} -src ${CMAKE_CURRENT_SOURCE_DIR} tutorial.zs
        OUTPUT_VARIABLE ZSERIO_OUTPUT
        RESULT_VARIABLE ZSERIO_RESULT_CODE)
    if (ZSERIO_RESULT_CODE)
        message(FATAL_ERROR "Zserio tool failed!")
    endif ()
endif ()

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(${TUTORIAL_ZSERIO_RUNTIME_DIR} runtime)

file(GLOB_RECURSE SOURCES_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.cpp")
file(GLOB_RECURSE HEADERS_TUTORIAL_API "${TUTORIAL_ZSERIO_GEN_DIR}/tutorial/*.h")

add_library(ZserioTutorialCpplLib STATIC ${SOURCES_TUTORIAL_API} ${HEADERS_TUTORIAL_API})

target_include_directories(ZserioTutorialCpplLib PUBLIC "${TUTORIAL_ZSERIO_GEN_DIR}")
target_link_libraries(ZserioTutorialCpplLib ZserioCppRuntime)

add_executable(ZserioTutorialCpp src/Main.cpp)

target_link_libraries(ZserioTutorialCpp ZserioTutorialCpplLib)
