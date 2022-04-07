set (MODULE math)

set (MODULE_SRC "")

list (APPEND MODULE_SRC rational.h)
list (APPEND MODULE_SRC internal/include/rational.h)
list (APPEND MODULE_SRC internal/src/rational.inl)
list (APPEND MODULE_SRC internal/src/rational.cpp)

set (MODULE_SET_LANGUAGE ON)
set (MODULE_LANGUAGE "CXX")

set (MODULE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

include (module)