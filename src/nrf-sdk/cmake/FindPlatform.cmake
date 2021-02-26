include(board-settings)
cmake_minimum_required(VERSION 3.16)
set(PLATFORM_FOUND TRUE)

function(target_add_compile_definitions TARGET_NAME)
    target_compile_definitions(${TARGET_NAME} PUBLIC ${COMPILE_DEFINITIONS})
endfunction(target_add_compile_definito)

function(target_setup_runtime TARGET_NAME)
    target_add_compile_definitions(${TARGET_NAME})
    target_link_directories(${TARGET_NAME} PUBLIC ${CONAN_INCLUDE_DIRS_NRFSDK})
    target_link_options(${TARGET_NAME} PUBLIC -T ${CONAN_NRFSDK_ROOT}/${LINKER_FILE})

    set(OUTPUT_BIN_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
    SET(FILENAME "${TARGET_NAME}")
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND $ENV{OBJCOPY} -Oihex ${FILENAME} ${FILENAME}.hex
        COMMAND $ENV{OBJCOPY} -Obinary ${FILENAME} ${FILENAME}.bin
        COMMAND $ENV{OBJDUMP} -x -D -S -s ${FILENAME} | $ENV{CPPFILT} > ${FILENAME}.dump
        WORKING_DIRECTORY ${OUTPUT_BIN_DIR}
        COMMENT "Create bin and Hex")
endfunction(target_setup_runtime TARGET_NAME)