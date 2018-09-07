#ifndef LIB_SMELT_H
#define LIB_SMELT_H

// Header used for linking smelt as library instead of single-header.//
// DO NOT use for single-header include, only if linking with SmeltSHARED

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


#endif