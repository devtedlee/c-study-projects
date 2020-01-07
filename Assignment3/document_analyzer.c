#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "document_analyzer.h"

#define SENTENCE_DELIMS (".!?")
#define WORD_DELIMS (" ,")

enum {
    PARAGRAPH_LENGTH = 1024
};

static char**** s_doc = NULL;
static size_t s_para_count = 0;
static node_t* s_sent_count_head = NULL;
static node_t* s_word_count_head = NULL;

int load_document(const char* document)
{
    FILE* doc_file = NULL;
    char paragraph_buffer[PARAGRAPH_LENGTH];
    char para_copy[PARAGRAPH_LENGTH];
    char* sentence_token = NULL;
    char* word_token = NULL;
    size_t para_count = 0;
    size_t sent_count = 0;
    size_t word_count = 0;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;
    size_t temp_str_len = 0;
    node_t* sent_node = NULL;
    node_t* word_node = NULL;
    int file_size;

    doc_file = fopen(document, "r");
    if (doc_file == NULL || doc_file == FALSE) {
        return FALSE;
    }

    if (fseek(doc_file, 0, SEEK_END) != 0) {
        return FALSE;
    }
    file_size = ftell(doc_file);

    fclose(doc_file);

    if (file_size < 1) {
        return TRUE;
    }

    doc_file = fopen(document, "r");

    while (fgets(paragraph_buffer, sizeof(paragraph_buffer), doc_file)) {
        if (strlen(paragraph_buffer) > 1) {
            para_count++;
        }
    }
    fclose(doc_file);

    doc_file = fopen(document, "r");

    s_doc = (char****)malloc(sizeof(char***) * para_count);
    s_para_count = para_count;

    s_sent_count_head = malloc(sizeof(node_t));
    s_sent_count_head->next = NULL;
    s_sent_count_head->val = 0;
    sent_node = s_sent_count_head;

    s_word_count_head = malloc(sizeof(node_t));
    s_word_count_head->next = NULL;
    s_word_count_head->val = 0;
    word_node = s_word_count_head;

    while (fgets(paragraph_buffer, sizeof(paragraph_buffer), doc_file)) {
        if (paragraph_buffer[0] == '\n') {
            continue;
        }

        temp_str_len = strlen(paragraph_buffer);

        if (paragraph_buffer[temp_str_len - 1] == '\n') {
            paragraph_buffer[temp_str_len - 1] = '\0';
        }

        sent_count = get_assignment_count(paragraph_buffer, SENTENCE_DELIMS);
        s_doc[i] = (char***)malloc(sizeof(char**) * (sent_count + 1));
        s_doc[i][sent_count] = NULL;

        add_node(&sent_node, sent_count);
        sent_node = sent_node->next;

        strcpy(para_copy, paragraph_buffer);
        sentence_token = strtok(para_copy, SENTENCE_DELIMS);

        j = 0;
        while (sentence_token != NULL) {
            if (sentence_token[0] == ' ') {
                sentence_token++;
            }

            word_count = get_assignment_count(sentence_token, WORD_DELIMS);
            ++word_count;

            add_node(&word_node, word_count);
            word_node = word_node->next;

            s_doc[i][j] = (char**)malloc(sizeof(char*) * (word_count + 1));
            s_doc[i][j][word_count] = NULL;

            word_token = strtok(sentence_token, WORD_DELIMS);

            k = 0;
            while (word_token != NULL) {
                if (strcmp(word_token, "\n") != 0) {
                    temp_str_len = strlen(word_token);
                    s_doc[i][j][k] = (char*)malloc(sizeof(char) * (temp_str_len + 1));
                    strncpy(s_doc[i][j][k], word_token, temp_str_len);
                    s_doc[i][j][k][temp_str_len] = '\0';
                }

                word_token = strtok(NULL, WORD_DELIMS);

                ++k;
            }

            strcpy(para_copy, paragraph_buffer);
            sentence_token = strtok(para_copy, SENTENCE_DELIMS);

            ++j;
            for (k = 0; k < j; k++) {
                sentence_token = strtok(NULL, SENTENCE_DELIMS);
            }
        }

        ++i;
    }

    fclose(doc_file);

    return TRUE;
}

void dispose(void)
{
    node_t* sent_node = NULL;
    node_t* word_node = NULL;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    if (s_para_count < 1 || s_sent_count_head == NULL || s_word_count_head == NULL) {
        return;
    }

    sent_node = s_sent_count_head->next;
    word_node = s_word_count_head->next;
    
    for (i = 0; i < s_para_count; i++) {
        for (j = 0; j < sent_node->val; j++) {
            for (k = 0; k < word_node->val; k++) {
                free(s_doc[i][j][k]);
            }

            free(s_doc[i][j]);
            word_node = word_node->next;
        }

        free(s_doc[i]);
        sent_node = sent_node->next;
    }

    free(s_doc);
    destroy_node(s_sent_count_head);
    destroy_node(s_word_count_head);
    s_para_count = 0;
    s_doc = NULL;
    s_sent_count_head = NULL;
    s_word_count_head = NULL;
}

