#ifndef SPLIT_H
#define SPLIT_H

#include <stdlib.h>
#include <string.h>

#define DOUBLE_QUOTE_CHAR                          '\"'
#define TERMINATOR_STRING                          '\0'
#define MAX_BUFFER_SIZE                            1024

typedef char* string;
extern char* strdup(const char*);
typedef struct { string *strings; size_t count; } SplittedString;

/**
 * @brief Counts the number of spaces in a string, ignoring spaces within double quotes.
 *
 * This function takes a string as input and counts the number of spaces present in it.
 * However, if a space is found within double quotes, it is treated as part of the string
 * and not counted.
 *
 * @param str The input string to be analyzed.
 * @return The number of spaces found in the string, ignoring spaces within quotes.
**/
size_t count_spaces(string str);

/**
 * @brief Splits a string by spaces, while ignoring spaces within double quotes.
 *
 * This function takes a string as input and splits it into an array of strings,
 * where each string is separated by a space. However, if a space is found within
 * double quotes, it is treated as part of the string and not used for
 * splitting.
 *
 * @param str The input string to be split.
 * @return A pointer to a `SplittedString` structure containing the split strings and their count.
 *
 * @note The returned `SplittedString` structure must be freed using the free_splitted_string() function.
**/
SplittedString *split_string_by_space(string str);

void free_splitted_string(SplittedString *splitted_string);

#endif