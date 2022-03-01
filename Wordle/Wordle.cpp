#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <array>

std::string getColoredChar(char c, int correct)
{
    std::string base_string = "\x1b[";
    switch (correct)
    {
        case 0: {base_string += "m"; break;}
        case 1: {base_string += "32m"; break;}
        case 2: {base_string += "30;42m"; break;}
    }
    base_string += c;
    return base_string += "\r";
}


#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};


int main()
{
    std::string secret;
    std::string words;
    std::array<std::string, 6> guesses;

    // Setting up for console colors -----------------------------------------
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return GetLastError();
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return GetLastError();

    std::cout << FOREGROUND(ForegroundColor::BrightRed, "Hello world!") << std::endl;
    std::cout << BACKGROUND(BackgroundColor::BrightRed, "Hello world!") << std::endl;
    std::cout << BACKGROUND(BackgroundColor::Yellow, "AB")
        << BACKGROUND(BackgroundColor::Green, "C") << BACKGROUND(BackgroundColor::Red, "DE") << std::endl;

    wprintf(L"\x1b[32mGreen on black\r\n");
    wprintf(L"\x1b[30;42mBlack on green\r\n");
    wprintf(L"\x1b[mReset to white on black\r\n");
    
    // Reading file ---------------------------------------------------------
    std::ifstream file("words.txt");
    if (file.is_open())
    {
        char currentchar;
        while (file)
        {
            currentchar = file.get();
            words += currentchar;
        }

        // std::string currentLine;
        // while (file)
        // {
        //     getline(file, currentLine);
        //     words.append(currentLine);
        // }
    }
    else
    {
        std::cout << "Couldn't open file"<< std::endl;
    }
    file.close();

    // Picking random word -------------------------------------------------------
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0, 8597);
    int randomRangedInt = distribution(generator);
    // secret = words.substr( randomRangedInt * 6, 5);
    secret = "level";

    // Game start ----------------------------------------------------------------
    std::cout << "What is your first guess?" << std::endl;
    std::cin >> guesses[0];

    for (int round = 1; round < 7; ++round)
    {
        for (int charPos = 0; charPos < 5; ++charPos)
        {
            std::string guess = guesses[charPos];
            if (guess[charPos] == secret[charPos])
            {
                std::cout << getColoredChar(guess[charPos], 2);
                std::cout << "test";
            }
            else
            {
                // Check against other letters in word
                bool match = false;
                for (int j = 0; j < 5; ++j)
                {
                    if (j == charPos) continue; // do not check letter in same location as self
                    if (guess[charPos] == secret[j])
                    {
                        match = true;
                    }
                }
                
                std::cout << getColoredChar(guess[charPos], match ? 1 : 0);
                
            }
        }
        if (round < 7)
        {
            std::cout << std::endl;;
            std::cout << "OK, next guess:";
            std::cin >> guesses[round +1];
        }
        else
        {
            std::cout << "over";
        }
    }

    

    
    
    
    
    return 0;
}
