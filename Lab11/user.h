#ifndef USER_H
#define USER_H

enum {
    STRING_LENGTH = 51,
};

typedef struct user {
    size_t id;
    char username[STRING_LENGTH];
    char email[STRING_LENGTH];
    char password[STRING_LENGTH];
} user_t;

#endif /* USER_H */
