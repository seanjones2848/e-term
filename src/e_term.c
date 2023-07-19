#include "e_term.h"

int init_term(TERM_WINDOW *t)
{
    t->Xcursor = TERM_XSTART;
    t->Ycursor = TERM_YSTART;
    t->Image = NULL;
    t->Buf_index = 0;
    t->Font = &TERM_FONT;
    for (int i = 0; i < BUF_LEN; i++) {
        t->Buf[i] = 0;
    }
    if((t->Image = (UBYTE *)malloc(IMAGE_SIZE)) == NULL) {
        printf("Failed to allocate image memory...\r\n");
        return -1;
    }
    // Init paint global with term image
    Paint_NewImage(t->Image, EPD_5IN83_WIDTH, EPD_5IN83_HEIGHT, 180, WHITE);
    return 1;
}
