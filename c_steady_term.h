#ifndef C_STEADY_TERM_H
#define C_STEADY_TERM_H

#include <stdint.h>

void c_steady_term_draw_line(char *frame_buffer, char ch, int x_start, int x_end, int y_start, int y_end);
int  c_steady_term_write_text(char *frame_buffer, int x, int y, const char *format, ...);
void c_steady_term_draw_rect(char *frame_buffer, char ch, int x_start, int y_start, int x_width, int y_width);
void c_steady_term_draw_triangle(char *frame_buffer, char ch, int x1, int y1, int x2, int y2, int x3, int y3);
void c_steady_term_draw_circle(char *frame_buffer, char ch, int x_center, int y_center, int radius);

#endif /* C_STEADY_TERM_H */
