#pragma once
#include <Windows.h>
#include <stdio.h>


// Setting up for console colors -----------------------------------------
DWORD setup_console_colors_support()
{
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h_out == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dw_mode = 0;
    if (!GetConsoleMode(h_out, &dw_mode)) return GetLastError();
    dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(h_out, dw_mode)) return GetLastError();
}
