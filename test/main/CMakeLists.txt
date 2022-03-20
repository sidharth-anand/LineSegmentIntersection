set (EXECUTABLE_NAME intersection_test)
set (INTERSECTION_OUTPUT_NAME "LineIntersectionUT")

include (platform)

set (SOURCE_LINK_LIBS ${LINK_LIBS})
set (LINK_LIBS "")

list (APPEND LINK_LIBS structures_test)
list (APPEND LINK_LIBS geometry_test)

add_executable(${EXECUTABLE_NAME} main.cpp)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES OUTPUT_NAME ${INTERSECTION_OUTPUT_NAME})

if (CC_IS_MINGW)
    if (CMAKE_BUILD_TYPE MATCHES "DEBUG")
        set_target_properties(mscore PROPERTIES LINK_FLAGS "-mwindows -mconsole")
    else (CMAKE_BUILD_TYPE MATCHES "DEBUG")
        set_target_properties(mscore PROPERTIES LINK_FLAGS "-Wl,-S -mwindows")
    endif (CMAKE_BUILD_TYPE MATCHES "DEBUG")
endif(CC_IS_MINGW)

if (CC_IS_MSVC)
    target_link_options(mscore PRIVATE /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup)
endif(CC_IS_MSVC)

target_link_libraries(intersection_test ${LINK_LIBS} ${SOURCE_LINK_LIBS})

install (TARGETS ${EXECUTABLE_NAME} RUNTIME DESTINATION utests)

if (MSVC)
    set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY true)
    set(CMAKE_SKIP_PACKAGE_ALL_DEPENDENCY true)

    if (NOT ${CMAKE_VERSION} VERSION_LESS "3.6.0")
        set_property (DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT mscore)
    endif ()

    file (TO_NATIVE_PATH "${CMAKE_INSTALL_PREFIX}/utests" VS_DEBUGGER_WORKING_DIRECTORY)

   if (NOT ${CMAKE_VERSION} VERSION_LESS "3.12.0")
      set_target_properties (${EXECUTABLE_NAME} PROPERTIES VS_DEBUGGER_COMMAND "${VS_DEBUGGER_WORKING_DIRECTORY}\\${MSCORE_EXECUTABLE_NAME}${CMAKE_EXECUTABLE_SUFFIX}")
   endif ()
   if (NOT ${CMAKE_VERSION} VERSION_LESS "3.8.0")
      set_target_properties (${EXECUTABLE_NAME} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${VS_DEBUGGER_WORKING_DIRECTORY}")
   endif ()
   if (NOT ${CMAKE_VERSION} VERSION_LESS "3.13.0")
      set_target_properties (${EXECUTABLE_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "--debug")
   endif ()

endif (MSVC)