#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define string char *
#define bool typedef enum Boolean { false, true } bool;

#define DOUBLE_QUOTE_CHAR                          '\"'
#define TERMINATOR_STRING                          '\0'
#define MAX_BUFFER_SIZE                            1024


typedef struct SplittedString {
    string *strings;
    size_t count;
} SplittedString;


/**
 * @brief Splits a string by spaces, while ignoring spaces within single or double quotes.
 *
 * This function takes a string as input and splits it into an array of strings,
 * where each string is separated by a space. However, if a space is found within
 * single or double quotes, it is treated as part of the string and not used for
 * splitting.
 *
 * @param str The input string to be split.
 * @return A pointer to a `SplittedString` structure containing the split strings and their count.
 *
 * @note The returned `SplittedString` structure must be freed using the free_splitted_string() function.
**/
SplittedString *split_string_by_space(string str) {
    string start = str;
    string *result = NULL;

    char buffer[MAX_BUFFER_SIZE];
    int is_double_quote = 0;
    size_t count = 0, buf_index = 0;

    while (*str) {
        is_double_quote = !is_double_quote ? *str == DOUBLE_QUOTE_CHAR : is_double_quote;

        if (isspace(*str) && !is_double_quote && buf_index > 0) {
            buffer[buf_index] = TERMINATOR_STRING;
            result = realloc(result, (count + 1) * sizeof(string));
            result[count] = strdup(buffer);
            count++;
            buf_index = 0;
        } else { buffer[buf_index++] = *str; }

        str++;
    }

    if (buf_index > 0) {
        buffer[buf_index] = TERMINATOR_STRING;
        result = realloc(result, (count + 1) * sizeof(string));
        result[count] = strdup(buffer);
        count++;
    }

    SplittedString *splitted_string = (SplittedString *)malloc(sizeof(SplittedString));
    splitted_string->strings = result;
    splitted_string->count = count;
    return splitted_string;
}


void free_splitted_string(SplittedString *splitted_string) { 
    for (size_t i = 0; i < splitted_string->count; i++) {
        free(splitted_string->strings[i]);
    }
    free(splitted_string->strings);
    free(splitted_string);
}


int main() {
    string input = strdup("Wow! You have a bunch of \"**special stuff**\".");
    SplittedString *split_result = split_string_by_space(input);

    printf("Result: [ ");
    for (size_t i = 0; i < split_result->count; i++) {
        if (i != split_result->count - 1)
            printf("'%s', ", split_result->strings[i]);
        else
            printf("'%s'", split_result->strings[i]);
    }
    printf(" ]\n");

    free_splitted_string(split_result);
    return 0;
}
