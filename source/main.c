#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>

#include <3ds.h>

#include "cJSON.h"
#include "request.h"
#include "reddit.h"
#include "display.h"

int main()
{
    gfxInitDefault();
    httpcInit(0); // Buffer size when POST/PUT.

    //Initialize console on top screen. Using NULL as the second argument tells the console library to use the internal console structure as current one
    // consoleInit(GFX_TOP, NULL);

    display_init();

    cJSON *root = http_download_json(URL_REDDIT_3DSHACK);
    reddit_list *list = handle_initial_list(root);

    show_list(list);

    // Main loop
    while (aptMainLoop()) {

        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        u32 kDown = hidKeysDown();
        if (kDown & KEY_B)
            break; // break in order to return to hbmenu

        if (kDown & KEY_DDOWN) {
            selection("DOWN");
            show_list(list);
        }

        if (kDown & KEY_DUP) {
            selection("UP");
            show_list(list);
        }

        if (kDown & KEY_A) {
            print_desc_post(list);
        }

        // code here
        // ---

        // Flush and swap framebuffers
        gfxFlushBuffers();
        gfxSwapBuffers();

        //Wait for VBlank
        gspWaitForVBlank();
    }

    // Exit services
    httpcExit();
    gfxExit();
    return 0;
}

