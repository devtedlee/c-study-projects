#ifndef TRANSLATE_H
#define TRANSLATE_H

#define TRUE (1)
#define FALSE (0)
#define MAX_BUFFER_SIZE (512)
#define IGNORE_CASE_FLAG ("-i")
#define NULL_CHAR ('\0')

typedef enum error_code {
    WRONG_ARGUMENTS_NUMBER = 1,
    INVALID_FLAG,
    INVALID_FORMAT,
    ARGUMENT_TOO_LONG,
    INVALID_RANGE
} error_code_t;

int translate(int argc, const char** argv);

void str_char_remove(size_t index, char* str);

void str_char_append(int index, char val, char* str);

int try_conversion_escape_characters(char* set);

int try_conversion_range_characters(char* set);

#endif /* TRANSLATE_H */
