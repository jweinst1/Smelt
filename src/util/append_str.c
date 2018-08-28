#include "append_str.h"

// Local macro that adds char to append str.
#define APPEND_STR_ADD_CH(as, ch) (as->string[as->len++] = ch)

// Local macro that rellocs the strings char buffer relative to the capacity.
// Note: The capacity needs to be increased before this is done.
#define APPEND_STR_REALLOC(as) (as->string = realloc(as->string, as->cap + 1))

// Local method to wipe all the char data
static inline void 
_append_str_clr(AppendStr* as)
{
	size_t i = as->len;
	while(--i) as->string[i] = '\0';
}

AppendStr* AppendStr_new(void)
{
	AppendStr* new_as = malloc(sizeof(AppendStr));
	new_as->cap = APPEND_STR_DEFAULT;
	new_as->len = 0;
	new_as->string = malloc(sizeof(char) * APPEND_STR_DEFAULT + 1);
	return new_as;
}

AppendStr* AppendStr_new_sz(size_t start_size)
{
	AppendStr* new_as = malloc(sizeof(AppendStr));
	new_as->cap = start_size;
	new_as->len = 0;
	new_as->string = malloc(sizeof(char) * start_size + 1);
	return new_as;	
}

void AppendStr_del(AppendStr* as)
{
	free(as->string);
	free(as);
}