#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) ((x) > (y) ? (x) : (y))

#define MIN(x, y) ((x) < (y) ? (x) : (y))

#define ABS(x) ((x) > 0 ? (x) : -(x))

#define RANGE(curr, min, max) for (curr = min; curr < (max) + 1; ++(curr))

#define RANGE_DESC(curr, max, min) for (curr = max; curr > (min) - 1; --(curr))

#define SET(ary, start, count, value) do { \
    int i = 0; \
    int j = start; \
    while (++i < (count) + 1) { \
        ary[j] = value; \
        ++j; \
    } \
} while (0)

#endif /* MACROS_H */
