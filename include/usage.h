#ifndef USAGE_H
#define USAGE_H

typedef struct Usage {
    char appName[64];
    int duration; // minutes
    char timeSlot[16]; // "Morning", "Afternoon", "Night"
    struct Usage *next;
} Usage;

Usage* create_usage(const char* app, int duration, const char* timeSlot);
void free_usage_list(Usage* head);

#endif
