#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>


#define FRAME_WIDTH  128
#define FRAME_HEIGHT 64

static char screen[FRAME_WIDTH * FRAME_HEIGHT];

uint32_t write_text_to_frame_buffer(char *frame_buffer, int x, int y, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Use vsprintf to format the string and write it to the frame buffer
    int written = vsprintf(&frame_buffer[y * FRAME_WIDTH + x], format, args);

    va_end(args);

    return written;
}


void draw_line(char *frame_buffer, char ch, uint32_t x_start, uint32_t y_start, uint32_t x_end, uint32_t y_end)
{
    int dx     = x_end - x_start;
    int dy     = y_end - y_start;
    int step_x = (dx < 0) ? -1 : 1;
    int step_y = (dy < 0) ? -1 : 1;

    dx = step_x * dx;
    dy = step_y * dy;

    int x = x_start;
    int y = y_start;

    // Calculate the index in the frame buffer corresponding to the starting coordinates
    int index           = y * FRAME_WIDTH + x;
    frame_buffer[index] = ch;  // Set the starting point

    if (dx > dy) {
        int error = dx / 2;
        while (x != x_end) {
            x += step_x;
            error -= dy;
            if (error < 0) {
                y += step_y;
                error += dx;
            }
            index               = y * FRAME_WIDTH + x;
            frame_buffer[index] = ch;
        }
    }
    else {
        int error = dy / 2;
        while (y != y_end) {
            y += step_y;
            error -= dx;
            if (error < 0) {
                x += step_x;
                error += dy;
            }
            index               = y * FRAME_WIDTH + x;
            frame_buffer[index] = ch;
        }
    }
}

int main()
{


    HANDLE hConsole =
        CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    COORD coord = { .X = 0, .Y = 0 };

    uint32_t ticks = 0;

    while (1) {

        ticks += 100;

        if (ticks >= 2000) {
            ticks = 0;
        }
        // write_text_to_frame_buffer(&screen, 0, 0, "Current tick ms %d ", ticks);
        draw_line(screen, '*', 10, 5, 20, 15);
        WriteConsoleOutputCharacter(hConsole, screen, FRAME_WIDTH * FRAME_HEIGHT, coord, &dwBytesWritten);


        Sleep(1000);
    }


    return 0;
}
