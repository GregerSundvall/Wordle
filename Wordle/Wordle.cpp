#include <iostream>
#include <random>
#include <string>
#include <initializer_list>
#include <array>
#include "words.h"
#include "consoleColors.h"

int main()
{
    words words;
    bool play = true;
    
    setup_console_colors_support();
    if (words.import_from_file("words.txt"))
    {
        std::cout << "Words imported from file successfully.\n" << std::endl;
    }
    else
    {
        std::cout << "Something went wrong while imoporting words from file\n" << std::endl;
    }

    std::cout << "Five letter word. Six guesses. You got this.";
    
    // Game loop -----------------------------------------------------------------
    while (play)
    {
        std::string secret;
        bool has_won = false;
        secret = words.get_random();
        std::array<std::string, 6> guesses{};

        // Game session start ----------------------------------------------------------------
        for (int round = 0; round < 6; ++round)
        {
            int input_error{}; // -1 = No error
            std::string guess;
            int correct_chars = 0;

            // Get input
            while (input_error != -1)
            {
                std::cout << "\n" << "\x1b[mWhat's your guess? ";
                std::cin >> guess;
                input_error = words.is_valid(guess);
                switch (input_error)
                {
                    case 0: 
                        std::cout << "\nWord too short. F I V E letters please." << std::endl;
                        break;
                    case 1:
                        std::cout << "\nWord too long. F I V E letters please." << std::endl;
                        break;
                    case 2:
                        std::cout << "\nCome on now, five L E T T E R S please.";
                        break;
                    default:
                        std::cout << "\n";
                        break;
                }
            }
            guesses[round] = words.to_upper(guess);
        
            // Check and print the guess
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

