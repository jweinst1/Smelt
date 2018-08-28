#include "test_append_str.h"

void test_append_str_new(void)
{
	AppendStr* as = AppendStr_new();
	TEST_IS_EQ("append_str_new", as->len, 0);
	TEST_IS_FALSE("append_str_new_space", (as->len == as->cap));
}