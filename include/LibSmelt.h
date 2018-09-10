#ifndef LIB_SMELT_H
#define LIB_SMELT_H

// Header used for linking smelt as library instead of single-header.//
// DO NOT use for single-header include, only if linking with SmeltSHARED
/*
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