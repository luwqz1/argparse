#include <stdio.h>
#include <stdlib.h>
#include "split.h"


int main() {
    string str = strdup("Wow! You have a bunch of \"**special stuff**\".");
    SplittedString *split_result = split_string_by_space(str);

    if (split_result == NULL) {
        printf("Result: None\n");
        return 0;
    }

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
