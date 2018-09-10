#ifndef SMELT_H
#define SMELT_H
/*
Main Smelt single header for CSV parsing and writing.
------------------------------
Wrriten by Joshua Weinstein
Email: jweinst1@berkeley.edu

MIT License

Copyright (c) 2018 Josh Weinstein

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Macro that represents the default capacity of row structure
#define SMELT_ROW_DEF_CAP 15
#define SMELT_ROW_EXP_FACTOR 2

#define SMELT_TABLE_DEF_CAP 15
#define SMELT_TABLE_EXP_FACTOR 2

// Macro that writes string to smelt_item_t only up to the item's size.
#define _SMELT_ITEM_WRITE(item, string) strncpy(item->data, string, item->size)

/*Data Structures for CSV Data*/

/*Encapsulates a single member of a CSV row.
* Holds data as characters
*/
typedef struct
{
	size_t size;
	char* data;
} smelt_item_t;

/* Holds an entire row of items.
  * Supports rows that are of different sizes.
  * Also functions as expandable container
  */
typedef struct
{
	size_t cap;
	size_t len;
	smelt_item_t** items;
} smelt_row_t;

/*Encapsulates data for entire CSV table document.
* Supports rows of different sizes, does not use matrix indexing.
*/
typedef struct
{
	size_t cap;
	size_t len;
	smelt_row_t** rows;
} smelt_table_t;

/*Note: Functions with _ are intended to be private functions*/


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

// Constructs empty smelt item of size
// Extra slot for null allows compatibility with C string functions.
static smelt_item_t*
_smelt_item_new_clean(size_t size)
{
	smelt_item_t* item = malloc(sizeof(smelt_item_t));
	item->size = size;
	item->data = _new_char_array(size);
	return item;
}
// Private fast function to print item data to stdout, stderr, or file
static inline void
_smelt_item_fprint(smelt_item_t* item, FILE* fp)
{
	fprintf(fp, "%s", item->data);
}

// Destructor function for items.
void _smelt_item_del(smelt_item_t* item)
{
	free(item->data);
	free(item);
}

// Row new, expand, delete... functions //

static smelt_row_t*
_smelt_row_new(size_t size)
{
	smelt_row_t* row = malloc(sizeof(smelt_row_t));
	row->cap = size;
	row->len = 0;
	row->items = malloc(sizeof(smelt_item_t*) * size);
	return row;
}

/* Check and expand function for row
 * Does not expand unless absolutely full.
 */
static inline void
_smelt_row_check_space(smelt_row_t* row)
{
	if(row->len == row->cap)
	{
		row->cap *= SMELT_ROW_EXP_FACTOR;
		row->items = realloc(row->items, row->cap * sizeof(smelt_item_t*));
	}
}

// Deletes all the items in a row and the row structure itself.
static inline void
_smelt_row_del(smelt_row_t* row)
{
	for(size_t i = 0; i < row->len ; i++) _smelt_item_del(row->items[i]);
	free(row);
}
// Appends new item to the end of the row
static inline void
_smelt_row_append(smelt_row_t* row, smelt_item_t* item)
{
	_smelt_row_check_space(row);
	row->items[row->len++] = item;
}

static inline void
_smelt_row_trim(smelt_row_t* row, size_t amount)
{
	while(row->len && amount--) free(row->items[row->len--]);
}

// Get Item method for rows.
// Returns NULL if index is out of range.
static inline smelt_item_t*
_smelt_row_get(smelt_row_t* row, size_t index)
{
	 return (index < row->len) ? row->items[index] : NULL;
}

// Prints a row to some file stream with exact csv format.
static void
_smelt_row_fprint(smelt_row_t* row, FILE* fp)
{
	size_t ind = 0;
	while(ind < row->len - 1)
	{
		_smelt_item_fprint(row->items[ind++], fp);
		putc(',', fp);
	}
	// Last item ended with newline
	_smelt_item_fprint(row->items[ind], fp);
	putc('\n', fp);
}

// Table new function
static smelt_table_t*
_smelt_table_new(size_t size)
{
	smelt_table_t* table = malloc(sizeof(smelt_table_t));
	table->cap = size;
	table->len = 0;
	table->rows = malloc(sizeof(smelt_row_t*) * size);
	return table;
}

/* Expansion function for table
 * Works similarly to the row expansion function.
 * Only expands when full.
 */
static inline void
_smelt_table_check_space(smelt_table_t* table)
{
	if(table->len == table->cap)
	{
		table->cap *= SMELT_TABLE_EXP_FACTOR;
		table->rows = realloc(table->rows, table->cap * sizeof(smelt_row_t*));
	}
}

static inline void
_smelt_table_append(smelt_table_t* table, smelt_row_t* row)
{
	_smelt_table_check_space(table);
	table->rows[table->len++] = row;
}

static inline void
_smelt_table_del(smelt_table_t* table)
{
	for(size_t i = 0; i < table->len; i++) _smelt_row_del(table->rows[i]);
	free(table);
}

static inline void
_smelt_table_fprint(smelt_table_t* table, FILE* fp)
{
	for(size_t i = 0; i < table->len ; i++) _smelt_row_fprint(table->rows[i], fp);
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

/* Util function that finds next terminator in CSV doc.
* - Returns 0 if null char is found.
* - Returns 1 if comma is found.
* - Returns 2 if newline is found.
* moves document to address of term.
*/
static const int
_find_next_terminator(const char** document)
{
	while(**document)
	{
		switch(**document)
		{
			case '\0':
			    return 0;
			case '"':
			     // CSV double quotes are treated as string literals
			     *document += 1;
			     while(**document != '"') *document += 1;
			     continue;
			case ',':
			    return 1;
			case '\n':
			    return 2;
			default:
			    *document += 1;
		}
	}
	return 0;
}

// Public parsing function to get another csv item out of the document.
smelt_item_t*
_smelt_parse_next_item(const char** document, int* result)
{
	if(!(**document)) return NULL;
	const char* start_parse = *document;
	*result = _find_next_terminator(document);
	smelt_item_t* parsed_item = _smelt_item_new_clean(*document - start_parse);
	*document += 1; // advances past found terminator
	_SMELT_ITEM_WRITE(parsed_item, start_parse);
	return parsed_item;
}

// Public parsing function to get the next row out of the document.
smelt_row_t*
_smelt_parse_next_row(const char** document, int* result)
{
	if(!(**document)) return NULL; // End of document reached
	smelt_row_t* row = _smelt_row_new(SMELT_ROW_DEF_CAP);
	smelt_item_t* current = NULL;
	while(*result)
	{
		current = _smelt_parse_next_item(document, result);
		if(*result == 1)
		{
			_smelt_row_append(row, current);
		}
		else if(*result == 2 || !(*result))
		{
			// End of row reached, newline sym found.
			// or, null found
			_smelt_row_append(row, current);
			return row;
		}
	}
	return row;
}

smelt_table_t*
_smelt_parse_table(const char** document, int* result)
{
	if(!(**document)) return NULL;
	smelt_table_t* table = _smelt_table_new(SMELT_TABLE_DEF_CAP);
	smelt_row_t* current = NULL;
	while(*result)
	{
		current = _smelt_parse_next_row(document, result);
		if(current == NULL) return table; // empty row at end of doc
		// Rows must always end with newline.
		if(*result == 2)
		{
			_smelt_table_append(table, current);
		}
		else if (!(*result))
		{
			// Final row reached.
			_smelt_table_append(table, current);
			return table;
		}
	}
	return table;
}

#endif // SMELT_H
