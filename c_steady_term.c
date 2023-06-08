/**
 * @file c_steady_term.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-06-08
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "c_steady_term.h"
#include "config.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int c_steady_term_write_text(char *frame_buffer, int x, int y, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Use vsprintf to format the string and write it to the frame buffer
    int written = vsprintf(&frame_buffer[y * FRAME_WIDTH + x], format, args);

    va_end(args);

    return written;
}

void c_steady_term_draw_line(char *frame_buffer, char ch, int x_start, int x_end, int y_start, int y_end)
{
    int dy = y_end - y_start;
    int dx = x_end - x_start;

    // SWAP VARIABLES
    if (dx < 0 && dy < 0) {
        int tmp = x_start;
        x_start = x_end;
        x_end   = tmp;

        tmp     = y_start;
        y_start = y_end;
        y_end   = tmp;
    }
    else if (dx > 0 && dy < 0) {
        int tmp = x_start;
        x_start = x_end;
        x_end   = tmp;
    }

    if (dy != 0 && dx != 0) {
        int derivative = labs(dy / dx);

        if (dx * dy > 0) {
            for (int x = x_start; x < x_end; x++) {
                for (int y = x * derivative; y < x * derivative + derivative; y++) {
                    frame_buffer[y * FRAME_WIDTH + x] = ch;
                }
            }
        }
        else {
            int y_offset = y_end < y_start ? y_end : y_start;

            for (int x = x_start; x > x_end; x--) {
                for (int y = (x_start - x) * derivative + y_offset;
                     y < ((x_start - x) * derivative) + derivative + y_offset; y++) {
                    frame_buffer[y * FRAME_WIDTH + x] = ch;
                }
            }
        }
    }
    else {
        if (dy == 0 && dx != 0) {

            for (int x = x_start; x < x_end; x++) {
                frame_buffer[y_start * FRAME_WIDTH + x] = ch;
            }
        }
        else if (dx == 0 && dy != 0) {

            for (int y = y_start; y < y_end; y++) {
                frame_buffer[y * FRAME_WIDTH + x_start] = ch;
            }
        }
        else {
            ;
        }
    }
}
