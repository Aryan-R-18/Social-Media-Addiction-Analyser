#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "usage.h"

Usage* create_usage(const char* app, int duration, const char* timeSlot) {
    Usage *u = (Usage*)malloc(sizeof(Usage));
    if (!u) return NULL;
    strncpy(u->appName, app, sizeof(u->appName)-1);
    u->appName[sizeof(u->appName)-1] = '\0';
    u->duration = duration;
    strncpy(u->timeSlot, timeSlot, sizeof(u->timeSlot)-1);
    u->timeSlot[sizeof(u->timeSlot)-1] = '\0';
    u->next = NULL;
    return u;
}

void free_usage_list(Usage* head) {
    Usage *cur = head;
    while (cur) {
        Usage *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
}
