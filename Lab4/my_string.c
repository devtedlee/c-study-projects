#include <stdio.h>
#include "my_string.h"
 
size_t get_str_length(const char* str)
{
    size_t count = 0;
    const char* p = str;
 
    while (*p++ != '\0') {
        ++count;
    }
    return count;
}
 
void reverse(char* str)
{
    size_t count = get_str_length(str);
    char* p = str;
    char* q = str + count - 1 ;
 
    while (p < q) {
        char temp = *p;
        *p = *q;
        *q = temp;
 
        ++p;
        --q;
    }
}
 
int index_of(const char* str, const char* word)
{
    const char* str_p = str;
    const char* word_p = word;
    size_t str_length = 0;
    size_t word_length = 0;
    size_t count = 0;
    
    if (str == NULL) {
        return -1;
    } else if (str != NULL) {
        str_length = get_str_length(str);
        word_length = get_str_length(word);
    } 

    if (*word == '\0') {
        return 0;
    }
 
    str_length = get_str_length(str);
    word_length = get_str_length(word);
 
    if(str_length < word_length) {
        return -1;
    } else {
        while (*str_p != '\0') {
            const char* temp_str = str_p;
            count = 0;
            word_p = word;
            while (*word_p != '\0') {
                if (*word_p != *temp_str) {
                    break;
                }

                word_p += 1;
                count += 1;

                if (*word_p == '\0') {
                    printf("%dcheck\n", word_length);
                    return ((temp_str - str)) - word_length + 1;
                }

                ++temp_str;
            }

            str_p += 1;
        }

        return -1;
    }
}
 
void reverse_by_words(char* str)
{
    size_t count = get_str_length(str);
    size_t i = 0;
    char* p = str;
    char* q = str;
 
    for (i = 0; i <= count; i++) {
        if (*(str + i) == ' ' || *(str + i) == '\0') {
            q = str + i - 1;
            while (p < q) {
                char temp = *p;
                *p = *q;
                *q = temp;
                ++p;
                --q;
            }
            p = str + i + 1;
        }
    }
}
 
char* tokenize(char* str, const char* delims)
{
    static char* s_str = NULL;
    size_t str_length = 0;
    size_t delims_lenght = 0;
    size_t toggle = 0;
    size_t i = 0;
    size_t j = 0;
 
    if (str != NULL) {
        s_str = str;
    } else if (str == NULL) {
        str = s_str;
        if(str == NULL) {
            goto return_str;
        }
    }
 
    str_length = get_str_length(str);
    delims_lenght = get_str_length(delims);
 
    for (i = 0; i < str_length; i++) {
        for (j = 0; j <= delims_lenght; j++) {
            if (*(str + i) == *(delims + j)) {
                toggle = 1;
                *(str + i) = '\0';
                s_str = str + i + 1;
                break;                
            } else if (toggle == 1 && *(delims + j) == '\0') {
                toggle = 0;
                goto return_str;
            }
        }
    }
 
    return_str:
        return str;
}
 
char* reverse_tokenize(char* str, const char* delims)
{
    char* init_token_p = tokenize(str, delims);
    reverse(init_token_p);
    return init_token_p;
}
