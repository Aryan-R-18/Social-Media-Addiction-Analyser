#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "user.h"
#include "usage.h"
#include "analysis.h"
#include "suggestions.h"
#include "file_handler.h"

// Normalize a string to lowercase for comparison
void to_lowercase(char *str)
{
    for (int i = 0; str[i]; i++)
        str[i] = tolower((unsigned char)str[i]);
}

// Print main menu
void print_menu()
{
    printf("\n=== Social Media Addiction Analyzer ===\n");
    printf("1. Register new user\n");
    printf("2. List users\n");
    printf("3. Log usage for a user\n");
    printf("4. View user daily report & suggestions\n");
    printf("5. Save and exit\n");
    printf("Choice: ");
}

int main()
{
    User *users = NULL;
    load_all_users(&users);

    int choice;

    while (1)
    {
        print_menu();

        // Validate menu choice
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number between 1–5.\n");
            while (getchar() != '\n')
                ; // Clear buffer
            continue;
        }

        if (choice == 1)
        {
            char name[64];
            printf("Enter new user name: ");
            scanf("%63s", name);

            // Validate name (no special characters)
            int valid = 1;
            for (int i = 0; name[i]; i++)
            {
                if (!isalnum(name[i]) && name[i] != '_' && name[i] != '-')
                {
                    valid = 0;
                    break;
                }
            }

            if (!valid)
            {
                printf("Invalid username! Use only letters, numbers, underscores, or hyphens.\n");
                continue;
            }

            if (find_user(users, name))
            {
                printf("User '%s' already exists.\n", name);
            }
            else
            {
                int id = 1;
                User *cur = users;
                while (cur)
                {
                    if (cur->id >= id)
                        id = cur->id + 1;
                    cur = cur->next;
                }

                User *u = create_user(id, name);
                add_user(&users, u);
                printf("User '%s' created with ID %d.\n", name, id);
            }
        }
        else if (choice == 2)
        {
            display_users(users);
        }
        else if (choice == 3)
        {
            char name[64];
            printf("Enter user name: ");
            scanf("%63s", name);

            User *u = find_user(users, name);
            if (!u)
            {
                printf("User '%s' not found. Please register first.\n", name);
                continue;
            }

            char app[64], slot[16];
            int dur;

            printf("Enter app name (e.g., Instagram): ");
            scanf("%63s", app);
            to_lowercase(app);

            // Duration validation
            printf("Enter duration minutes: ");
            if (scanf("%d", &dur) != 1 || dur <= 0)
            {
                printf("Invalid duration. Please enter a positive number.\n");
                while (getchar() != '\n')
                    ;
                continue;
            }

            printf("Enter time slot (Morning/Afternoon/Night): ");
            scanf("%15s", slot);
            to_lowercase(slot);

            // Validate slot input
            if (strcmp(slot, "morning") != 0 && strcmp(slot, "afternoon") != 0 && strcmp(slot, "night") != 0)
            {
                printf("Invalid time slot! Please enter Morning, Afternoon, or Night.\n");
                continue;
            }

            // Store usage
            Usage *nu = create_usage(app, dur, slot);
            if (!u->usageHead)
            {
                u->usageHead = u->usageTail = nu;
            }
            else
            {
                u->usageTail->next = nu;
                u->usageTail = nu;
            }

            printf("Usage for app '%s' added successfully for %s.\n", app, u->name);
        }
        else if (choice == 4)
        {
            char name[64];
            printf("Enter user name: ");
            scanf("%63s", name);

            User *u = find_user(users, name);
            if (!u)
            {
                printf("User '%s' not found.\n", name);
                continue;
            }

            // Analyze the user's usage
            AnalysisResult r = analyze_user(u);

            // Save the report in reports/ folder
            save_report(u, r);

            printf("\n=== Usage Summary for %s ===\n", u->name);
            printf("Total time spent: %d mins\n", r.totalTime);

            if (r.appCount == 0)
            {
                printf("\nNo app usage records found.\n");
            }
            else
            {
                printf("\nTime spent per app:\n");
                for (int i = 0; i < r.appCount; i++)
                {
                    printf("  %s: %d mins\n", r.appStats[i].name, r.appStats[i].minutes);
                }

                printf("\nTime spent per time slot:\n");
                for (int i = 0; i < r.slotCount; i++)
                {
                    printf("  %s: %d mins\n", r.slotStats[i].name, r.slotStats[i].minutes);
                }
            }

            // Print generalized suggestions only (no app-specific)
            suggest_improvements(r);

            printf("\nReport saved successfully for %s in 'reports/' folder.\n", u->name);
        }
        else if (choice == 5)
        {
            save_all_users(users);
            printf("Data saved successfully. Exiting program.\n");
            break;
        }
        else
        {
            printf("Invalid choice. Please select a valid option (1–5).\n");
        }
    }

    free_users(users);
    return 0;
}
