#include <stdio.h>
#include "my_string.h"

enum {
    FAILED = -1,
    MAX_WORD_LENGTH = 50
};

void reverse_pointer(char* start, char* end)
{
    char* str_start = start;
    char* str_end = end;
    char temp;

    while (str_start < str_end) {
        temp = *str_start;
        *str_start = *str_end;
        *str_end = temp;

        ++str_start;
        --str_end;
    }
}

void reverse(char* str)
{
    char* str_end = str;

    if (str == NULL) {
        return;
    }

    while (*str_end != '\0') {
        ++str_end;
    }

    reverse_pointer(str, str_end - 1);
}

size_t _strlen(const char* s)
{
    const char* s_p = s;
    if (s == NULL || *s == '\0') {
        return 0;
    }

    while (*s_p != '\0') {
        ++s_p;
    }

    return (size_t)(s_p - s);
}

int index_of(const char* str, const char* word)
{
    int word_indexs[MAX_WORD_LENGTH] = { 0, };
    size_t str_len = _strlen(str);
    size_t word_len = _strlen(word);
    size_t i = 0;
    size_t j = 0;

    if (str == NULL) {
        return FAILED;
    }

    if (word == NULL || *word == '\0') {
        return 0;
    }

    for (i = 1; i < word_len; ++i) {
        if (word[i] == word[j]) {
            ++j;
            word_indexs[i] = j;

            continue;
        }

        if (i > 1 && j == 0) {
            word_indexs[i] = 0;
            continue;
        }

        if (i > 2) {
            j = word_indexs[j - 2];
        }
    }

    j = 0;
    for (i = 0; i < str_len; ++i) {
        while (j > 0 && str[i] != word[j]) {
            j = word_indexs[j - 1];
        }

        if (str[i] == word[j]) {
            if (j == word_len - 1) {
                return i - j;
            }

            ++j;
        }
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
    char* last_str_cut_point = NULL;

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
                if (last_str_cut_point == NULL) {
                    *str_p = '\0';

                    last_str_cut_point = str_p;

                    break;
                }

                if (str_p - last_str_cut_point > 1) {
                    goto loop_end;
                }

                last_str_cut_point = str_p;
                break;
            }

            ++delims_p;
        }

        ++str_p;
    }

loop_end:
    if (last_str_cut_point != NULL) {
        s_str = last_str_cut_point + 1;
    } else {
        s_str = NULL;
    }

    return token;
}

char* reverse_tokenize(char* str, const char* delims)
{
    char* token = tokenize(str, delims);

    reverse(token);

    return token;
}
