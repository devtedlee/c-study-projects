#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parentheses.h"

size_t get_matching_parentheses(parenthesis_t* parentheses, size_t max_size, const char* str)
{
    char left_parentheses[4] = {'{', '(', '[', '<'};
    char right_parentheses[4] = {'}', ')', ']', '>'};
    size_t parentheses_count = 0;
    size_t str_len = 0;
    size_t opening_i = 0;
    size_t closing_i = 0;
    size_t duplicate_parentheses_count = 0;
    size_t* right_parentheses_indexes;
    size_t* temp_right_p;
    char current_left_parentheses = '\0';
    char current_right_parentheses = '\0';
    size_t i = 0;

    str_len = strlen(str);
    if (str_len == 0) {
        return parentheses_count;
    }

    right_parentheses_indexes = (size_t*)calloc(max_size, sizeof(size_t));
    while (opening_i < str_len && parentheses_count < max_size) {
        for (i = 0; i < 4; ++i) {
            if (str[opening_i] == left_parentheses[i]) {
                current_left_parentheses = left_parentheses[i];
                current_right_parentheses = right_parentheses[i];
                closing_i = opening_i + 1;
                break;
            }
        }

        if (current_left_parentheses != '\0') {
            while (closing_i < str_len + 1) {
                if (str[closing_i] == current_left_parentheses) {
                    ++duplicate_parentheses_count;
                }

                if (str[closing_i] == current_right_parentheses) {
                    if (duplicate_parentheses_count == 0) {
                        
                        temp_right_p = right_parentheses_indexes;
                        while (*temp_right_p != 0) {
                            if (closing_i == *temp_right_p) {

                                goto end_find_right_parentheses_loop;
                            }

                            ++temp_right_p;
                        }
                        
                        parentheses[parentheses_count].opening_index = opening_i;
                        parentheses[parentheses_count].closing_index = closing_i;
                        right_parentheses_indexes[parentheses_count] = closing_i;
                        ++parentheses_count;

                        goto end_find_right_parentheses_loop;
                    }

                    if (duplicate_parentheses_count > 0) {
                        --duplicate_parentheses_count;
                    }
                }

                ++closing_i;
            }
        }

end_find_right_parentheses_loop:
        current_left_parentheses = '\0';
        current_right_parentheses = '\0';
        duplicate_parentheses_count = 0;
        ++opening_i;
    }

    free(right_parentheses_indexes);
    return parentheses_count;
}
