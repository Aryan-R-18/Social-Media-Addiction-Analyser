#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

static int nextId = 1;

User* create_user(int id, const char* name) {
    User *u = (User*)malloc(sizeof(User));
    if (!u) return NULL;
    u->id = id;
    strncpy(u->name, name, sizeof(u->name)-1);
    u->name[sizeof(u->name)-1] = '\0';
    u->usageHead = u->usageTail = NULL;
    u->next = NULL;
    if (id >= nextId) nextId = id + 1;
    return u;
}

void add_user(User **head, User *u) {
    if (!*head) {
        *head = u;
    } else {
        User *cur = *head;
        while (cur->next) cur = cur->next;
        cur->next = u;
    }
}

User* find_user(User *head, const char* name) {
    User *cur = head;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur;
        cur = cur->next;
    }
    return NULL;
}

void display_users(User *head) {
    User *cur = head;
    if (!cur) {
        printf("No users registered yet.\n");
        return;
    }
    printf("Registered users:\n");
    while (cur) {
        printf("ID: %d, Name: %s\n", cur->id, cur->name);
        cur = cur->next;
    }
}

void free_users(User *head) {
    User *cur = head;
    while (cur) {
        User *tmp = cur;
        cur = cur->next;
        // free usage list
        if (tmp->usageHead) {
            Usage *u = tmp->usageHead;
            while (u) {
                Usage *t = u;
                u = u->next;
                free(t);
            }
        }
        free(tmp);
    }
}
