#include "c_steady_term.h"
#include "config.h"
#include "platform_port.h"
#include <conio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>



int main()
{

    platform_port_init();

    char framebuffer[FRAME_WIDTH * FRAME_HEIGHT];
    memset(framebuffer, ' ', FRAME_WIDTH * FRAME_HEIGHT);

    c_steady_term_draw_line(framebuffer, '*', 0, 10, 0, 10);
    c_steady_term_draw_line(framebuffer, '*', 10, 0, 0, 10);

    c_steady_term_draw_line(framebuffer, '*', 20, 10, 20, 10);
    c_steady_term_draw_line(framebuffer, '*', 10, 20, 20, 10);

    // write_console_output(framebuffer, FRAME_WIDTH, FRAME_HEIGHT);

    c_steady_term_write_text(framebuffer, 50, 30, "HELLO WORLD %d %d ", 10, 20);

    platform_port_send_frame_buffer(framebuffer, FRAME_WIDTH, FRAME_HEIGHT);
    getch();
    return 0;
}
