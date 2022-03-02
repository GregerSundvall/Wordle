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
    HANDLE h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    if (h_out == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dw_mode = 0;
    if (!GetConsoleMode(h_out, &dw_mode)) return GetLastError();
    dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(h_out, dw_mode)) return GetLastError();
    
    // Reading file ---------------------------------------------------------
    std::ifstream file("words.txt");
    if (file.is_open())
    {
        char current_char;
        while (file)
        {
            current_char = file.get();
            words += tolower(current_char);
        }
    }
    else
    {
        std::cout << "Couldn't open file"<< std::endl;
    }
    file.close();

    std::cout << "Five letter word. Six guesses. You got this." << std::endl;
    // Game loop -----------------------------------------------------------------
    while (play)
    {
        std::string secret;
        std::array<std::string, 6> guesses;
        bool has_won = false;
        
        // Picking random word -------------------------------------------------------
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distribution(0, 8597);
        int random_ranged_int = distribution(generator);
        secret = words.substr( random_ranged_int * 6, 5);

        // Game start ----------------------------------------------------------------
        for (int round = 0; round < 6; ++round)
        {
            std::cout << "\n" << "\x1b[mWhat's your guess? ";
            std::cin >> guesses[round];
            int correct_chars = 0;
        
            for (int char_pos = 0; char_pos < 5; ++char_pos)
            {
                std::string guess = guesses[round];
                if (guess[char_pos] == secret[char_pos])
                {
                    correct_chars ++;
                    std::cout << "\x1b[30;42m" << guess[char_pos] << "\033[0m";
                }
                else
                {
                    // Check against other letters in word
                    bool letter_is_in_word = false;
                    for (int j = 0; j < 5; ++j)
                    {
                        if (j == char_pos) continue; // do not check letter in same location as self
                        if (guess[char_pos] == secret[j])
                        {
                            letter_is_in_word = true;
                        }
                    }
                    
                    letter_is_in_word ? std::cout << "\x1b[30;43m" << guess[char_pos] << "\033[0m" :
                            std::cout << "\x1b[30;48;2;200;200;200m" << guess[char_pos] << "\033[0m";
                }
                if (correct_chars == 5)
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
            std::cout << "You nailed it!" << std::endl;
        }
        else
        {
            std::cout << "Sorry to see you humiliate yourself like that." << std::endl;
            std::cout << "The word was " << secret << ". Better luck next time." << std::endl;
        }

        std::cout << "Play again? (y/n)" << std::endl;
        char play_again;
        std::cin >> play_again;
        if (play_again != 'y') play = false;
    }
        
    return 0;
}
