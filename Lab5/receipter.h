#include <time.h>

#ifndef RECEIPTER_H
#define RECEIPTER_H

#define TRUE (1)
#define FALSE (0)

int add_item(const char* name, double price);

void add_tip(double tip);

void add_message(const char* message);

int print_receipt(const char* filename, time_t timestamp);

void print_to_file(FILE* f, const char* s, const size_t blank_size);

#endif /* RECEIPTER_H */
