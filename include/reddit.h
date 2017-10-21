#ifndef reddit__h
#define reddit__h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <3ds.h>

#include "cJSON.h"
#include "request.h"

#define URL_REDDIT_3DSHACK "https://www.reddit.com/r/3dshacks.json"

typedef struct reddit_post
{
    char *title;
    char *id;
} reddit_post;

typedef struct reddit_list
{
    struct reddit_post post;
    struct reddit_list *next;
} reddit_list;

reddit_list* handle_initial_list(cJSON *root);

#endif
