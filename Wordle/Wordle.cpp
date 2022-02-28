#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>
#include <Windows.h>
#include <stdio.h>

char getColoredChar(char c, std::string color)
{
    std::map<std::string, std::string> colors ={
        {"green", "42"},
        {"red", "42"},
        {"blue", "42"}};
}


int main()
{
    std::string secret;
    std::string guess;
    std::string words;

    // Setting up for console colors
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return GetLastError();
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return GetLastError();
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) return GetLastError();
    
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

    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0, 8597);
    int randomRangedInt = distribution(generator);
    secret = words.substr( randomRangedInt * 6, 5);

    std::cout << "What is your first guess?" << std::endl;
    std::cin >> guess;

    for (int i = 0; i < 5; ++i)
    {
        if (secret[i] == guess[i])
        {
            std::cout <<guess.at(i);
        }
        else
        {
            for (int j = 0; j < 5; ++j)
            {
                if (j == i) continue;
                if (guess[i] == secret[j])
                {
                    std::cout <<guess.at(i);
                }
                else
                {
                    std::cout << guess[i];
                }
            }
        }
        if (i < 4)
        {
            std::cout << std::endl;;
            std::cout << "OK, next guess:";
            std::cin >> guess;
        }
        else
        {
            std::cout << "over";
        }
    }

    

    
    
    
    
    return 0;
}
