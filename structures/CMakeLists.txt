add_library (structures internal/src/rbtreenodebase.cpp)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories (structures INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})


set (HEADER_FILES "")

list (APPEND HEADER_FILES rbtree.h)
list (APPEND HEADER_FILES internal/include/rbtree.h)
list (APPEND HEADER_FILES internal/include/rbtreecolor.h)
list (APPEND HEADER_FILES internal/include/rbtreeconstiterator.h)
list (APPEND HEADER_FILES internal/include/rbtreeiterator.h)
list (APPEND HEADER_FILES internal/include/rbtreenode.h)
list (APPEND HEADER_FILES internal/include/rbtreenodebase.h)
list (APPEND HEADER_FILES internal/include/rbtreeutils.h)
list (APPEND HEADER_FILES internal/src/rbtree.inl)
list (APPEND HEADER_FILES internal/src/rbtreeconstiterator.inl)
list (APPEND HEADER_FILES internal/src/rbtreeiterator.inl)
list (APPEND HEADER_FILES internal/src/rbtreenode.inl)

install (TARGETS structures DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include)