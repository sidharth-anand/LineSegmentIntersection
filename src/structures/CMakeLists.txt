set (MODULE structures)

set (MODULE_SRC "")

list (APPEND MODULE_SRC rbtree.h)
list (APPEND MODULE_SRC internal/include/rbtree.h)
list (APPEND MODULE_SRC internal/src/rbtree.inl)
list (APPEND MODULE_SRC internal/include/rbtreecolor.h)
list (APPEND MODULE_SRC internal/include/rbtreeconstiterator.h)
list (APPEND MODULE_SRC internal/src/rbtreeconstiterator.inl)
list (APPEND MODULE_SRC internal/include/rbtreeiterator.h)
list (APPEND MODULE_SRC internal/src/rbtreeiterator.inl)
list (APPEND MODULE_SRC internal/include/rbtreenode.h)
list (APPEND MODULE_SRC internal/src/rbtreenode.inl)
list (APPEND MODULE_SRC internal/include/rbtreenodebase.h)
list (APPEND MODULE_SRC internal/src/rbtreenodebase.cpp)
list (APPEND MODULE_SRC internal/include/rbtreeutils.h)

set (MODULE_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

include (module)