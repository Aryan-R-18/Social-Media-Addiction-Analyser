#include <stdio.h>
#include <string.h>
#include "analysis.h"

void suggest_improvements(AnalysisResult r) {
    printf("\n----- Suggestions -----\n");

    // 1️⃣ General total screen time advice
    if (r.totalTime > 300) {
        printf("High total screen time today (%d mins). Consider taking a digital detox for a few hours.\n", r.totalTime);
    } else if (r.totalTime > 180) {
        printf("Moderate screen time (%d mins). Try scheduling short breaks every 30 minutes.\n", r.totalTime);
    } else {
        printf("Good screen balance (%d mins). Keep maintaining healthy digital habits.\n", r.totalTime);
    }

    // 2️⃣ Time-slot based suggestion
    for (int i = 0; i < r.slotCount; i++) {
        if (strcasecmp(r.slotStats[i].name, "Night") == 0 && r.slotStats[i].minutes > 60) {
            printf("You've spent %d mins using your phone at night. Try enabling bedtime mode and keeping your phone away 1 hour before sleep.\n",
                   r.slotStats[i].minutes);
        }
    }

    // 3️⃣ App usage concentration warning
    if (r.appCount > 0) {
        int maxIndex = 0;
        for (int i = 1; i < r.appCount; i++) {
            if (r.appStats[i].minutes > r.appStats[maxIndex].minutes)
                maxIndex = i;
        }

        if (r.appStats[maxIndex].minutes > r.totalTime * 0.5) {
            printf("Most of your time (%.1f%%) was spent on '%s'. Consider setting time limits or scheduling focused breaks.\n",
                   (r.appStats[maxIndex].minutes * 100.0 / r.totalTime),
                   r.appStats[maxIndex].name);
        }
    }

    // 4️⃣ Restriction suggestion
    printf("Consider setting short 'no-phone' periods (e.g., during meals or study sessions) to improve focus.\n");

    printf("------------------------\n");
}
