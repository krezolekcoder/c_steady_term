#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>


#define FRAME_WIDTH  128
#define FRAME_HEIGHT 64


void set_console_size(int width, int height)
{
    HANDLE     std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect       = { 0, 0, width - 1, height - 1 };

    SetConsoleWindowInfo(std_handle, TRUE, &rect);
}

void set_console_title(const char *title)
{
    SetConsoleTitleA(title);
}

void write_console_output(const char *char_buffer, int width, int height)
{
    HANDLE std_handle  = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  coord       = { width, height };
    COORD  start_coord = { 0, 0 };
    DWORD  chars_written;

    WriteConsoleOutputCharacterA(std_handle, char_buffer, width * height, start_coord, &chars_written);
}

uint32_t write_text_to_frame_buffer(char *frame_buffer, int x, int y, const char *format, ...)
{
    va_list args;
    va_start(args, format);

    // Use vsprintf to format the string and write it to the frame buffer
    int written = vsprintf(&frame_buffer[y * FRAME_WIDTH + x], format, args);

    va_end(args);

    return written;
}


void draw_line(char *frame_buffer, char ch, uint32_t x_start, uint32_t x_end, uint32_t y_start, uint32_t y_end)
{

    // calculate dy/dx

    uint32_t dy = labs(y_end - y_start);
    uint32_t dx = labs(x_end - x_start);

    uint32_t derivative = 0;

    if (dy > dx) {
        derivative = dy / dx;

        for (int x = x_start; x < x_end; x++) {
            for (int y = x * derivative; y < x * derivative + derivative; y++) {
                frame_buffer[y * FRAME_WIDTH + x] = ch;
            }
        }
    }
    else {
        derivative = dx / dy;

        for (int y = y_start; y < y_end; y++) {
            for (int x = y * derivative; x < y * derivative + derivative; x++) {
                frame_buffer[y * FRAME_WIDTH + x] = ch;
            }
        }
    }
}



int main()
{

    // Create the console window
    set_console_size(FRAME_WIDTH, FRAME_HEIGHT);
    set_console_title("Character Framebuffer Example");

    // Example character framebuffer (replace with your own data)
    char framebuffer[FRAME_WIDTH * FRAME_HEIGHT];
    memset(framebuffer, ' ', FRAME_WIDTH * FRAME_HEIGHT);

    // Display the character framebuffer

    draw_line(framebuffer, '*', 0, 0, 0, 10);

    write_console_output(framebuffer, FRAME_WIDTH, FRAME_HEIGHT);

    getch();
    return 0;
}
