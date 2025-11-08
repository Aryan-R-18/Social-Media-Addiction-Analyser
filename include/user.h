#ifndef USER_H
#define USER_H

#include "usage.h"

typedef struct User {
    int id;
    char name[64];
    Usage *usageHead;
    Usage *usageTail;
    struct User *next;
} User;

/* user list operations */
User* create_user(int id, const char* name);
void add_user(User **head, User *u);
User* find_user(User *head, const char* name);
void display_users(User *head);
void free_users(User *head);

#endif
