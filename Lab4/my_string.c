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
    char temp = '\0';
    size_t i;
    size_t string_length = 0;
    size_t length_count = 0; /* start_index + length_count로 last index를 구할 수 있다. */
    size_t start_index = 0;  /* 단어 위치변경 배열의 첫인덱스 */
    size_t last_index = 0;  /* 단어 위치변경 배열의 마지막인덱스 */
    
    string_length = get_string_length(str);
    
    for (i = 0; i <= string_length; i++) {
        length_count++;
        if (str[i] == ' ' || str[i] == '\0') { /* 공백기준으로 탐색을 진행하고, 마지막문자는 공백이 아닌 NULL을 가기 때문에 */
            start_index = (i + 1) - length_count; /* i가 멈춘 위치 - 길이 + 1 = 시작위치 */
            last_index = start_index + length_count - 2; /* 공백위치 빼고, 배열인덱스 빼고 = -2 */
            while (start_index < last_index) { /* arr[1] arr[2] arr[3] arr[4]  1,4랑바꾸고 2,3이랑 바꾸면 된다. */
                temp = str[start_index];
                str[start_index++] = str[last_index];
                str[last_index--] = temp;
            }
            length_count = 0; /* 초기화 */
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
