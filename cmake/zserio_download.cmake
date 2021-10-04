# Download zserio binaries together with runtime libraries to the given download directory from GitHub.
function(download_zserio DOWNLOAD_DIR ZSERIO_JAR_VAR_NAME ZSERIO_RUNTIME_DIR_VAR_NAME)
    file(MAKE_DIRECTORY "${DOWNLOAD_DIR}") 

    get_latest_zserio_version("${DOWNLOAD_DIR}" LATEST_ZSERIO_VERSION)

    set(GITHUB_HTTPS_DOWNLOAD "https://github.com/ndsev/zserio/releases/download")
    set(ZSERIO_BIN_ZIP_NAME "zserio-${LATEST_ZSERIO_VERSION}-bin.zip")
    set(ZSERIO_RUNTIME_LIBS_ZIP_NAME "zserio-${LATEST_ZSERIO_VERSION}-runtime-libs.zip")

    download_file("${GITHUB_HTTPS_DOWNLOAD}/v${LATEST_ZSERIO_VERSION}/${ZSERIO_BIN_ZIP_NAME}"
            "${DOWNLOAD_DIR}/${ZSERIO_BIN_ZIP_NAME}"
            "zserio v${LATEST_ZSERIO_VERSION} binaries")
    unzip_file("${DOWNLOAD_DIR}"
            "${ZSERIO_BIN_ZIP_NAME}"
            "zserio v${LATEST_ZSERIO_VERSION} binaries")
    download_file("${GITHUB_HTTPS_DOWNLOAD}/v${LATEST_ZSERIO_VERSION}/${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
            "${DOWNLOAD_DIR}/${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
            "zserio v${LATEST_ZSERIO_VERSION} runtime libraries")
    unzip_file("${DOWNLOAD_DIR}"
            "${ZSERIO_RUNTIME_LIBS_ZIP_NAME}"
            "zserio v${LATEST_ZSERIO_VERSION} runtime libraries")

    set(${ZSERIO_JAR_VAR_NAME} "${DOWNLOAD_DIR}/zserio.jar" PARENT_SCOPE)
    set(${ZSERIO_RUNTIME_DIR_VAR_NAME} "${DOWNLOAD_DIR}/runtime_libs/cpp" PARENT_SCOPE)
endfunction()

function(get_latest_zserio_version DOWNLOAD_DIR OUTPUT_VERSION_VAR_NAME)
    set(LATEST_RELEASE_JSON_FULL_NAME "${DOWNLOAD_DIR}/latest_release.json")
    download_file("https://api.github.com/repos/ndsev/zserio/releases/latest"
            "${LATEST_RELEASE_JSON_FULL_NAME}"
            "zserio latest release json")
    file(READ "${LATEST_RELEASE_JSON_FULL_NAME}" LATEST_RELEASE_JSON)
    string(REGEX MATCH "\"tag_name\": \"v([0-9.]+)\"" REGEX_RESULT ${LATEST_RELEASE_JSON})
    set(${OUTPUT_VERSION_VAR_NAME} "${CMAKE_MATCH_1}" PARENT_SCOPE)
endfunction()

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
