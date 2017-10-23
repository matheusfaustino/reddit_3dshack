#include "display.h"

int item_selected = -1;
int total_items = 0;

int line_show = 0;
// int page_post = 0;

void display_init()
{
    // screen
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &downScreen);

    // window
    consoleInit(GFX_BOTTOM, &downDescWindow);
    consoleInit(GFX_BOTTOM, &downActionWindow);

    consoleSetWindow(&downActionWindow, 2, 27, 35, 5);
    consoleSetWindow(&downDescWindow, 2, 0, 35, 26);
}

void show_list(reddit_list *head)
{
    consoleSelect(&topScreen);
    consoleClear();

    int count = 0;
    int count_all = 0;
    int page = item_selected / MAX_DISPLAY_ITEMS;
    reddit_list *list_aux = head;

    printf("\x1b[1mThe 3DS Hacks Subreddit\n");
    // printf("Selected Item: %d\n", item_selected);
    while (list_aux != NULL && count < MAX_DISPLAY_ITEMS) {
        count_all++;

        // show items based on the page
        if (page * count_all >= page * MAX_DISPLAY_ITEMS) {
            count++;

            // print_item(list_aux->post, count);
            print_item(list_aux->post, count_all);
        }

        list_aux = list_aux->next;
    }
}

void selection(const char *action)
{
    if (strcmp(action, "DOWN") == 0) {
        // if (item_selected < MAX_DISPLAY_ITEMS)
        item_selected++;

        line_show = 0;
    }
    else if (strcmp(action, "UP") == 0) {
        if (item_selected > 0)
            item_selected--;

        line_show = 0;
    }
    else if (strcmp(action, "LEFT") == 0) {
        // @task: bug quando nao tem nada selecionado, item_selected = 0
        line_show--;
    }
    else if (strcmp(action, "RIGHT") == 0) {
        line_show++;
    }
}

void print_item(reddit_post post, int post_index)
{
    if (post_index == item_selected)
        printf("\n%s- %s %s\n", COLOR_GREEN, post.title, COLOR_RESET);
    else
        printf("\n- %s\n", post.title);
}

void print_desc_post(reddit_list *head)
{
    consoleSelect(&downDescWindow);
    consoleClear();

    int count = 1;
    char *desc = NULL;
    reddit_list *list_aux = head;

    while (list_aux != NULL && count != item_selected) {
        list_aux = list_aux->next;
        count++;
    }

    desc = scroll_text(list_aux->post.desc, line_show);

    printf("\nDescription: \n-------------------\n%s\n", desc);
}

void print_actions()
{
    consoleSelect(&downActionWindow);
    consoleClear();

    printf("----------------------------------\n");
    printf(" B-Exit | A-Select | DPad-Move \n");
    printf("----------------------------------\n");
}

char* scroll_text(const char *txt, int line)
{
    size_t len = strlen(txt);

    if (len == 0)
        return "<no description>...";

    char *str = (char*) malloc(sizeof(char) * len);
    if (str == NULL) {
        printf("Error Malloc String\n");
        return "--";
    }

    int char_to_start = line * MAX_CHAR_PER_LINE;
    // help count how much line we should skip
    int aux_line = line;
    int count_chars_added = 0;
    int i;

    for (i = 0; i < len && count_chars_added <= TEXT_LIMIT_DESC; i++) {
        // new line
        if (i < char_to_start) {
            // when find a new line
            if (txt[i] == '\n' && --aux_line == 0) {
                // starts here, because it found a new line
                char_to_start = i;
            }

            // skip characters
            continue;
        }

        // add char to string to show
        str[count_chars_added++] = txt[i];
    }
    // end string
    str[count_chars_added] = '\0';

    return str;
}
