#ifndef _E_TERM_H_
#define _E_TERM_H_

#include <stdlib.h>
#include "DEV_Config.h"
#include "EPD_5in83.h"
#include "/home/grawr/e-term/lib/GUI/GUI_Paint.h"

#define TERM_XSTART     4
#define TERM_YSTART     4
#define TERM_XEND       (EPD_5IN83_WIDTH - 4)
#define TERM_YEND       (EPD_5IN83_HEIGHT - 4)
#define TERM_FOREGROUND BLACK
#define TERM_BACKGROUND WHITE
#define BUF_LEN         100
#define TERM_FONT       Font12
#define IMAGE_SIZE      ((EPD_5IN83_WIDTH / 8 ) * EPD_5IN83_HEIGHT)

typedef struct {
    UWORD   Xcursor;
    UWORD   Ycursor;
    UBYTE   *Image;
    char    Buf[BUF_LEN];
    uint8_t Buf_index;
    sFONT   *Font;
}   TERM_WINDOW;

int init_term(TERM_WINDOW *t);

#endif
