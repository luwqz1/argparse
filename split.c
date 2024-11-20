#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


size_t count_spaces(string str) {
    int is_double_quote = 0;
    size_t count = 0;

    while (*str) {
        if (isspace(*str) && !is_double_quote) { count++; }
        is_double_quote = !is_double_quote ? *str == DOUBLE_QUOTE_CHAR : is_double_quote;
        str++;
    }

    return count;
}


SplittedString *split_string_by_space(string str) {
    size_t count = count_spaces(str), buf_index = 0, result_index = 0;

    char buffer[MAX_BUFFER_SIZE];
    int is_double_quote = 0;

    if (count == 0) return NULL;

    count++;
    string *result = malloc(count * sizeof(string));
    
    while (*str) {
        is_double_quote = !is_double_quote ? *str == DOUBLE_QUOTE_CHAR : is_double_quote;

        if (isspace(*str) && !is_double_quote && buf_index > 0) {
            buffer[buf_index] = TERMINATOR_STRING;
            result[result_index] = strdup(buffer);
            buf_index = 0;
            result_index++;
        }
        else { buffer[buf_index++] = *str; }

        str++;
    }

    // End the last word if any
    if (buf_index > 0) {
        buffer[buf_index] = TERMINATOR_STRING;
        result[result_index] = strdup(buffer);
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
