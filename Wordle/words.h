


class Word{
    char m_data[];

};



class Words{
    
public:
    Words(){
        ReAlloc(2);
    }


    void PushBack(const std::string& item){
        if ( m_size >= m_capacity ) {
            ReAlloc(m_capacity * 2);
        }
        m_data[m_size] = item;
        m_size++;
    }


    std::string& operator[](size_t index) { return m_data[index]; }
    std::string& operator[](size_t index) { return m_data[index]; }
    const std::string& operator[](size_t index) const { return m_data[index]; }
    
    size_t Size() const { return m_size; }
private:
    void ReAlloc(size_t newCapacity){
        std::string* newBlock = new std::string[newCapacity];

        if ( newCapacity < m_size ) {
            m_size = newCapacity;
        }

        for ( size_t i = 0; i < m_size; i++ ) {
            newBlock[i] = std::move(m_data[i]);
        }
        delete m_data;
        m_data = newBlock;
        m_capacity = newCapacity;
    }
    std::string* m_data = nullptr;
    size_t m_size;
    size_t m_capacity;
};




























//#pragma once
//#include <map>
//#include <string>



// Two instances of a custom ordered vector class. "Fresh" and "Stale".
// Custom array[5]
// Pick word from random index in fresh and then move it to stale.
// When 90% of items are false, set all back to true.
// Allocate for 10000 items first. If full, MOVE all to new "vector" 50% bigger.


// Previous thoughts:
// Vector-ish class with tuples of char[5] and a bool.
// Custom tuple class with char[5] and a bool will minimize allocation.
// Resizeable to be able to add more words.
// When 90% of items are false, set all back to true.
// Allocate for 10000 items first. If full, MOVE all to new "vector" 50% bigger.

// Trie is not an option since I want to get a random word.
// A class with two trie structures, one for "fresh" words and one for "stale".
// When a word is used, it's moved to stale.
// When the size of fresh words < 5% of stale everything goes back into fresh.


//class oldWords
//{
//    std::map<std::string, int> list_;
//public:
//    
//    void add_word(std::string word);
//
//    void import_from_file(std::string filename);
//
//    std::string get_random();
//
//    
//};
