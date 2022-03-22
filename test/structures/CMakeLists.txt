set (TEST_MODULE structures)

set (MODULE_SRC "")
set (MODULE_DEPENDS "")

list (APPEND MODULE_SRC "rbtree.test.cpp")

list (APPEND MODULE_DEPENDS structures)

include (testmodule)