set (TEST_MODULE geometry)

set (MODULE_SRC "")
set (MODULE_DEPENDS "")

list (APPEND MODULE_SRC "linesegment.test.cpp")
list (APPEND MODULE_SRC "point.test.cpp")
list (APPEND MODULE_SRC "intersection.test.cpp")

list (APPEND MODULE_DEPENDS geometry)

include (testmodule)