#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "analysis.h"

AnalysisResult analyze_user(User *u)
{
    AnalysisResult res;
    res.totalTime = 0;
    res.appCount = 0;
    res.slotCount = 0;

    if (!u)
    {
        printf("Error: User data not found.\n");
        return res;
    }

    struct Usage *cur = u->usageHead;

    while (cur)
    {
        // Ensure valid duration
        if (cur->duration <= 0)
        {
            printf("Warning: Invalid duration for app '%s'. Skipping entry.\n", cur->appName);
            cur = cur->next;
            continue;
        }

        res.totalTime += cur->duration;

        // --- App-wise aggregation ---
        int foundApp = 0;
        for (int i = 0; i < res.appCount; i++)
        {
            if (strcasecmp(res.appStats[i].name, cur->appName) == 0)
            {
                res.appStats[i].minutes += cur->duration;
                foundApp = 1;
                break;
            }
        }
        if (!foundApp && res.appCount < 50)
        {
            strcpy(res.appStats[res.appCount].name, cur->appName);
            res.appStats[res.appCount].minutes = cur->duration;
            res.appCount++;
        }

        // --- Time-slot aggregation ---
        int foundSlot = 0;
        for (int i = 0; i < res.slotCount; i++)
        {
            if (strcasecmp(res.slotStats[i].name, cur->timeSlot) == 0)
            {
                res.slotStats[i].minutes += cur->duration;
                foundSlot = 1;
                break;
            }
        }
        if (!foundSlot && res.slotCount < 10)
        {
            strcpy(res.slotStats[res.slotCount].name, cur->timeSlot);
            res.slotStats[res.slotCount].minutes = cur->duration;
            res.slotCount++;
        }

        cur = cur->next;
    }

    // --- Display Analysis Summary ---
    printf("\n=== Analysis for %s ===\n", u->name);
    printf("Total Social Media Time: %d minutes\n", res.totalTime);
    printf("\n--- App Usage ---\n");
    for (int i = 0; i < res.appCount; i++)
    {
        printf("%s: %d minutes\n", res.appStats[i].name, res.appStats[i].minutes);
    }

    printf("\n--- Time Slot Distribution ---\n");
    for (int i = 0; i < res.slotCount; i++)
    {
        printf("%s: %d minutes\n", res.slotStats[i].name, res.slotStats[i].minutes);
    }

    printf("\nAnalysis completed successfully.\n");

    return res;
}
