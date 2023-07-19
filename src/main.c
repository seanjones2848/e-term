#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "e_term.h"

uint8_t keep_running = 1;

void    sleep_screen(void)
{
    Debug("Clear...\r\n");
    EPD_5IN83_Clear();
    Debug("Goto Sleep...\r\n");
    EPD_5IN83_Sleep();
    DEV_Delay_ms(2000);//important, at least 2s
    // close 5V
    DEV_Module_Exit();
}

void  Handler(int signo)
{
    keep_running = 0;
}

void    exit_program(TERM_WINDOW *t)
{
    //System Exit
    Debug("\r\nHandler:exit\r\n");
    free(t->Image);
    sleep_screen();
    exit(0);
}

void    awaken_screen(void)
{
    Debug("e-Paper Init and Clear...\r\n");
    EPD_5IN83_Init();
    EPD_5IN83_Clear();
    DEV_Delay_ms(500);
}

int main(void)
{
    TERM_WINDOW term;
    int counter = 0;

    printf("First round of tests for e-paper terminal\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    if (init_term(&term) == -1) {
        printf("Failed to init term...\r\n");
        return -1;
    }
    //Create a new image cache
    

    awaken_screen();

    while(1) {
        if (!keep_running) {
            exit_program(&term);
        }
        // display shell prompt
        EPD_5IN83_Display(term.Image);
        // - know where you are in the file structure
        // - track where cursor is
        // accept command
        // - accept keyboard input
        // - display chars on screen gathered within screen refreshtime
        //   - have a sleep in the loop to take up time not spend gathering keys and computing loop
        // process command
        // - submit after enter is pressed for processing
        // - be able to capture exit keys to ecsape without interupting process
        // output responses
        // log to file
        // scroll screen when x number of lines is displayed
        if (counter) {
            Paint_Clear(WHITE);
            counter = 0;
        }
        else {
            Paint_Clear(BLACK);
            counter = 1;
        }
        Debug("I did a round\r\n");
        DEV_Delay_ms(500);
    }

    return 0;
}
