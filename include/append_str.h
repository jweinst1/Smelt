#ifndef APPEND_STR_H
#define APPEND_STR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Utility class for string that is optimized for
* char by char appending and expanding.
*/

// Controls defualt size of append str
#ifndef APPEND_STR_DEFAULT
#define APPEND_STR_DEFAULT 200
#endif

#define APPEND_STR_FACTOR 2

// Gets space left in append string
#define APPEND_STR_SPACE(as) (as->cap - as->len)
#define APPEND_STR_IS_FULL(as) (as->cap == as->len)
#define APPEND_STR_END(as) (as->string + as->len)
// Resets string to zero, allowing existing memory to be reused
#define APPEND_STR_RESET(as) (as->len = 0)

typedef struct
{
	size_t cap;
	size_t len;
	char* string;
} AppendStr;

// Creates a new append str according to the default size macro
AppendStr* AppendStr_new(void);
// Creates a new custom start size append str
AppendStr* AppendStr_new_sz(size_t start_size);
// Reserves additional capacity of some amount n
void AppendStr_reserve(AppendStr* as, size_t n);
// Prints all the characters in string to stdout.
void AppendStr_print(AppendStr* as);
// writes whole string to file, assumes fp mode
void AppendStr_to_file(AppendStr* as, FILE* fp);

/* Main character writing function
 * If full, expands by APPEND_STR_FACTOR
 * exits if realloc returns NULL
 */
void AppendStr_write_ch(AppendStr* as, char ch);

static inline void 
AppendStr_write_str(AppendStr* as, const char* string)
{
	while(*string) AppendStr_write_ch(as, *string++);
}

void AppendStr_del(AppendStr* as);


#endif //APPEND_STR_H