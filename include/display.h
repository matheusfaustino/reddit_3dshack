#ifndef display__h
#define display__h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>

#include "reddit.h"

#define MAX_DISPLAY_ITEMS 8

#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[1;32m"


extern int item_selected;
extern int total_items;

void show_list(reddit_list *head);
void selection(const char *action);

#endif
