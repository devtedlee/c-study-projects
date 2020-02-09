#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "receipter.h"

#define MAX_PRICE (999.99)

enum {
    MAX_ITEM_COUNT = 10,
    NAME_MAX_LENGTH = 25,
    MESSAGE_MAX_LENGTH = 75,
    MAX_ORDER_COUNT = 99999
};

static size_t s_order_number = 0;

char g_item_names[MAX_ITEM_COUNT][NAME_MAX_LENGTH + 1];
double g_item_prices[MAX_ITEM_COUNT];
size_t g_item_count = 0;

double g_tip = 0.0;
char g_message[MESSAGE_MAX_LENGTH + 1];

int add_item(const char* name, double price)
{
    char* item_name;
    size_t name_len;
    if (g_item_count >= MAX_ITEM_COUNT || price > MAX_PRICE) {
        return FALSE;
    }

    if (name == NULL || *name == '\0') {
        return FALSE;
    }

    name_len = strlen(name);
    if (name_len >= NAME_MAX_LENGTH) {
        name_len = NAME_MAX_LENGTH;
    }

    item_name = g_item_names[g_item_count];
    memset(item_name, 0, NAME_MAX_LENGTH + 1);

    strncpy(item_name, name, name_len + 1);
    item_name[name_len] = '\0';

    g_item_prices[g_item_count] = price;

    ++g_item_count;

    return TRUE;
}

void add_tip(double tip)
{
    if (tip > MAX_PRICE) {
        return;
    }

    g_tip = tip;
}

void add_message(const char* message)
{
    size_t message_len = strlen(message);

    if (message_len >= MESSAGE_MAX_LENGTH) {
        message_len = MESSAGE_MAX_LENGTH;
    }

    memset(g_message, 0, MESSAGE_MAX_LENGTH + 1);

    if (*message == '\0' || NULL) {
        return;
    }

    strncpy(g_message, message, message_len + 1);
    g_message[message_len] = '\0';
}

void print_to_file(FILE* f, const char* s, const size_t blank_size)
{
    size_t i;
    for (i = 0; i < blank_size; ++i) {
        fprintf(f, " ");
    }
    fprintf(f, "%s", s);
}

int print_receipt(const char* filename, time_t timestamp)
{
    FILE* file;
    struct tm* time_p;
    char time_buffer[20];
    const size_t LEFT_BUFFER_SIZE = 33;
    const size_t RIGHT_BUFFER_SIZE = 18;
    const size_t MESSAGE_DIVIDE_LENGTH = 50;
    char price_str[7];
    char* price_str_p = price_str;
    double tax = 0.0;
    double subtotal = 0.0;
    double total = 0.0;
    size_t i;
    size_t index;
    size_t temp_len;

    if (filename == NULL || g_item_count == 0) {
        return FALSE;
    }

    file = fopen(filename, "w");

    time_p = gmtime(&timestamp);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_p);

    fprintf(file, "Charles' Seafood\n--------------------------------------------------\n");
    fprintf(file, "%s                          %05d\n--------------------------------------------------\n", time_buffer, s_order_number++);

    for (i = 0; i < g_item_count; ++i) {
        temp_len = strlen(g_item_names[i]);
        
        print_to_file(file, g_item_names[i], LEFT_BUFFER_SIZE - temp_len);
        sprintf(price_str_p, "%5.2f\n", g_item_prices[i]);
        temp_len = strlen(price_str_p);

        print_to_file(file, price_str_p, RIGHT_BUFFER_SIZE - temp_len);

        subtotal += g_item_prices[i];
    }
    fprintf(file, "\n");

    fprintf(file, "                         Subtotal");
    sprintf(price_str_p, "%5.2f\n", subtotal);
    temp_len = strlen(price_str_p);
    print_to_file(file, price_str_p, RIGHT_BUFFER_SIZE - temp_len);

    if (g_tip != 0.0) {
        sprintf(price_str_p, "%5.2f\n", g_tip);
        temp_len = strlen(price_str_p);
        fprintf(file, "                              Tip");
        print_to_file(file, price_str_p, RIGHT_BUFFER_SIZE - temp_len);
    }

    tax = subtotal * 0.05;
    sprintf(price_str_p, "%5.2f\n", tax);
    temp_len = strlen(price_str_p);

    fprintf(file, "                              Tax");
    print_to_file(file, price_str_p, RIGHT_BUFFER_SIZE - temp_len);

    total += subtotal;
    total += g_tip;
    total += tax;
    sprintf(price_str_p, "%5.2f\n", total);
    temp_len = strlen(price_str_p);

    fprintf(file, "                            Total");
    print_to_file(file, price_str_p, RIGHT_BUFFER_SIZE - temp_len);

    fprintf(file, "\n");

    temp_len = strlen(g_message);
    if (temp_len != 0) {
        char temp_message_buffer[52];
        char* temp_message_p;
        if (temp_len > MESSAGE_DIVIDE_LENGTH) {
            strcpy(temp_message_buffer, g_message);
            temp_message_buffer[MESSAGE_DIVIDE_LENGTH] = '\0';
            fprintf(file, "%s\n", temp_message_buffer);

            temp_message_p = &g_message[MESSAGE_DIVIDE_LENGTH];
            fprintf(file, "%s\n", temp_message_p);
        } else {
            fprintf(file, "%s\n", g_message);
        }

        g_message[0] = '\0';
    }
    
    /* footer section */ 

    fprintf(file, "==================================================\n                                        Tax#-51234");

    fclose(file);

    /* after print reciept must reset global variables */
    for (i = 0; i < g_item_count; i++) {
        if (strlen(g_item_names[i]) != 0) {
            g_item_names[i][0] = '\0';
            g_item_prices[i] = 0.0;
        }
    }

    g_item_count = 0;

    if (g_tip != 0.0) {
        g_tip = 0.0;
    }

    return TRUE;
}
