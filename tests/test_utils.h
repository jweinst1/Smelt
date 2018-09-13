#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <stdio.h>
#include <stdlib.h>

/* Contains various macros to facilitate unit testing and other
 * tests for Smelt.
*/

#define TEST_BAR_SEP "_______________________________"

// Test that passes if result == expected
#define TEST_IS_EQ(name, result, expected) puts(TEST_BAR_SEP); printf("is_eq test for: %s\n", name); \
                                           if(result == expected) printf("test PASSED\n"); \
                                           else printf("test FAILED\n")

// Test that passes if result is a true value.
#define TEST_IS_TRUE(name, result) puts(TEST_BAR_SEP); printf("is_true test for: %s\n", name); \
                                           if(result) printf("test PASSED\n"); \
                                           else printf("test FAILED\n")

// Test that passes if result is a false value.
#define TEST_IS_FALSE(name, result) puts(TEST_BAR_SEP); printf("is_false test for: %s\n", name); \
                                           if(!(result)) printf("test PASSED\n"); \
                                           else printf("test FAILED\n") 

#define TEST_NOT_NULL(name, result) puts(TEST_BAR_SEP); printf("not_null test for: %s\n", name); \
                                           if(result != NULL) printf("test PASSED\n"); \
                                           else printf("test FAILED\n")

// Convenience macro to write string to file for testing purposes
#define TEST_WRITE_STRING_TO_FILE(path, string) do { \
       FILE* fp; \
       fp = fopen(path, "w+"); \
       if(fp == NULL) {fprintf(stderr, "Cannot write to file at path: %s, exiting.\n", path); exit(1);} \
       fprintf(fp, "%s", string); \
       fclose(fp); \
} while(0)



#endif