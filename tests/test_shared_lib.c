#include <stdlib.h>
#include <string.h>
#include "test_utils.h"
#include "LibSmelt.h"

/*
* Main testing file for Smelt Shared Library
* -------------------------------------------
* Links in the shared library and tests via the library header
*/

void test_smelt_parse_string(void)
{
	const char* tester = "fred,5\nbob,6\ngeorge,10";
	smelt_table_t* table = Smelt_parse_string(tester);

	TEST_IS_EQ("Lib: test_smelt_parse_string_rows", table->len, 3);
	TEST_IS_EQ("Lib: test_smelt_parse_string_row_1_items", table->rows[0]->len, 2);
	Smelt_delete_table(table);
}

void test_smelt_parse_file(void)
{
	TEST_WRITE_STRING_TO_FILE("test_smelt_parse_file.txt", "5,6\n7,5\n9,8\n33,98322");
	smelt_table_t* table = Smelt_parse_file("test_smelt_parse_file.txt");
	TEST_IS_EQ("Lib: test_smelt_parse_file_rows", table->len, 4);
	TEST_IS_EQ("Lib: test_smelt_parse_file_row_1_items", table->rows[0]->len, 2);
	TEST_IS_EQ("Lib: test_smelt_parse_file_item_data", table->rows[0]->items[0]->data[0], '5');
	remove("test_smelt_parse_file.txt");
	Smelt_delete_table(table);
}

int main(int argc, char const *argv[])
{
	puts("****Smelt Library Tests****");
	test_smelt_parse_string();
	test_smelt_parse_file();
	puts("***************************");
	return 0;
}
