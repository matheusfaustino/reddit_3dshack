#ifndef request__h
#define request__h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <3ds.h>

#include "cJSON.h"

cJSON* http_download_json(const char *url);

#endif
