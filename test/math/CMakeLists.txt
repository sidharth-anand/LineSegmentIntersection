set (TEST_MODULE math)

set (MODULE_SRC "")
set (MODULE_DEPENDS "")

list (APPEND MODULE_SRC "rational.test.cpp")

list (APPEND MODULE_DEPENDS math)

include (testmodule)