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

// Macro that represents the default capacity of row structure
#define SMELT_ROW_DEF_CAP 15
#define SMELT_ROW_EXP_FACTOR 2

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
	size_t size;
	smelt_row_t* rows;
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

// Row new, expand, delete functions //

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
Smelt_parse_next_item(const char** document, int* result)
{
	const char* start_parse = *document;
	*result = _find_next_terminator(document);
	// End of document reached
	if(*result == 0) return NULL;
	smelt_item_t* parsed_item = _smelt_item_new_clean(*document - start_parse);
	*document += 1; // advances past found terminator
	_SMELT_ITEM_WRITE(parsed_item, start_parse);
	return parsed_item;
}

// Public parsing function to get the next row out of the document.
smelt_row_t*
Smelt_parse_next_row(const char** document, int* result)
{
	if(!(**document)) return NULL; // End of document reached
	smelt_row_t* row = _smelt_row_new(SMELT_ROW_DEF_CAP);
	smelt_item_t* current = Smelt_parse_next_item(document, result);
	while(*result)
	{
		if(*result == 1)
		{
			_smelt_row_append(row, current);
		}
		else if(*result == 2)
		{
			// End of row reached, newline sym found.
			_smelt_row_append(row, current);
			return row;
		}

		smelt_item_t* current = Smelt_parse_next_item(document, result);
	}
	return row;
}

#endif // SMELT_H
