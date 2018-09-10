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
	int r = 999;
	smelt_item_t* parse = _smelt_parse_next_item(doc, &r);
	printf("Got item in test:%s\n", parse->data);
	TEST_IS_EQ("test_smelt_parse_next_item", r, 1);
	_smelt_item_del(parse);
}

void test_smelt_parse_next_row(void)
{
	const char* tester = "ralph,frank\ntom,scott\ncharles,tod";
	const char** doc = &tester;
	int r = 999;
	smelt_row_t* first_row = _smelt_parse_next_row(doc, &r);
	TEST_IS_EQ("test_smelt_parse_next_row_1", r, 2);
	smelt_row_t* second_row = _smelt_parse_next_row(doc, &r);
	TEST_IS_EQ("test_smelt_parse_next_row_2", r, 2);
	_smelt_row_del(first_row);
	_smelt_row_del(second_row);
}

void test_smelt_parse_table(void)
{
	const char* tester = "aa,bb,cc\ndd,ew,fd\ng";
	const char** doc = &tester;
	int r = 999;
	smelt_table_t* table = _smelt_parse_table(doc, &r);
	TEST_IS_EQ("test_smelt_parse_table", table->len, 3);
	_smelt_table_del(table);
}

void test_smelt_table_fprint(void)
{
	const char* tester = "aa,bb,cc\ndd,ew,fd";
	FILE* test_file;
	test_file = fopen("test_smelt.txt", "w+");
	const char** doc = &tester;
	int r = 999;
	smelt_table_t* table = _smelt_parse_table(doc, &r);
	_smelt_table_fprint(table, test_file);
	printf("Test: %s, Visual result: \n", "test_smelt_table_fprint");
	_smelt_table_fprint(table, stdout);
	fclose(test_file);

	// reading file to test
	const char* result_file = _read_file_into_c_string("test_smelt.txt");
	int bool_result = result_file[0] == 'a' && result_file[1] == 'a' && result_file[2] == ',';
	TEST_IS_TRUE("test_smelt_table_fprint", bool_result);
	free((void*)result_file);
	remove("test_smelt.txt");
}

int main(int argc, char const *argv[])
{
	test_smelt_parse_next_item();
	test_smelt_parse_next_row();
	test_smelt_parse_table();
	test_smelt_table_fprint();
	return 0;
}