size_t get_total_word_count(void)
{
    node_t* word_node = NULL;
    size_t count = 0;

    if (s_doc != NULL) {
        word_node = s_word_count_head->next;

        while (word_node->next != NULL) {
            count += word_node->val;
            word_node = word_node->next;
        }
        count += word_node->val;
    }

    return count;
}

size_t get_total_sentence_count(void)
{
    node_t* sent_node = NULL;
    size_t count = 0;

    if (s_doc != NULL) {
        sent_node = s_sent_count_head->next;
        while (sent_node->next != NULL) {
            count += sent_node->val;
            sent_node = sent_node->next;
        }
        count += sent_node->val;
    }

    return count;
}

size_t get_total_paragraph_count(void)
{
    size_t count = 0;

    if (s_doc != NULL) {
        count = s_para_count;
    }

    return count;
}

const char*** get_paragraph(const size_t paragraph_index)
{
    char*** result;

    if (s_doc == NULL || paragraph_index > s_para_count - 1) {
        return NULL;
    }

    result = s_doc[paragraph_index];
    return (const char***)result;
}

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index)
{
    size_t i = 0;
    node_t* sent_node = NULL;
    char** result;

    if (s_doc == NULL || paragraph_index > s_para_count - 1) {
        return NULL;
    }

    sent_node = s_sent_count_head->next;
    while (i < paragraph_index) {
        sent_node = sent_node->next;
        ++i;
    }

    if (sentence_index > sent_node->val - 1) {
        return NULL;
    }

    result = s_doc[paragraph_index][sentence_index];
    return (const char**)result;
}

size_t get_sentence_word_count(const char** sentence)
{
    size_t count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    while (*sentence != NULL) {
        ++count;
        ++sentence;
    }

    return count;
}

size_t get_paragraph_word_count(const char*** paragraph)
{
    size_t count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    while (*paragraph != NULL) {
        count += get_sentence_word_count(*paragraph);
        ++paragraph;
    }

    return count;
}

size_t get_paragraph_sentence_count(const char*** paragraph)
{
    size_t count = 0;

    if (s_doc == NULL) {
        return 0;
    }

    while (*paragraph != NULL) {
        ++count;
        ++paragraph;
    }

    return count;
}

int print_as_tree(const char* filename)
{
    FILE* file;
    node_t* sent_node;
    node_t* word_node;
    size_t i = 0;
    size_t j = 0;
    size_t k = 0;

    if (s_doc == NULL) {
        return 0;
    }

    sent_node = s_sent_count_head->next;
    word_node = s_word_count_head->next;

    file = fopen(filename, "w");

    for (i = 0; i < s_para_count; i++) {
        fprintf(file, "Paragraph %d:\n", i);
        for (j = 0; j < sent_node->val; j++) {
            fprintf(file, "    Sentence %d:\n", j);
            for (k = 0; k < word_node->val; k++) {
                fprintf(file, "        %s", s_doc[i][j][k]);

                if (i + 1 == s_para_count && j + 1 == sent_node->val && k + 1 == word_node->val) {
                    goto loop_end;
                }

                fprintf(file, "\n");
            }
            
            word_node = word_node->next;
        }

        sent_node = sent_node->next;
        fprintf(file, "\n");
    }

loop_end:
    fclose(file);

    return TRUE;
}

size_t get_assignment_count(const char* buffer, const char* delims)
{
    const char* temp_delims;
    size_t assignment_count = 0;
    size_t current_index = 0;
    size_t prev_delim_index;

    while (*buffer != '\0') {
        temp_delims = delims;
        while (*temp_delims != '\0') {
            if (*buffer == *temp_delims) {
                if (current_index != prev_delim_index + 1) {
                    ++assignment_count;
                }
                prev_delim_index = current_index;
                break;
            }

            ++temp_delims;
        }
        ++current_index;
        ++buffer;
    }
    return assignment_count;
}

void add_node(node_t** node, size_t val)
{
    node_t* new_node;
    node_t* current_node = *node;

    new_node = malloc(sizeof(node_t));
    new_node->next = NULL;
    new_node->val = val;
    current_node->next = new_node;
}

void destroy_node(node_t* head)
{
    node_t* p = head;

    while (p != NULL) {
        node_t* next = p->next;
        free(p);
        p = next;
    }
}
