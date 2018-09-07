#include <stdlib.h>
#include <string.h>
#include "test_utils.h"
#include "Smelt.h"

/*
* Main testing file for Smelt Single-Header Functions
* ------------------------------------------
* Tests smaller, private functions of header file implementation, as well as larger functions
*/

void test_smelt_parse_next_item(void)
{
	const char* tester = "ralph,foo";
	const char** doc = &tester;
	int r = 0;
	smelt_item_t* parse = Smelt_parse_next_item(doc, &r);
	puts(parse->data);
	TEST_IS_EQ("test_smelt_parse_next_item", r, 1);
}

int main(int argc, char const *argv[])
{
	test_smelt_parse_next_item();
	return 0;
}
