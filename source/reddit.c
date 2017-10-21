#include "reddit.h"

reddit_list* handle_initial_list(cJSON *root)
{
    int count = 0;
    int count_children;

    cJSON *data = cJSON_GetObjectItem(root, "data");
    cJSON *children = cJSON_GetObjectItem(data, "children");
    cJSON *elem = NULL;
    cJSON *elem_data = NULL;

    reddit_list *head = (reddit_list *) malloc(sizeof(reddit_list));
    reddit_list *current = head;
    reddit_post *post = NULL;

    count_children = cJSON_GetArraySize(children);
    cJSON_ArrayForEach(elem, children) {
        count++;

        elem_data = cJSON_GetObjectItem(elem, "data");

        post = (reddit_post*) malloc(sizeof(reddit_post));
        post->title = cJSON_GetObjectItem(elem_data, "title")->valuestring;
        post->id = cJSON_GetObjectItem(elem_data, "id")->valuestring;
        post->desc = cJSON_GetObjectItem(elem_data, "selftext")->valuestring;

        current->post = *post;
        current->next = NULL;

        // @todo: improve it (workaround)
        if (count >= count_children)
            current->next = NULL;
        else
            current->next = (reddit_list *) malloc(sizeof(reddit_list));

        current = current->next;

        free(post);
    }

    free(post);
    free(current);

    return head;
}
