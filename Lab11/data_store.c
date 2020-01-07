#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "data_store.h"

#define LOG_FILE_NAME ("log.txt")

user_t* get_user_by_id_or_null(user_t** users, size_t id)
{
    size_t i = 0;

    if (users == NULL) {
        return NULL;
    }

    while (users[i] != NULL) {
        if (users[i]->id == id) {
            break;
        }

        ++i;
    }

    if (users[i] == NULL) {
        return NULL;
    }

    return users[i];
}

user_t* get_user_by_username_or_null(user_t** users, const char* username)
{
    size_t i = 0;

    if (users == NULL) {
        return NULL;
    }

    while (users[i] != NULL) {
        if (strcmp(users[i]->username, username) == 0) {
            break;
        }

        ++i;
    }

    if (users[i] == NULL) {
        return NULL;
    }

    return users[i];
}

bool update_email(user_t** users, size_t id, const char* email)
{
    user_t* user = get_user_by_id_or_null(users, id);
    FILE* log_file;
    char old_email[STRING_LENGTH];
    char new_email[STRING_LENGTH];
    size_t email_len = 0;

    if (user == NULL) {
        return false;
    }

    email_len = strlen(user->email);
    strncpy(old_email, user->email, email_len + 1);
    old_email[email_len] = '\0';

    email_len = strlen(email);
    strncpy(new_email, email, email_len + 1);
    new_email[email_len] = '\0';

    strncpy(user->email, email, email_len + 1);
    user->email[email_len] = '\0';

#if defined(RELEASE)
    str_redact(old_email, true);
    str_redact(new_email, true);
#endif

    log_file = fopen(LOG_FILE_NAME, "a");
    fprintf(log_file, "TRACE: User %d updated email from \"%s\" to \"%s\"\n", user->id, old_email, new_email);
    fclose(log_file);

    return true;
}

bool update_password(user_t** users, size_t id, const char* password)
{
    user_t* user = get_user_by_id_or_null(users, id);
    FILE* log_file;
    char old_password[STRING_LENGTH];
    char new_password[STRING_LENGTH];
    size_t password_len;

    if (user == NULL) {
        return false;
    }

    password_len = strlen(user->password);
    strncpy(old_password, user->password, password_len + 1);
    old_password[password_len] = '\0';

    password_len = strlen(password);
    strncpy(new_password, password, password_len + 1);
    new_password[password_len] = '\0';

    strncpy(user->password, password, password_len + 1);
    user->password[password_len] = '\0';

#if defined(RELEASE)
    str_redact(old_password, false);
    str_redact(new_password, false);
#endif

    log_file = fopen(LOG_FILE_NAME, "a");
    fprintf(log_file, "TRACE: User %d updated password from \"%s\" to \"%s\"\n", user->id, old_password, new_password);
    fclose(log_file);

    return true;
}

#if defined(RELEASE)

void str_redact(char* str, bool is_email)
{
    size_t at_sign_index = 0;
    size_t str_len = strlen(str);
    char* str_copy = str;
    size_t i = 0;

    if (is_email) {
        while (*str_copy != '@' && *str_copy != '\0') {
            ++at_sign_index;
            ++str_copy;
        }

        str_len = at_sign_index;
    }

    if (str_len == 0) {
        return;
    } else if (str_len == 1) {
        str[0] = '*';
    } else if (str_len == 2) {
        str[1] = '*';
    } else {
        for (i = 1; i < str_len - 1; ++i) {
            str[i] = '*';
        }
    }
}

#endif
