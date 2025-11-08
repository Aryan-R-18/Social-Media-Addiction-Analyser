#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "user.h"
#include "usage.h"
#include "analysis.h"   // ✅ ADD THIS LINE

void save_user_usage_to_file(User *u);
void load_user_usage_from_file(User *u);
void save_all_users(User *head);
void load_all_users(User **head);
void save_report(User *u, AnalysisResult r);  // already fine

#endif
