#include <stdio.h>
#include <string.h>
#include <windows.h>


#define X_SIZE 80
#define Y_SIZE 25

static wchar_t screen[X_SIZE * Y_SIZE];



int main()
{

    sprintf(screen, "Hello world ! ");
    // HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ);
    HANDLE hConsole =
        CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;

    COORD coord = { .X = 0, .Y = 0 };

    while (1) {
        WriteConsoleOutputCharacter(hConsole, screen, 80 * 25, coord, &dwBytesWritten);
        Sleep(100);
    }
    // GetAsyncKeyState()
    return 0;
}
