#pragma once

#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include <array>



int main()
{
    std::string words;
    bool play = true;
    
    // Setting up for console colors -----------------------------------------
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return GetLastError();
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return GetLastError();
    // wprintf(L"\x1b[32mGreen on black\r\n");
    // wprintf(L"\x1b[30;42mBlack on green\r\n");
    // wprintf(L"\x1b[mReset to white on black\r\n");
    
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

    while (play)
    {
        std::string secret;
        std::array<std::string, 6> guesses;
        bool has_won = false;
        
        // Picking random word -------------------------------------------------------
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distribution(0, 8597);
        int randomRangedInt = distribution(generator);
        // secret = words.substr( randomRangedInt * 6, 5);
        secret = "level";

        // Game start ----------------------------------------------------------------
        for (int round = 0; round < 6; ++round)
        {
            std::cout << "\x1b[mWhat's your guess?\r" << std::endl;
            std::cin >> guesses[round];
            int correctChars = 0;
        
            for (int charPos = 0; charPos < 5; ++charPos)
            {
                std::string guess = guesses[round];
                if (guess[charPos] == secret[charPos])
                {
                    correctChars ++;
                    printf("\x1b[30;42m%hc\033[0m", guess[charPos]);
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
                    match ? printf("\x1b[92m%hc\033[0m", guess[charPos]) :
                            printf("\033[37;40m%hc\033[0m", guess[charPos]);
                }
                if (correctChars == 5)
                {
                    has_won = true;
                }
            }
            std::cout << std::endl;
            if (round == 5 || has_won)
            {
                break;
            }
        }

        if (has_won)
        {
            printf("You nailed it!\n");
        }
        else
        {
            printf("Sorry to see you humiliate yourself like that. Better luck next time.\n");
        }

        printf("Play again? y/n\n");
        char playAgain;
        std::cin >> playAgain;
        if (playAgain != 'y') play = false;
    }
        
    return 0;
}
