#include <stddef.h>
#include "my_string.h"
 
static char* s_buffer = NULL;

size_t get_string_length(const char* str)
{
    const char* p = str;
    size_t count = 0;
    
    if (str == NULL) {
        return 0;
    }
    while (*p++ != '\0') {
        count++;
    }
    
    return count;
}

void reverse(char* str)
{
    char* end = str - 2;
 
    while (*(++end + 1) != '\0') {
    }
 
    while (str < end) {
        *str = *str ^ *end;
        *end = *str ^ *end;
        *str = *str ^ *end;
        str++;
        end--;
    }
}
 
int index_of(const char* str, const char* word)
{
    size_t i;
    size_t string_length = 0;
    size_t word_length = 0;
    size_t count = 0;
    size_t temp_i = 0;
 
    string_length = get_string_length(str);
    word_length = get_string_length(word);
 
    for (i = 0; i < string_length; i++) {
        while (str[i] != '\0' && str[i] == *word) { /* and 조건 때문에 NULL 문자를 만나면 거짓조건으로 탈출한다. and 조건으로 배열의 범위를 넘어서 접근하지 않는다. */
            word++;
            count++;
            temp_i = i;
        }
    }
    
    return word_length == count ? (int)(temp_i - word_length + 1) : -1;
}
 
void reverse_by_words(char* str)
{
    char* end;
 
    while (TRUE) {
        end = str;
        while (*end != ' ' && *end != '\0') {
            end++;
        }
        end--;
        while (str < end) {
            *str = *str ^ *end;
            *end = *str ^ *end;
            *str = *str ^ *end;
            str++;
            end--;
        }
        while (TRUE) {
            if (*str == '\0') {
                return;
            }
            if (*str == ' ') {
                str++;
                break;
            }
            str++;
        }
    }
}
 
char* tokenize(char* str, const char* delims)
{
    const char* delims_ptr;
    char* buffer_ptr;
    char* token_ptr;
 
    if (str != NULL) {
        s_buffer = str;
    }
 
    if (s_buffer == NULL || *s_buffer == '\0') {
        return NULL;
    }
 
    buffer_ptr = s_buffer;
 
    while (TRUE) {
        if (*buffer_ptr == '\0') {
            s_buffer = NULL;
            return NULL;
        }
 
        delims_ptr = delims;
        while (*delims_ptr != '\0') {
            if (*delims_ptr == *buffer_ptr) {
                break;
            }
            delims_ptr++;
        }
 
        if (*delims_ptr == '\0') {
            break;
        }
 
        buffer_ptr++;
    }
 
    token_ptr = buffer_ptr;
 
    while (TRUE) {
        if (*buffer_ptr == '\0') {
            s_buffer = NULL;
            return token_ptr;
        }
 
        delims_ptr = delims;
        while (*delims_ptr != '\0') {
            if (*delims_ptr == *buffer_ptr) {
                break;
            }
            delims_ptr++;
        }
 
        if (*delims_ptr != '\0') {
            break;
        }
 
        buffer_ptr++;
    }
 
    *buffer_ptr = '\0';
 
    s_buffer = buffer_ptr + 1;
    return token_ptr;
}
 
char* reverse_tokenize(char* str, const char* delims)
{
    char* token = tokenize(str, delims);
 
    if (token == NULL) {
        return NULL;
    }
 
    reverse(token);
 
    return token;
}
