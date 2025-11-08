#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "user.h"

// Structure to store individual statistics (for each app or time slot)
typedef struct {
    char name[64];   // Name of the app or time slot
    int minutes;     // Time spent in minutes
} StatItem;

// Structure to store full analysis results for a user
typedef struct {
    int totalTime;    // Total time spent overall
    int instaTime;    // Time spent on Instagram (optional)
    int nightTime;    // Time spent during night (optional)

    // Arrays to store statistics for all apps and time slots
    StatItem appStats[50];
    int appCount;

    StatItem slotStats[10];
    int slotCount;
} AnalysisResult;

// Function to analyze a user's data and return the results
AnalysisResult analyze_user(User *u);

#endif
