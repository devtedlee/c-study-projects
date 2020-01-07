#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tokenize.h"

char** tokenize_malloc(const char* str, const char* delim)
{
    char** result;
    char* token;
    char* str_malloc;
    char* str_copy;
    char* delim_copy;
    size_t temp_str_len = 0;
    size_t token_count = 0;

    if (str == NULL || strlen(str) < 1) {
        result = (char**)malloc(sizeof(char*) * 1);
        result[0] = (char*)malloc(sizeof(char) * 1);
        result[0] = NULL;
        return result;
    }

    temp_str_len = strlen(str);
    str_malloc = (char*)malloc(sizeof(char) * (temp_str_len + 1));
    str_copy = str_malloc;
    strncpy(str_copy, str, temp_str_len);
    str_copy[temp_str_len] = '\0';

    if (delim == NULL || strlen(delim) < 1) {
        result = (char**)malloc(sizeof(char*) * 2);
        result[0] = (char*)malloc(sizeof(char) * (temp_str_len + 1));
        strncpy(result[0], str_copy, temp_str_len);
        result[0][temp_str_len] = '\0';
        result[1] = NULL;

        return result;
    }

    token = str_copy;

    result = (char**)malloc(sizeof(char*) * strlen(str_copy));
    
    while (*str_copy != '\0') {
        delim_copy = (char*)delim;
        while (*delim_copy != '\0') {
            if (*str_copy == *delim_copy) {
                *str_copy = '\0';
                temp_str_len = strlen(token);
                if (temp_str_len < 1U) {
                    token = str_copy + 1;
                    break;
                }
                
                result[token_count] = (char*)malloc(sizeof(char) * (temp_str_len + 1));
                strncpy(result[token_count], token, temp_str_len);
                result[token_count][temp_str_len] = '\0';
                ++token_count;
                token = str_copy + 1;
                break;
            }
            ++delim_copy;
        }
        ++str_copy;

        if (*str_copy == '\0' && strlen(token) > 0) {
            temp_str_len = strlen(token);
            result[token_count] = (char*)malloc(sizeof(char) * (temp_str_len + 1));
            strncpy(result[token_count], token, temp_str_len);
            result[token_count][temp_str_len] = '\0';
            ++token_count;
        }
    }

    free(str_malloc);

    result[token_count] = NULL;
    result = realloc(result, sizeof(char*) * (token_count + 1));

    return result;
}
