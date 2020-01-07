#include <time.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "receipter.h"

#define MAX_ORDER_ITEM_COUNT (10)
#define MAX_PRICE (999.99)
#define MAX_MESSAGE_LENGTH (75)
#define NULL_CHAR ('\0')

static int s_order_number = 0;
char g_order_names[MAX_ORDER_ITEM_COUNT][26];
char (*g_order_names_p)[26] = g_order_names;
double g_order_prices[10] = { 0.0, };
double g_subtotal = 0;
double g_tip = 0;
char g_message[76];

int add_item(const char* name, double price) 
{
    size_t i;
    size_t j;
    size_t name_length;

    /* validate order item count - up to 10 */
    if (strlen(g_order_names[MAX_ORDER_ITEM_COUNT - 1]) > 0) { 
        return FALSE;
    }
    
    name_length = strlen(name);

    for (i = 0; i < MAX_ORDER_ITEM_COUNT; i++) {
        if (strlen(g_order_names[i]) == 0) {
            for (j = 0; j < name_length + 1; j++) {
                if (j == name_length || j > 24) {
                    g_order_names[i][j] = NULL_CHAR;
                    break;
                }

                g_order_names[i][j] = name[j];
            }

            g_order_prices[i] = price;
            g_subtotal += price;
            break;
        }
    }

    return TRUE;
}

void add_tip(double tip) 
{
    if (fabs(tip) > 0.0001 && tip <= MAX_PRICE) {
        g_tip = tip;
    }
}

void add_message(const char* message) 
{
    size_t i;

    for (i = 0; i < MAX_MESSAGE_LENGTH; i++) {
        g_message[i] = message[i];

        if (message[i] == NULL_CHAR) {
            break;
        }

        if (i == MAX_MESSAGE_LENGTH - 1) {
            g_message[MAX_MESSAGE_LENGTH] = NULL_CHAR;
        }
    }
}

int print_receipt(const char* filename, time_t timestamp) 
{
    const int MESSAGE_DIVIDE_LENGTH = 50;
    const int LEFT_BODY_SIZE = 33;
    const int RIGHT_BODY_SIZE = 17;
    const char divider[52] = "--------------------------------------------------\n";
    FILE* reciept;
    struct tm* time_p;
    char time_buffer[20];
    char temp_str[28];
    char* temp_str_p = temp_str;
    char body_left_buffer[40];
    char body_right_buffer[20];
    char temp_message_buffer[52];
    size_t i;
    double tax = 0;
    double total = 0;
    int message_length = 0;

    if (strlen(g_order_names[0]) == 0) {
        return FALSE;
    }

    reciept = fopen(filename, "w");

    /* header section */ 

    fprintf(reciept, "Charles' Seafood\n");
    fprintf(reciept, divider);

    sprintf(temp_str_p, "%05d", s_order_number++);

    time_p = gmtime(&timestamp);
    strftime(time_buffer, sizeof(time_buffer), "%Y-%m-%d %H:%M:%S", time_p);

    fprintf(reciept, "%s                          %s\n", time_buffer, temp_str_p);

    fprintf(reciept, divider);
    
    /* body section */ 

    for (i = 0; i < MAX_ORDER_ITEM_COUNT; i++) {
        temp_str_p = g_order_names[i];
        if (strlen(temp_str_p) != 0) {
            append_string_to_buffer(temp_str_p, strlen(temp_str_p), body_left_buffer, LEFT_BODY_SIZE);
            
            sprintf(temp_str_p, "%5.2f", g_order_prices[i]);
            append_string_to_buffer(temp_str_p, strlen(temp_str_p), body_right_buffer, RIGHT_BODY_SIZE);

            fprintf(reciept, "%s%s\n", body_left_buffer, body_right_buffer);
        } else {
            break;
        }
    }
    fprintf(reciept, "\n");
    
    append_string_to_buffer("Subtotal", 8, body_left_buffer, LEFT_BODY_SIZE);
    sprintf(temp_str, "%5.2f", g_subtotal);
    append_string_to_buffer(temp_str, strlen(temp_str), body_right_buffer, RIGHT_BODY_SIZE);

    fprintf(reciept, "%s%s\n", body_left_buffer, body_right_buffer);

    if (g_tip != 0.0) {
        append_string_to_buffer("Tip", 3, body_left_buffer, LEFT_BODY_SIZE);
        sprintf(temp_str, "%5.2f", g_tip);
        append_string_to_buffer(temp_str, strlen(temp_str), body_right_buffer, RIGHT_BODY_SIZE);

        fprintf(reciept, "%s%s\n", body_left_buffer, body_right_buffer);
    }

    append_string_to_buffer("Tax", 3, body_left_buffer, LEFT_BODY_SIZE);
    tax = g_subtotal * 0.05;
    sprintf(temp_str, "%5.2f", tax);
    append_string_to_buffer(temp_str, strlen(temp_str), body_right_buffer, RIGHT_BODY_SIZE);

    fprintf(reciept, "%s%s\n", body_left_buffer, body_right_buffer);

    append_string_to_buffer("Total", 5, body_left_buffer, LEFT_BODY_SIZE);
    total += g_subtotal;
    total += g_tip;
    total += tax;
    sprintf(temp_str, "%5.2f", total);
    append_string_to_buffer(temp_str, strlen(temp_str), body_right_buffer, RIGHT_BODY_SIZE);

    fprintf(reciept, "%s%s\n", body_left_buffer, body_right_buffer);

    fprintf(reciept, "\n");

    message_length = strlen(g_message);
    if (message_length != 0) {
        if (message_length > MESSAGE_DIVIDE_LENGTH) {
            strcpy(temp_message_buffer, g_message);
            temp_message_buffer[MESSAGE_DIVIDE_LENGTH] = NULL_CHAR;
            fprintf(reciept, "%s\n", temp_message_buffer);

            temp_str_p = &g_message[MESSAGE_DIVIDE_LENGTH];
            fprintf(reciept, "%s\n", temp_str_p);
        } else {
            fprintf(reciept, "%s\n", g_message);
        }
    }
    
    /* footer section */ 

    fprintf(reciept, "==================================================\n");
    fprintf(reciept, "                                        Tax#-51234");

    fclose(reciept);

    /* after print reciept must reset global variables */
    for (i = 0; i < MAX_ORDER_ITEM_COUNT; i++) {
        if (strlen(g_order_names[i]) != 0) {
            g_order_names[i][0] = NULL_CHAR;
            g_order_prices[i] = 0.0;
        }
    }

    g_subtotal = 0.0;
    if (g_tip != 0.0) {
        g_tip = 0.0;
    }

    if (message_length != 0) {
        g_message[0] = NULL_CHAR;
    }

    return TRUE;
}

void append_string_to_buffer(char* str, int str_size, char* buffer, int buffer_size)
{
    int i;
    int j;
    
    j = str_size;
    for (i = buffer_size; i > -1; i--) {
        if (j > -1) {
            buffer[i] = str[j];
            j--;
        } else {
            buffer[i] = ' ';
        }
    }
}
