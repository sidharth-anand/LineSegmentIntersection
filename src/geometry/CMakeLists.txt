set (MODULE geometry)

set (MODULE_SRC "")

list (APPEND MODULE_SRC "linesegment.h")
list (APPEND MODULE_SRC "point.h")
list (APPEND MODULE_SRC "intersection.h")
list (APPEND MODULE_SRC "internal/include/slope.h")
list (APPEND MODULE_SRC "internal/src/slope.cpp")
list (APPEND MODULE_SRC "internal/include/point.h")
list (APPEND MODULE_SRC "internal/src/point.inl")
list (APPEND MODULE_SRC "internal/include/linesegment.h")
list (APPEND MODULE_SRC "internal/src/linesegment.inl")
list (APPEND MODULE_SRC "internal/include/intersection.h")
list (APPEND MODULE_SRC "internal/src/intersection.cpp")

set (MODULE_SET_LANGUAGE ON)
set (MODULE_LANGUAGE "CXX")

set (MODULE_LINK structures)

set (MODULE_INCLUDE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}/src/structures
)

include (module)