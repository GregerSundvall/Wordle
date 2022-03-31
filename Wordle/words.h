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

// feedback: while I see the effort to add a custom words storage I'm not sure I fully understand the intent behind it.
// You use a wrapper around the std::map, however it doesn't seem like you ever set or get values(ints) in the map but only use keys(strings).
// Moreover get_random() has to iterate the map which is far from ideal(see my comment in that function)

class words
{
    std::map<std::string, int> list_;
public:
    
    void add_word(std::string word); // feedback - argument could be std::string& instead to avoid copying

    void import_from_file(std::string filename); // feedback - same here

    std::string get_random();

    
};
