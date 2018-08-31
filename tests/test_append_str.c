#include "test_append_str.h"

void test_append_str_new(void)
{
	AppendStr* as = AppendStr_new();
	TEST_IS_EQ("append_str_new", as->len, 0);
	TEST_IS_FALSE("append_str_new_space", (as->len == as->cap));
}

void test_append_str_write(void)
{
	AppendStr* as = AppendStr_new();
	AppendStr_write_ch(as, 'h');
	TEST_IS_EQ("append_str_write_ch", as->string[0], 'h');
	for(int i = 0; i < 300; i++) AppendStr_write_ch(as, '$');
	TEST_IS_EQ("append_str_write_exp", as->string[300], '$');
    // String writing test vs ch
    AppendStr_write_str(as, "Hello!");
    TEST_IS_EQ("append_str_write_str", as->string[302], 'e');
}