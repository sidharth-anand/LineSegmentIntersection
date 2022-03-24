set (EXECUTABLE_NAME intersection_test)
set (INTERSECTION_OUTPUT_NAME "LineIntersectionUT")

include (platform)

set (TEST_MODULE_LIST 
    structures
    geometry
)

set (LINK_LIBRARIES ${TEST_MODULE_LIST})
set (TEST_SOURCE "")
set (TEST_INCLUDES "")

foreach (TEST_MODULE IN LISTS TEST_MODULE_LIST)
    add_subdirectory (${TEST_MODULE})
endforeach ()

foreach (TEST_MODULE IN LISTS TEST_MODULE_LIST)
    list (APPEND TEST_INCLUDES ${PROJECT_SOURCE_DIR}/src/${TEST_MODULE})
endforeach ()

add_executable(${EXECUTABLE_NAME} ${TEST_SRC} main/main.cpp)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${INTERSECTION_OUTPUT_NAME})

if (CC_IS_MINGW)
    if (CMAKE_BUILD_TYPE MATCHES "DEBUG")
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "-mwindows -mconsole")
    else (CMAKE_BUILD_TYPE MATCHES "DEBUG")
        set_target_properties(${EXECUTABLE_NAME} PROPERTIES LINK_FLAGS "-Wl,-S -mwindows")
    endif (CMAKE_BUILD_TYPE MATCHES "DEBUG")
endif(CC_IS_MINGW)

if (CC_IS_MSVC)
    target_link_options(${EXECUTABLE_NAME} PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif(CC_IS_MSVC)

target_link_libraries (${EXECUTABLE_NAME} ${LINK_LIBS} gtest gmock)
target_include_directories (${EXECUTABLE_NAME} PRIVATE 
    ${PROJECT_BINARY_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
    ${PROJECT_ROOT_DIR}
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src
    ${TEST_INCLUDES}
)

include (GoogleTest)
gtest_discover_tests(${EXECUTABLE_NAME})

install (TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION utests)