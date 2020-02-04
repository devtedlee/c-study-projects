#include <stdio.h>
#include "my_string.h"

enum {
    FAILED = -1
};

void reverse_pointer(char* start, char* end)
{
    char* str_start = start;
    char* str_end = end;
    char temp;

    while (str_start != str_end) {
        temp = *str_start;
        *str_start = *str_end;
        *str_end = temp;

        if (str_start + 1 == str_end) {
            break;
        }
        ++str_start;
        --str_end;
    }
}

void reverse(char* str)
{
    char* str_start = str;
    char* str_end = str;

    if (*str_start == '\0' || str_start == NULL) {
        return;
    }

    while (*str_end != '\0') {
        ++str_end;
    }
    str_end = *str_end == '\0' ? --str_end : str_end; 

    reverse_pointer(str_start, str_end);
}

int index_of(const char* str, const char* word)
{
    const char* str_p = str;
    const char* word_p = word;

    if (str_p == NULL) {
        return FAILED;
    }

    if (word_p == NULL || *word_p == '\0') {
        return 0;
    }

    while (*str_p != '\0') {
        const char* temp_str = str_p;

        while (*word_p != '\0') {
            if (*temp_str != *word_p) {
                break;
            }

            ++temp_str;
            ++word_p;

            if (*word_p == '\0') {
                return str_p - str;
            }

            if (*temp_str == '\0') {
                return FAILED;
            }
        }
        
        word_p = word;
        ++str_p;
    }

    return FAILED;
}

void reverse_by_words(char* str)
{
    char* str_p = str;
    char* start = str;
    char* end = str;

    if (str_p == NULL) {
        return;
    }

    while (*str_p != '\0') {
        if (*str_p == ' ') {
            end = str_p - 1;
            reverse_pointer(start, end);
            start = str_p + 1;
        }

        ++str_p;

        if (*str_p == '\0') {
            end = str_p - 1;
            reverse_pointer(start, end);
        }
    }
}

static char* s_str = NULL;

char* tokenize(char* str, const char* delims)
{
    char* token = str;
    char* str_p = str;
    const char* delims_p = delims;

    if (str == NULL) {
        if (s_str == NULL) {
            return NULL;
        }

        token = s_str;
        str_p = s_str;
    }

    while (*str_p != '\0') {
        delims_p = delims;

        while (*delims_p != '\0') {
            if (*str_p == *delims_p) {
                *str_p = '\0';
                
                ++str_p;
                goto find_chain_delim_str;
            }

            ++delims_p;
        }

        ++str_p;
    }

    return token;

find_chain_delim_str:

    while (*str_p != '\0') {
        int flag = 0;
        delims_p = delims;

        while (*delims_p != '\0') {
            if (*str_p == *delims_p) {
                flag = 1;

                break;
            }

            ++delims_p;
        }

        if (flag == 0) {
            break;
        }

        flag = 0;
        ++str_p;
    }

    s_str = str_p;
    return token;
}

char* reverse_tokenize(char* str, const char* delims)
{
    char* token = tokenize(str, delims);

    reverse(token);

    return token;
}
