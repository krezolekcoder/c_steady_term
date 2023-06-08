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

void c_steady_term_draw_rect(char *frame_buffer, char ch, int x_start, int y_start, int x_width, int y_width)
{
    c_steady_term_draw_line(frame_buffer, ch, x_start, x_start + x_width, y_start, y_start);
    c_steady_term_draw_line(frame_buffer, ch, x_start, x_start + x_width, y_start + y_width - 1,
                            y_start + y_width - 1);
    c_steady_term_draw_line(frame_buffer, ch, x_start, x_start, y_start, y_start + y_width);
    c_steady_term_draw_line(frame_buffer, ch, x_start + x_width, x_start + x_width, y_start, y_start + y_width);
}

void c_steady_term_draw_triangle(char *frame_buffer, char ch, int x1, int y1, int x2, int y2, int x3, int y3)
{
    c_steady_term_draw_line(frame_buffer, ch, x1, x2, y1, y2);
    c_steady_term_draw_line(frame_buffer, ch, x1, x3, y1, y3);
    c_steady_term_draw_line(frame_buffer, ch, x2, x3, y2, y3);
}


void c_steady_term_draw_circle(char *frame_buffer, char ch, int x_center, int y_center, int radius)
{
}