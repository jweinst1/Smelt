#ifndef SMELT_TYPES_H
#define SMELT_TYPES_H

#include <stdint.h>

/* Header to define Smelt types for main data handling
* Other files include this file to define more functions and handlers
*/

typedef struct
{
	int32_t* data;
} smelt_row_t;


#endif