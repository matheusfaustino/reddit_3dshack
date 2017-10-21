#include "display.h"

int item_selected = -1;
int total_items = 0;

void display_init()
{
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &downScreen);
}

void show_list(reddit_list *head)
{
    consoleSelect(&topScreen);
    consoleClear();

    int count = 0;
    reddit_list *list_aux = head;

    printf("Selected Item: %d\n", item_selected);
    while (list_aux != NULL && count < MAX_DISPLAY_ITEMS) {
        count++;

        print_item(list_aux->post, count);

        list_aux = list_aux->next;
    }
}

void selection(const char *action)
{
    if (strcmp(action, "DOWN") == 0) {
        if (item_selected < MAX_DISPLAY_ITEMS)
            item_selected++;
    }
    else {
        if (item_selected > 0)
            item_selected--;
    }
}

void print_item(reddit_post post, int post_index)
{
    if (post_index == item_selected)
        printf("\n%sTitle (%s): %s %s\n", COLOR_GREEN, post.id, post.title, COLOR_RESET);
    else
        printf("\nTitle (%s): %s\n", post.id, post.title);
}

void print_desc_post(reddit_list *head)
{
    consoleSelect(&downScreen);
    consoleClear();

    int count = 1;
    reddit_list *list_aux = head;

    while (list_aux != NULL && count != item_selected) {
        list_aux = list_aux->next;
        count++;
    }

    printf("Title: %s\n", list_aux->post.title);
    printf("\nDescription: \n-------------------\n%s\n", trim(list_aux->post.desc, 400));
}
