#ifndef display__h
#define display__h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <3ds.h>

#include "reddit.h"
#include "string_utils.h"

#define MAX_DISPLAY_ITEMS 8

#define COLOR_RESET "\x1b[0m"
#define COLOR_GREEN "\x1b[1;32m"


// navigate menu
int item_selected;
int total_items;

// reference to each screen
PrintConsole topScreen, downScreen;

void display_init();
void show_list(reddit_list *head);
void selection(const char *action);
void print_item(reddit_post post, int post_index);
void print_desc_post(reddit_list *head);

#endif
