#pragma once
#include <map>
#include <string>


class word {
    char word[5];
    bool used;
};


class word_list {

};

// Vector-ish class with tuples of char[5] and a bool.
// Custom tuple class with char[5] and a bool will minimize allocation.
// Resizeable to be able to add more words.
// When 90% of items are false, set all back to true.
// Allocate for 10000 items first. If full, MOVE all to new "vector" 50% bigger.



class words
{
    std::map<std::string, int> list_;
public:
    
    void add_word(std::string word);

    void import_from_file(std::string filename);

    std::string get_random();

    
};
