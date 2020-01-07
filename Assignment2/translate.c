#include <stdio.h>
#include <string.h>
#include "translate.h"

int translate(int argc, const char** argv)
{
    char buffer[MAX_BUFFER_SIZE] = { 0, };
    char set1[MAX_BUFFER_SIZE + 2];
    char set2[MAX_BUFFER_SIZE + 2];
    size_t i = 0;
    size_t j;
    int k;
    size_t set1_size = 0;
    size_t set2_size = 0;
    char set2_char;
    error_code_t error;

    /* argument number validation */
    if (argc < 3 || argc > 4) {
        error = WRONG_ARGUMENTS_NUMBER;

        return error;
    }
    
    /* ignore case flag validation */
    if (argc == 4) {
        if (strcmp(argv[1], IGNORE_CASE_FLAG) != 0) {
            error = INVALID_FLAG;

            return error;
        }

        strcpy(set1, argv[2]);
        strcpy(set2, argv[3]);
    } else {
        strcpy(set1, argv[1]);
        strcpy(set2, argv[2]);
    }

    /* conversion escape character */
    if (try_conversion_escape_characters(set1) == FALSE || try_conversion_escape_characters(set2) == FALSE) {
        error = INVALID_FORMAT;

        return error;
    }

    /* conversion range character */
    if (try_conversion_range_characters(set1) == FALSE || try_conversion_range_characters(set2) == FALSE) {
        error = INVALID_RANGE;

        return error;
    }

    /* SET1, SET2 size validation */
    set1_size = strlen(set1);
    set2_size = strlen(set2);

    if (set1_size == 0 || set2_size == 0) {
        return 0;
    }

    if (set1_size + 1 > MAX_BUFFER_SIZE || set2_size + 1 > MAX_BUFFER_SIZE) {
        error = ARGUMENT_TOO_LONG;

        return error;
    }

    /* string replacement */
    while (fgets(buffer, sizeof(buffer), stdin)) {
        i = 0;
        while (buffer[i] != NULL_CHAR) {
            if (argc == 4) { 
                if ((int)buffer[i] > 64 && (int)buffer[i] < 91) {
                    buffer[i] = (char)((int)buffer[i] + 32);
                }
            }
            
            for (j = 0; j < set1_size; j++) {
                for (k = (int)set1_size - 1; k > (int)j; k--) {
                    if ((int)j != k && set1[j] == set1[k]) {
                        goto replacement_pass;
                    }
                }
                
                if (j > set2_size - 1) {
                    set2_char = set2[set2_size - 1];
                } else {
                    set2_char = set2[j];
                }
                
                if (buffer[i] == set1[j]) {
                    buffer[i] = set2_char;
                    break;
                }

replacement_pass:
                continue;
            }
            i++;
        }

        printf("%s", buffer);
    }

    return 0;
}

int try_conversion_escape_characters(char* set)
{
    const char allowed_escapes[10] = {'\\', 'a', 'b', 'f', 'n', 'r', 't', 'v', '\'', '"'};
    const char original_escapes[10] = {'\\', '\a', '\b', '\f', '\n', '\r', '\t', '\v', '\'', '\"'};
    const size_t ESCAPES_COUNT = 10;
    size_t i = 0;
    size_t set_index = 0;
    int is_ok = FALSE;

    while (set[set_index] != NULL_CHAR) {
        if (set[set_index] == '\\') {
            for (i = 0; i < ESCAPES_COUNT; i++) {
                if (set[set_index + 1] == allowed_escapes[i]) {
                    set[set_index] = original_escapes[i];

                    str_char_remove(set_index + 1, set);

                    is_ok = TRUE;
                    break;
                }
            }

            if (is_ok != TRUE) {
                return FALSE;
            }
        }

        set_index++;
    }

    return TRUE;
}

int try_conversion_range_characters(char* set) 
{
    size_t i = 0;
    int j;
    size_t set_index = 0;
    int temp_size = 0;
    size_t last_scope_index = -1;

    while (set[set_index] != NULL_CHAR) {    
        if (set[set_index] == '-' && set_index > 0 && set[set_index + 1] != NULL_CHAR) {
            if (last_scope_index == set_index - 1) {
                goto index_pass;
            }

            if ((int)set[set_index - 1] > (int)set[set_index + 1]) {
                return FALSE;
            }

            if (set[set_index - 1] != set[set_index + 1]) {
                str_char_remove(set_index, set);
                
                i = set_index;
                temp_size = (int)set[set_index];
                for (j = (int)set[set_index - 1] + 1; j < temp_size; j++) {
                    str_char_append(i, (char)j, set);
                    i++;
                }

                last_scope_index = i;

                set_index = i + 1;
            } else {
                str_char_remove(set_index, set);
                str_char_remove(set_index, set);

                last_scope_index = set_index - 1;
            }
        } else {
index_pass:
            set_index++;
        }
    }

    return TRUE;
}

void str_char_remove(size_t index, char* str) 
{
    while (str[index] != NULL_CHAR) {
        str[index] = str[index + 1];

        index++;
    }
}

void str_char_append(int index, char val, char* str) 
{
    int i = index;
    char temp_char1 = str[i];
    char temp_char2;

    while (str[i] != NULL_CHAR) {
        temp_char2 = temp_char1;
        temp_char1 = str[i + 1];
        str[i + 1] = temp_char2;

        i++;

        if (str[i] == NULL_CHAR) {
            str[i] = NULL_CHAR;
        }
    }

    str[index] = val;
}
