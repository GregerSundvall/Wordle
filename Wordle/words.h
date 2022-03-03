#pragma once
#include <map>
#include <string>



class words
{
    std::map<std::string, int> list_;
public:
    
    void add_word(std::string word);

    void import_from_file(std::string filename);

    std::string get_random();

    
};
