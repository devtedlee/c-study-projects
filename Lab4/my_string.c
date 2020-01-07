#include <stdio.h>
#include "my_string.h"

static char* s_current_token;

void reverse(char* str)
{
    size_t i = 0;
    size_t j;
    char temp_char;

    while (str[i] != NULL_CHAR) {
        i++;
    }

    if (i < 2) {
        return;
    }
    
    j = i - 1;
    i = 0;
    
    while (i < j) {
        temp_char = str[i];
        str[i] = str[j];
        str[j] = temp_char;

        i++;
        j--;
    }
}

int index_of(const char* str, const char* word)
{
    size_t i = 0;
    size_t j;
    size_t k;
    size_t word_length;

    while (word[i] != NULL_CHAR) {
        i++;
    }

    if (i < 1) {
        return 0;
    }

    word_length = i;
    i = 0;

    while (str[i] != NULL_CHAR) {
        k = 0;
        if (str[i] == word[k]) {
            j = i;
            while (k < word_length) {
                if (str[j] == NULL_CHAR) {
                    goto loop_end;
                }

                if (str[j] != word[k]) {
                    break;
                }

                j++;
                k++;
            }

            if (k >= word_length) {
                return i;
            }
        }

        i++;
    }

loop_end:
    return -1;
}

void reverse_by_words(char* str)
{
    const char SPACE = ' ';
    size_t i = 0;
    size_t j;
    size_t k;
    char temp_char;
    size_t word_end;

    while (str[i] != NULL_CHAR) {
        j = i;

        while (str[j] != SPACE && str[j] != NULL_CHAR) {
            j++;
        }
        
        word_end = j;
        k = word_end - 1;
        j = i;

        while (j < k) {
            temp_char = str[j];
            str[j] = str[k];
            str[k] = temp_char;

            j++;
            k--;
        }
        

        if (str[word_end] == NULL_CHAR) {
            break;
        }

        i = word_end + 1;
    }
}

char* tokenize(char* str, const char* delims)
{
    char* token_start;
    char* temp_pointer;
    size_t i;
    size_t delim_flag;

    if (str == NULL) {
        if (s_current_token == NULL) {
            return NULL;
        }

        str = s_current_token;
    }

    token_start = str;

    while (*str != NULL_CHAR) {
        for (i = 0; delims[i] != NULL_CHAR; i++) {
            if (*str == delims[i]) {
                temp_pointer = str + 1;
                *str = NULL_CHAR;
                str = temp_pointer;

                goto get_token_loop_exit;
            }
        }

        str++;
    }

    s_current_token = NULL;
    return token_start;

get_token_loop_exit:

    while (*str != NULL_CHAR) {
        delim_flag = 0;
        for (i = 0; delims[i] != NULL_CHAR; i++) {
            if (*str == delims[i]) {
                delim_flag++;
            }
        }

        if (delim_flag == 0) {
            s_current_token = str;
            break;
        }

        str++;
    }

    if (*str == NULL_CHAR) {
        s_current_token = NULL;
    }

    return token_start;
}

char* reverse_tokenize(char* str, const char* delims)
{
    char* token_start;
    char* temp_pointer;
    char temp_char;
    size_t i;
    size_t j = 0;
    size_t k = 0;

    if (str == NULL) {
        if (s_current_token == NULL) {
            return NULL;
        }

        str = s_current_token;
    }

    token_start = str;

    while (*str != NULL_CHAR) {
        for (i = 0; delims[i] != NULL_CHAR; i++) {
            if (*str == delims[i]) {
                k--;
                while (j < k) {
                    temp_char = token_start[j];
                    token_start[j] = token_start[k];
                    token_start[k] = temp_char;

                    j++;
                    k--;
                }

                temp_pointer = str + 1;
                *str = NULL_CHAR;
                str = temp_pointer;

                goto get_token_loop_exit;
            }
        }

        str++;
        k++;

        if (*str == NULL_CHAR) {
            k--;
            while (j < k) {
                temp_char = token_start[j];
                token_start[j] = token_start[k];
                token_start[k] = temp_char;

                j++;
                k--;
            }
        }
    }

    s_current_token = NULL;
    return token_start;

get_token_loop_exit:

    while (*str != NULL_CHAR) {
        j = 0;
        for (i = 0; delims[i] != NULL_CHAR; i++) {
            if (*str == delims[i]) {
                j++;
            }
        }

        if (j == 0) {
            s_current_token = str;
            break;
        }

        str++;
    }

    if (*str == NULL_CHAR) {
        s_current_token = NULL;
    }
    
    return token_start;
}
