#pragma once
#include "words.h"
#include <random>




size_t words::size()
{
    return data.size();
}

std::string words::get_random()
{
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distribution(0, data.size());
    return data.at(distribution(generator));
}

int words::is_valid(std::string input)
{
    if (input.size() < 5)
    {
        return 0;
    }
    
    if (input.size() > 5)
    {
        return 1;
    }

    for (size_t i = 0; i < 5; i++)
    {
        if (!isalpha(input.at(i)))
        {
            return 2;
        }
    }
    return -1;
}

std::string words::to_upper(std::string input)
{
    for (size_t i = 0; i < 5; i++)
    {
        input[i] = toupper(input[i]);
    }
    return input;
}

bool words::already_exists(std::string input)
{
    if (data.size() == 0)
    {
        return false;
    }
    for (size_t i = 0; i < data.size(); i++)
    {
        if (data.at(i) == input)
        {
            return true;
        }
    }
    return false;
}

void words::add(std::string input)
{
    if (is_valid(input))
    {
        input = to_upper(input);
        if (!already_exists(input))
        {
            data.push_back(input);
        }
    }
}

void words::import_from_file(std::string file_name)
{
    std::ifstream file(file_name);
    if (file.is_open())
    {
        std::string str = "     ";
        std::string current_line;
        while (file)
        {
            std::getline(file, current_line);
            for (size_t i = 0; i < 5; i++)
            {
                char c = current_line.at(i);
                str.at(i) = c;
            }
            add(str);
        }
    }
    else
    {
        std::cout << "Couldn't open file" << std::endl;
    }
    file.close();
}















//
//
//#include "words.h"
//#include <fstream>
//#include <iostream>
//#include <map>
//#include <random>
//#include <string>
//
//
//    void oldWords::add_word(std::string word)
//    {
//        list_.try_emplace(word, 0);
//    }
//
//    std::string oldWords::get_random()
//    {
//        std::random_device rand_dev;
//        std::mt19937 generator(rand_dev());
//        std::uniform_int_distribution<int> distribution(0, list_.size()-1);
//        int random_ranged_int = distribution(generator);
//        int i = 0;
//        for (const auto& item : list_)
//        {
//            if (random_ranged_int != i)
//            {
//                i++;
//                continue;
//            }
//            return item.first;
//        }
//    }
//
//    void oldWords::import_from_file(std::string filename)
//    {
//        std::ifstream file(filename);
//        if (file.is_open())
//        {
//            std::string word;
//            std::string current_line;
//            while (file)
//            {
//                std::getline(file, current_line);
//                for (char& c : current_line)
//                {
//                    c = std::tolower(c);
//                }
//                word = current_line.substr(0, 5);
//                list_.try_emplace(word);
//            }
//        }
//        else
//        {
//            std::cout << "Couldn't open file"<< std::endl;
//        }
//        file.close();
//    }
//
//    
//
