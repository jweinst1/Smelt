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

/* Test for how big the row can grow when more and more items are 
*  append to it. Also tests for freeing large amount of items.
*/
void test_smelt_row_grow(void)
{
	smelt_row_t* row = _smelt_row_new(10);
	smelt_item_t* retrieve;
	for(int i = 0; i < 500; i++)
	{
		 retrieve = _smelt_item_new_clean(30);
		_smelt_row_append(row, retrieve);
	}
	TEST_IS_EQ("test_smelt_row_grow", row->len, 500);
	_smelt_row_del(row);
}

void test_smelt_item_new_int(void)
{
	smelt_item_t* num = _smelt_item_new_int(10);
	int result = num->data[0] == '1' && num->data[1] == '0';
	TEST_IS_TRUE("test_smelt_item_new_int", result);
	_smelt_item_del(num);
}

int main(int argc, char const *argv[])
{
	puts("~~~~~~Smelt Header Tests~~~~~~~~~~~");
	test_smelt_parse_next_item();
	test_smelt_parse_next_row();
	test_smelt_parse_table();
	test_smelt_table_fprint();
	test_smelt_row_grow();
	test_smelt_item_new_int();
	puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	return 0;
}
