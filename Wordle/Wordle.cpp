
#include <iostream>
#include <random>
#include <string>
#include <array>
#include "words.h"
#include "consoleColors.h"

bool check_input(std::string& input);

int main()
{
    words words;
    bool play = true;
    
    setup_console_colors_support();
    words.import_from_file("words.txt");

    std::cout << "Five letter word. Six guesses. You got this." << std::endl;
    
    // Game loop -----------------------------------------------------------------
    while (play)
    {
        std::string secret;
        std::array<std::string, 6> guesses;
        bool has_won = false;
        secret = words.get_random();
        // Game start ----------------------------------------------------------------
        for (int round = 0; round < 6; ++round)
        {
            bool input_error = true;
            while (input_error)
            {
                std::cout << "\n" << "\x1b[mWhat's your guess? ";
                std::cin >> guesses[round];
                input_error = check_input(guesses[round]);
            }
            
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

bool check_input(std::string& input)
{
    if (input.size() != 5)
    {
        std::cout << "F I V E letters please.";
        return true;
    }
    for (char& c : input)
    {
        if (!isalpha(c))
        {
            std::cout << "Five L E T T E R S please.";
            return true;
        }
        c = tolower(c);
    }
    return false;
}
