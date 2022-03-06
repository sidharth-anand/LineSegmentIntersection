add_library (geometry INTERFACE)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories (geometry INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

set (HEADER_FILES "")

list (APPEND HEADER_FILES linesegment.h)
list (APPEND HEADER_FILES point.h)
list (APPEND HEADER_FILES internal/include/linesegment.h)
list (APPEND HEADER_FILES internal/include/point.h)
list (APPEND HEADER_FILES internal/src/linesegment.inl)
list (APPEND HEADER_FILES internal/src/point.inl)

install (TARGETS geometry DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include)