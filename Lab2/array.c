#include "array.h"
#include "limits.h"

int get_index_of(const int numbers[], const size_t element_count, const int num)
{
    size_t i;
    
    for (i = 0; i < element_count; ++i) {
        if (numbers[i] == num) {
            return i;
        }
    }

    return FAILED;
}

int get_last_index_of(const int numbers[], const size_t element_count, const int num)
{
    int i;
    
    for (i = (int)(element_count - 1); i > -1; --i) {
        if (numbers[i] == num) {
            return i;
        }
    }

    return FAILED;
}

int get_max_index(const int numbers[], const size_t element_count)
{
    int max = INT_MIN;
    size_t max_index = 0;
    size_t i;

    if (element_count == 0) {
        return FAILED;
    }

    for (i = 0; i < element_count; ++i) {
        int num = numbers[i];
        if (num > max) {
            max = num;
            max_index = i;
        }
    }

    return (int)max_index;
}

int get_min_index(const int numbers[], const size_t element_count)
{
    int min = INT_MAX;
    size_t min_index = 0;
    size_t i;

    if (element_count == 0) {
        return FAILED;
    }

    for (i = 0; i < element_count; ++i) {
        int num = numbers[i];
        if (num < min) {
            min = num;
            min_index = i;
        }
    }

    return (int)min_index;
}

int is_all_positive(const int numbers[], const size_t element_count)
{
    size_t i;

    if (element_count == 0) {
        return FAILED;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] < 0) {
            return FALSE;
        }
    }

    return TRUE;
}

int has_even(const int numbers[], const size_t element_count)
{
    size_t i;

    if (element_count == 0) {
        return FAILED;
    }

    for (i = 0; i < element_count; ++i) {
        if (numbers[i] % 2 == 0) {
            return TRUE;
        }
    }

    return FALSE;
}

int insert(int numbers[], const size_t element_count, const int num, const size_t pos)
{
    size_t i;

    if (pos > element_count || element_count == 0) {
        return FALSE;
    }

    for (i = element_count; i > pos; --i) {
        numbers[i] = numbers[i - 1];
    }

    numbers[pos] = num;

    return TRUE;
}

int remove_at(int numbers[], const size_t element_count, const size_t index)
{
    size_t i;

    if (index >= element_count || element_count == 0) {
        return FALSE;
    }

    for (i = index; i < element_count; ++i) {
        numbers[i] = numbers[i + 1];
    }

    return TRUE;
}
