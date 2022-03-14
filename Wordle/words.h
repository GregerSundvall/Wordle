#include <assert.h>


//class Word{
//    char m_data[];
//
//};



class Words{
    
public:
    Words(){
        ReAlloc(2);
    }

    ~Words(){
        delete[] m_data;
    }




    void Add(std::string&& input)
    {
        char word[5];
        for (size_t i = 0; i < 5; i++)
        {
            word[i] = input[i];
        }

        std::string* newBlock;

        if ( m_size < m_capacity ) 
        {
            newBlock = new std::string[m_capacity];
        }
        else 
        {
            m_capacity *= 2;
            newBlock = new std::string[m_capacity];
        }

        if ( m_size == 0 ) 
        {
            newBlock[0] = std::move(input);
            m_size++;
            std::cout << "first added" << std::endl;
        }
        else 
        {
            for ( size_t i = 0; i < m_size; i++ ) 
            {
                std::cout << "Word for loop iteration " << i << std::endl;
                for ( size_t j = 0; j < 4; j++ ) 
                {
                    std::cout << "Char for loop iteration " << j << std::endl;
                    std::cout << "item[j] is " << input[j] << std::endl;

                    if ( input[j] > m_data[i][j])
                    {
                        //std::cout << item << std::endl;
                        newBlock[i] = std::move(m_data[i]);
                        break;
                    }
                    else if ( input[j]  < m_data[i][j])
                    {
                        //std::cout << item << std::endl;
                        newBlock[i] = std::move(input);
                        m_size++;
                        break;
                    }
                    else if (j == 4)
                    {
                        // Attempting to add duplicate, using "original".
                        newBlock[i] = std::move(m_data[i]);
                    }
                }
            
            }
        }
        

        delete[] m_data;
        m_data = newBlock;
    }

    std::string& operator[](size_t index) { 
        if ( index >= m_size ) {
            assert(index < m_size, "Index out of bounds");
        }
        return m_data[index]; }
    const std::string& operator[](size_t index) const { 
        if ( index >= m_size ) {
            assert(index < m_size, "Index out of bounds");
        }
        return m_data[index]; }
    
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
        delete[] m_data;
        m_data = newBlock;
        m_capacity = newCapacity;
    }
    std::string* m_data = nullptr;
    size_t m_size = 0;
    size_t m_capacity = 0;
};


    //void PopBack(){
    //    if ( m_size > 0 ) {
    //        m_size--;
    //        m_data[m_size].~basic_string();
    //    }
    //}
    //void Clear(){
    //    for ( size_t i = 0; i < m_size; i++ ) {
    //        m_data[i].~basic_string();
    //    }
    //    m_size = 0;
    //}

    //void PushBack(const std::string& item){
    //    if ( m_size >= m_capacity ) {
    //        ReAlloc(m_capacity * 2);
    //    }
    //    m_data[m_size] = item;
    //    m_size++;
    //}
    //void PushBack(std::string&& item){
    //    if ( m_size >= m_capacity ) {
    //        ReAlloc(m_capacity * 2);
    //    }
    //    m_data[m_size] = std::move(item);
    //    m_size++;
    //}
























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
