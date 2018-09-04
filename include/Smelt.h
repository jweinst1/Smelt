#ifndef SMELT_H
#define SMELT_H
/*
Main Smelt single header for CSV parsing and writing.
------------------------------
Wrriten by Joshua Weinstein
Email: jweinst1@berkeley.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Collection Structures for CSV Data*/

/*Encapsulates a single member of a CSV row.
* Holds data as characters
*/
typedef struct
{
	size_t size;
	char* data;
} smelt_item_t;

/* Holds an entire row of items.
  Supports rows that are of different sizes.
  */
typedef struct
{
	size_t size;
	smelt_item_t* items;
} smelt_row_t;

/*Encapsulates data for entire CSV table document.
* Supports rows of different sizes, does not use matrix indexing.
*/
typedef struct
{
	size_t size;
	smelt_row_t* rows;
} smelt_table_t;


// Gets size of file from current position to end.
static inline void
_get_file_ptr_size(FILE* fp, size_t* sz)
{
        fseek(fp, 0L, SEEK_END);
        *sz = ftell(fp);
        rewind(fp);
}

// Util function that makes new char array with cleaned mem
static inline char*
_new_char_array(size_t size)
{
	char* ch_arr = malloc(sizeof(char) * size + 1);
	memset(ch_arr, '\0', size + 1);
	return ch_arr;
}

// Reads an entire file into memory of a c-string
// If path cannot be reached or read from, returns NULL
static const char*
_read_file_into_c_string(const char* path)
{
	FILE* rfp;
	size_t fp_size = 0;
	rfp = fopen(path, "r");
	if(rfp == NULL) return NULL;

	_get_file_ptr_size(rfp, &fp_size);
	char* file_data = _new_char_array(fp_size);
	fread(file_data, sizeof(char), fp_size, rfp);
	fclose(rfp);

	return file_data;
}


#endif // SMELT_H
