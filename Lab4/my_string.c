#include <stddef.h>
#include "my_string.h"
 
char* g_start_position = NULL;
char* g_next_position = NULL;
size_t g_string_length = 0;

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
    const char* str_start = str;
    const char* str_ptr;
    const char* word_ptr;
 
    if (*word == '\0') {
        return 0;
    }
 
    while (*str != '\0') {
        str_ptr = str;
        word_ptr = word;
        while (*str_ptr++ == *word_ptr++) {
            if (*word_ptr == '\0') {
                return str - str_start;
            }
            if (*str_ptr == '\0') {
                return -1;
            }
        }
        str++;
    }
 
    return -1;
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
    char* temp = NULL;
    size_t i;
    
    if (g_string_length == 0) {
        g_string_length = get_string_length(str);
    } else {
        g_string_length = get_string_length(g_next_position);
    }
 
    /* 순수 NULL이 들어오는 경우 */
    if (str == NULL && g_string_length == 0) {
        return NULL;
    }
    /* 처음문자 토큰 반환 이후 처리 구문 */
    if (str == NULL && g_string_length != 0) {
        g_start_position = g_next_position;
    } else if (str != NULL && g_string_length != 0) {
        g_start_position = str; /* 첫 문자열이 들어오면 시작점을 문자열 처음으로 넣어준다. */
    }
    
    for (i = 0; i < g_string_length; i++) {
        if (g_start_position[i] == *delims) {
            g_start_position[i] = '\0';
            g_next_position = g_start_position + i + 1; /* 배열의 인덱스 + null의 다음요소로 인해 + 1 */
            return g_start_position;
        }
        /* 마지막 문자열 탐색에서 모든 변수 초기화 */
        if (i == g_string_length - 1) {
            temp = g_start_position;
            g_start_position = NULL;
            g_next_position = NULL;
            g_string_length = 0;
            return temp;
        }
    }
 
    return NULL;
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
