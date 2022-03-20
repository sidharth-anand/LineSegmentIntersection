set (MODULE geometry)

set (MODULE_SRC "")

list (APPEND MODULE_SRC "linesegment.h")
list (APPEND MODULE_SRC "point.h")
list (APPEND MODULE_SRC "internal/include/linesegment.h")
list (APPEND MODULE_SRC "internal/src/linesegment.inl")
list (APPEND MODULE_SRC "internal/include/point.h")
list (APPEND MODULE_SRC "internal/src/point.inl")

set (MODULE_SET_LANGUAGE ON)
set (MODULE_LANGUAGE "CXX")

set (MODULE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

include (module)