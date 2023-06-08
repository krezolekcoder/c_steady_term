#ifndef C_STEADY_TERM_H
#define C_STEADY_TERM_H

#include <stdint.h>

void c_steady_term_draw_line(char *frame_buffer, char ch, int x_start, int x_end, int y_start, int y_end);
int  c_steady_term_write_text(char *frame_buffer, int x, int y, const char *format, ...);

#endif /* C_STEADY_TERM_H */
