

#include "words.h"
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <string>


    void words::add_word(std::string word) // feedback: this function seems never called
    {
        list_.try_emplace(word, 0);
    }

    std::string words::get_random()
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distribution(0, list_.size()-1);
        int random_ranged_int = distribution(generator);
        int i = 0;
        for (const auto& item : list_) // feedback: iterating the map element-by-element is an expensive operation because of cache misses since 
                                       // elements are not placed in a single-allocated block of memory. In practice it can be orders of magnitude slower
                                       // than iterating a vector, which has monolitic memory layout and fits in cache lines nicely.
        {
            if (random_ranged_int != i)
            {
                i++;
                continue;
            }
            return item.first;
        }
    }

    void words::import_from_file(std::string filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            std::string word;
            std::string current_line;
            while (file)
            {
                std::getline(file, current_line);
                for (char& c : current_line)
                {
                    c = std::tolower(c);
                }
                word = current_line.substr(0, 5);
                list_.try_emplace(word);
            }
        }
        else
        {
            std::cout << "Couldn't open file"<< std::endl;
        }
        file.close();
    }

    

