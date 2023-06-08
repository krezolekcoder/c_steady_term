#include "config.h"
#include "platform_port.h"
#include <windows.h>


static void set_console_size(int width, int height)
{
    HANDLE     std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect       = { 0, 0, width - 1, height - 1 };

    SetConsoleWindowInfo(std_handle, TRUE, &rect);
}

static void set_console_title(const char *title)
{
    SetConsoleTitleA(title);
}

void platform_port_init(void)
{
    set_console_size(FRAME_WIDTH, FRAME_HEIGHT);
    set_console_title("Character Framebuffer Example");
}

void platform_port_send_frame_buffer(const char *char_buffer, int width, int height)
{
    HANDLE std_handle  = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  coord       = { width, height };
    COORD  start_coord = { 0, 0 };
    DWORD  chars_written;

    WriteConsoleOutputCharacterA(std_handle, char_buffer, width * height, start_coord, &chars_written);
}
