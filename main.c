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

void draw_line(char *frame_buffer, char ch, int x_start, int x_end, int y_start, int y_end)
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
            for (int x = x_start; x > x_end; x--) {
                for (int y = (x_start - x) * derivative; y < ((x_start - x) * derivative) + derivative; y++) {
                    frame_buffer[y * FRAME_WIDTH + x] = '*';
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



int main()
{

    // // Create the console window
    set_console_size(FRAME_WIDTH, FRAME_HEIGHT);
    set_console_title("Character Framebuffer Example");

    // // Example character framebuffer (replace with your own data)
    char framebuffer[FRAME_WIDTH * FRAME_HEIGHT];
    memset(framebuffer, ' ', FRAME_WIDTH * FRAME_HEIGHT);

    // Display the character framebuffer

    draw_line(framebuffer, '*', 0, 10, 0, 10);
    draw_line(framebuffer, '*', 10, 0, 0, 10);

    // draw_line(framebuffer, '*', 20, 10, 20, 10);
    draw_line(framebuffer, '*', 10, 20, 20, 10);


    write_console_output(framebuffer, FRAME_WIDTH, FRAME_HEIGHT);

    getch();
    return 0;
}
