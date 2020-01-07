#ifndef DOCUMENT_ANALYZER_H
#define DOCUMENT_ANALYZER_H

#define TRUE (1)
#define FALSE (0)

typedef struct node {
    size_t val;
    struct node* next;
} node_t;

int load_document(const char* document);

void dispose(void);

size_t get_total_word_count(void);

size_t get_total_sentence_count(void);

size_t get_total_paragraph_count(void);

const char*** get_paragraph(const size_t paragraph_index);

const char** get_sentence(const size_t paragraph_index, const size_t sentence_index);

size_t get_sentence_word_count(const char** sentence);

size_t get_paragraph_word_count(const char*** paragraph);

size_t get_paragraph_sentence_count(const char*** paragraph);

int print_as_tree(const char* filename);

size_t get_assignment_count(const char* buffer, const char* delims);

void add_node(node_t** node, size_t val);

void destroy_node(node_t* head);

#endif /* DOCUMENT_ANALYZER_H */
