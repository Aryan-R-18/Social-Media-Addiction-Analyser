#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "file_handler.h"
#include "analysis.h"   // for AnalysisResult structure

// -----------------------------------------------------------------------------
// Ensure "data" and "data/reports" directories exist
// -----------------------------------------------------------------------------
static void ensure_dirs() {
    struct stat st = {0};

    // Create 'data' folder if missing
    if (stat("data", &st) == -1) {
        mkdir("data", 0700);
    }

    // Create 'data/reports' folder inside 'data'
    if (stat("data/reports", &st) == -1) {
        mkdir("data/reports", 0700);
    }
}

// -----------------------------------------------------------------------------
// Save individual user's usage into data/usage_<username>.txt
// -----------------------------------------------------------------------------
void save_user_usage_to_file(User *u) {
    if (!u) return;
    ensure_dirs();

    char filename[128];
    snprintf(filename, sizeof(filename), "data/usage_%s.txt", u->name);

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Error creating user usage file");
        return;
    }

    Usage *cur = u->usageHead;
    while (cur) {
        fprintf(f, "%s,%d,%s\n", cur->appName, cur->duration, cur->timeSlot);
        cur = cur->next;
    }

    fclose(f);
}

// -----------------------------------------------------------------------------
// Load individual user's usage data from file
// -----------------------------------------------------------------------------
void load_user_usage_from_file(User *u) {
    if (!u) return;

    char filename[128];
    snprintf(filename, sizeof(filename), "data/usage_%s.txt", u->name);

    FILE *f = fopen(filename, "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        // format: app,duration,timeSlot
        char *app = strtok(line, ",\n");
        char *durS = strtok(NULL, ",\n");
        char *timeSlot = strtok(NULL, ",\n");

        if (!app || !durS || !timeSlot) continue;

        int dur = atoi(durS);
        if (dur <= 0) continue;  // skip invalid duration

        Usage *nu = create_usage(app, dur, timeSlot);
        if (!u->usageHead) {
            u->usageHead = u->usageTail = nu;
        } else {
            u->usageTail->next = nu;
            u->usageTail = nu;
        }
    }

    fclose(f);
}

// -----------------------------------------------------------------------------
// Save all users and their usage data
// -----------------------------------------------------------------------------
void save_all_users(User *head) {
    ensure_dirs();

    FILE *f = fopen("data/users.txt", "w");
    if (!f) {
        perror("Failed to open data/users.txt for writing");
        return;
    }

    User *cur = head;
    while (cur) {
        fprintf(f, "%d,%s\n", cur->id, cur->name);
        save_user_usage_to_file(cur);
        cur = cur->next;
    }

    fclose(f);
}

// -----------------------------------------------------------------------------
// Load all users from data/users.txt
// -----------------------------------------------------------------------------
void load_all_users(User **head) {
    ensure_dirs();

    FILE *f = fopen("data/users.txt", "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        // id,name
        char *idS = strtok(line, ",\n");
        char *name = strtok(NULL, ",\n");
        if (!idS || !name) continue;

        int id = atoi(idS);
        if (id <= 0) continue;

        User *u = create_user(id, name);
        add_user(head, u);
        load_user_usage_from_file(u);
    }

    fclose(f);
}

// -----------------------------------------------------------------------------
// Save a daily report for a specific user inside data/reports/
// -----------------------------------------------------------------------------
void save_report(User *u, AnalysisResult r) {
    if (!u) return;
    ensure_dirs();

    char path[128];
    snprintf(path, sizeof(path), "data/reports/%s_report.txt", u->name);

    FILE *f = fopen(path, "w");
    if (!f) {
        perror("Error creating report file");
        return;
    }

    fprintf(f, "=== Daily Report for %s ===\n", u->name);
    fprintf(f, "Total screen time: %d mins\n\n", r.totalTime);

    fprintf(f, "--- App-wise Usage ---\n");
    for (int i = 0; i < r.appCount; i++) {
        fprintf(f, "%s: %d mins\n", r.appStats[i].name, r.appStats[i].minutes);
    }

    fprintf(f, "\n--- Time Slot Breakdown ---\n");
    for (int i = 0; i < r.slotCount; i++) {
        fprintf(f, "%s: %d mins\n", r.slotStats[i].name, r.slotStats[i].minutes);
    }

    fclose(f);
    printf("Report saved successfully at: %s\n", path);
}
