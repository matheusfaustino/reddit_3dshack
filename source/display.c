#include "display.h"

int item_selected = -1;
int total_items = 0;

void show_list(reddit_list *head)
{
    int count = 0;
    reddit_list *list_aux = head;

    printf("Selected Item: %d\n", item_selected);
    while (list_aux != NULL && count < MAX_DISPLAY_ITEMS) {
        count++;

        if (count == item_selected)
            printf("\n%sTitle (%s): %s %s\n", COLOR_GREEN, list_aux->post.id, list_aux->post.title, COLOR_RESET);
        else
            printf("\nTitle (%s): %s\n", list_aux->post.id, list_aux->post.title);

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
