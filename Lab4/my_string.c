#include "my_string.h"
#include <stdio.h>

static char* s_start_position = NULL;
static char* s_next_position = NULL;
static size_t ss_string_length = 0;

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
    size_t i;
    size_t s_string_length = 0;
    char temp;
 
    s_string_length = get_string_length(str);
    
    for ( i = 0; i < s_string_length / 2; i++) {
        temp = str[i];
        str[i] = str[s_string_length - 1 - i]; /* 문자열 마지막은 NULL이므로 NULL 이전문자부터 교환 시작 */
        str[s_string_length -1 -i] = temp;
    }
}
 
/* 문자열 조작, 두 문자열 비교 강의 영상 참조 */
int index_of(const char* str, const char* word)
{
    size_t i;
    size_t s_string_length = 0;
    size_t word_length = 0;
    size_t count = 0;
    size_t temp_i = 0;
 
    s_string_length = get_string_length(str);
    word_length = get_string_length(word);
 
    for (i = 0; i < s_string_length; i++) {
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
    char temp = '\0';
    size_t i;
    size_t s_string_length = 0;
    size_t length_count = 0; /* start_index + length_count로 last index를 구할 수 있다. */
    size_t start_index = 0;  /* 단어 위치변경 배열의 첫인덱스 */
    size_t last_index = 0;  /* 단어 위치변경 배열의 마지막인덱스 */
    
    s_string_length = get_string_length(str);
    
    for (i = 0; i <= s_string_length; i++) {
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
 
/* 문자열 토큰화 강의 참조 */
char* tokenize(char* str, const char* delims)
{
    char* temp = NULL;
    size_t i;
    
    if (ss_string_length == 0) {
        ss_string_length = get_string_length(str);
    } else {
        ss_string_length = get_string_length(s_next_position);
    }
 
    /* 순수 NULL이 들어오는 경우 */
    if (str == NULL && ss_string_length == 0) {
        return NULL;
    }
    /* 처음문자 토큰 반환 이후 처리 구문 */
    if (str == NULL && ss_string_length != 0) {
        s_start_position = s_next_position;
    } else if (str != NULL && ss_string_length != 0) {
        s_start_position = str; /* 첫 문자열이 들어오면 시작점을 문자열 처음으로 넣어준다. */
    }
    
    for (i = 0; i < ss_string_length; i++) {
        if (s_start_position[i] == *delims) {
            s_start_position[i] = '\0';
            s_next_position = s_start_position + i + 1; /* 배열의 인덱스 + null의 다음요소로 인해 + 1 */
            return s_start_position;
        }
        /* 마지막 문자열 탐색에서 모든 변수 초기화 */
        if (i == ss_string_length - 1) {
            temp = s_start_position;
            s_start_position = NULL;
            s_next_position = NULL;
            ss_string_length = 0;
            return temp;
        }
    }
 
    return NULL;
}
 
/* tokenize 함수과 str을 공유한다. */
char* reverse_tokenize(char* str, const char* delims)
{
    char* temp = NULL;
    size_t i;
    
    if (ss_string_length == 0) {
        ss_string_length = get_string_length(str);
    } else {
        ss_string_length = get_string_length(s_next_position);
    }
 
    /* 순수 NULL이 들어오는 경우 */
    if (str == NULL && ss_string_length == 0) {
        return NULL;
    }
    /* 처음문자 토큰 반환 이후 처리 구문 */
    if (str == NULL && ss_string_length != 0) {
        s_start_position = s_next_position;
    } else if (str != NULL && ss_string_length != 0) {
        s_start_position = str; /* 첫 문자열이 들어오면 시작점을 문자열 처음으로 넣어준다. */
    }
    
    for (i = 0; i < ss_string_length; i++) {
        if (s_start_position[i] == *delims) {
            s_start_position[i] = '\0';
            s_next_position = s_start_position + i + 1; /* 배열의 인덱스 + null의 다음요소로 인해 + 1 */
            return s_start_position;
        }
        /* 마지막 문자열 탐색에서 모든 변수 초기화 */
        if (i == ss_string_length - 1) {
            temp = s_start_position;
            s_start_position = NULL;
            s_next_position = NULL;
            ss_string_length = 0;
            return temp;
        }
    }
 
    return NULL;
}
