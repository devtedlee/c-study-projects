#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "todo_list.h"

todo_list_t* init_todo_list_malloc(size_t max_size)
{
    todo_list_t* todo_list = (todo_list_t*)malloc(sizeof(todo_list_t));

    todo_list->max_size = max_size;
    todo_list->current_size = 0;
    todo_list->priority = -1;
    todo_list->task = NULL;
    todo_list->next = NULL;

    return todo_list;
}

void dispose(todo_list_t* todo_list)
{
    todo_list_t* temp_todo_list;

    while (todo_list != NULL) {
        temp_todo_list = todo_list->next;
        if (todo_list->task != NULL) {
            free(todo_list->task);
        }
        free(todo_list);
        todo_list = temp_todo_list;
    }
}

bool add_todo(todo_list_t* todo_list, const int32_t priority, const char* task)
{
    todo_list_t* todo_list_p = todo_list;
    todo_list_t* new_todo_list;
    size_t task_len = strlen(task);
    size_t todo_list_len = get_count(todo_list);

    if (todo_list_len >= todo_list->max_size) {
        return false;
    }

    todo_list->current_size = todo_list->current_size + 1;

    new_todo_list = (todo_list_t*)malloc(sizeof(todo_list_t));
    new_todo_list->max_size = todo_list_p->max_size;
    new_todo_list->next = NULL;
    new_todo_list->priority = priority;
    new_todo_list->task = (char*)malloc(sizeof(char) * (task_len + 1));
    strncpy(new_todo_list->task, task, task_len);
    new_todo_list->task[task_len] = '\0';
    
    if (todo_list_p->next == NULL) {
        todo_list_p->next = new_todo_list;

        return true;
    }

    todo_list_p = todo_list_p->next;

    if (todo_list_p->priority < priority) {
        new_todo_list->next = todo_list_p;
        todo_list->next = new_todo_list;

        return true;
    }

    while (todo_list_p->next != NULL) {
        if (todo_list_p->next->priority < priority) {
            break;
        }
        todo_list_p = todo_list_p->next;
    }

    if (todo_list_p->next != NULL) {
        new_todo_list->next = todo_list_p->next;
    }

    todo_list_p->next = new_todo_list;

    return true;
}

bool complete_todo(todo_list_t* todo_list)
{
    todo_list_t* todo_list_p = todo_list;

    if (todo_list_p->next == NULL) {
        return false;
    }

    todo_list->current_size = todo_list->current_size - 1;
    todo_list_p = todo_list_p->next;

    if (todo_list_p->next == NULL) {
        todo_list->next = NULL;
    } else {
        todo_list->next = todo_list_p->next;
    }

    free(todo_list_p->task);
    free(todo_list_p);
    
    return true;
}

const char* peek_or_null(todo_list_t* todo_list)
{
    todo_list_t* todo_list_p = todo_list;

    if (todo_list_p->next == NULL) {
        return NULL;
    }

    return (const char*)todo_list_p->next->task;
}

size_t get_count(todo_list_t* todo_list)
{
    return todo_list->current_size;
}

bool is_empty(todo_list_t* todo_list)
{
    todo_list_t* todo_list_p = todo_list;

    if (todo_list_p->next == NULL) {
        return true;
    }

    return false;
}
