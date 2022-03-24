if (NOT CMAKE_BUILD_TYPE)
    set (CMAKE_BUILD_TYPE "DEBUG")
endif ()

string (TOUPPER ${CMAKE_BUILD_TYPE} _BUILD_TYPE)

if (_BUILD_TYPE MATCHES "DEBUG")
    set (BUILD_IS_DEBUG 1)
    set (BUILD_IS_RELEASE 0)
else ()
    set (BUILD_IS_DEBUG 0)
    set (BUILD_IS_RELEASE 1)
endif ()