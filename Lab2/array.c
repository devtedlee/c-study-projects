#include "array.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;

    for (i = 0; i < element_count; i++) {
        if (numbers[i] == num) {
            return i;
        }
    }

    return -1;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    int i;

    for (i = element_count - 1; i > -1 ; i--) {
        if (numbers[i] == num) {
            return i;
        }
    }

    return -1;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    int max_value = numbers[0];
    int result = -1;
    size_t i;

    for (i = 0; i < element_count; i++) {
        if (numbers[i] > max_value) {
            max_value = numbers[i];
            result = (int)i;
        }
    }

    return result;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int min_value = numbers[0];
    int result = -1;
    size_t i;

    for (i = 0; i < element_count; i++) {
        if (numbers[i] < min_value) {
            min_value = numbers[i];
            result = (int)i;
        }
    }

    return result;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i;

    if (element_count == 0) {
        return FALSE;
    }

    for (i = 0; i < element_count; i++) {
        if (numbers[i] < 0) {
            return FALSE;
        }
    }

    return TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i;

    for (i = 0; i < element_count; i++) {
        if (numbers[i] % 2 == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t i;
    int temp_value = numbers[pos];
    int next_value = num;

    if (pos > element_count) {
        return FALSE;
    }

    for (i = pos; i < element_count + 1; i++) {
        temp_value = numbers[i];
        numbers[i] = next_value;
        next_value = temp_value;
    }

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;

    if (element_count == 0 || index > element_count - 1) {
        return FALSE;
    }

    for (i = index; i < element_count; i++) {
        numbers[i] = numbers[i + 1];
    }

    return TRUE;
}
