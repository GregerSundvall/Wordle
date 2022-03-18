#include <fstream>
#include <iostream>
#include <vector>
#include <string>


class words
{
    std::vector<std::string> data;

    bool already_exists(std::string input);
public:
    size_t size();

    int is_valid(std::string input);

    std::string to_upper(std::string input);

    void add(std::string input);

    void import_from_file(std::string file_name);

    std::string get_random();
};






/*
class Words{
    char** m_data = nullptr;
    size_t m_size = 0;
public:
    Words(){
    }

    ~Words(){
        delete[] m_data;
    }

    char get_random()
    {
        std::random_device rand_dev;
        std::mt19937 generator(rand_dev());
        std::uniform_int_distribution<int> distribution(0, m_size);
        int random_ranged_int = distribution(generator);
        std::cout << m_size << " " << random_ranged_int << std::endl;
        return *m_data[random_ranged_int];
    }

    void import_from_file(std::string filename)
    {
        std::ifstream file(filename);
        if (file.is_open())
        {
            char word[6]{};
            std::string current_line;
            while (file)
            {
                std::getline(file, current_line);
                for (size_t i = 0; i < 5; i++)
                {
                    char c = current_line[i];
                    c = std::tolower(c);
                    word[i] = c;
                }
                Add(word);
                std::cout << m_size << word << m_data[0] << std::endl;
            }
            std::cout << m_size << std::endl;
        }
        else
        {
            std::cout << "Couldn't open file"<< std::endl;
        }
        file.close();
    }

    void Add(std::string input)
    {
        char c_array[6];
        for (size_t i = 0; i < 6; i++)
        {
            c_array[i] = input[i];
        }
        Add(c_array);
    }

    void Add(const char* input)
    {
        char** newBlock = new char*[m_size + 1];

        if ( m_size == 0 ) 
        {
            newBlock[0] = (char*)input;
            m_size++;
        }
        else 
        {
            bool newWordIsAdded = false;
            for (size_t i = 0; i < m_size; i++)
            {
                if (!newWordIsAdded)
                {
                    for (size_t j = 0; j < 5; j++)
                    {
                        if (input[j] > m_data[i][j])
                        {
                            newBlock[i] = m_data[i];
                            break;
                        }
                        else if (input[j] < m_data[i][j])
                        {
                            newBlock[i] = (char*)input;
                            m_size++;
                            newWordIsAdded = true;
                            break;
                        }
                        else if (j == 4)
                        {
                            // Attempting to add duplicate, using "original".
                            newBlock[i] = m_data[i];
                            newWordIsAdded = true;
                            // deallocate stuff?
                            return;
                        }
                    }
                }
                else
                {
                    newBlock[i] = m_data[i - 1];
                }
            }

            if (!newWordIsAdded)
            {
                newBlock[m_size] = (char*)input;
                m_size++;
            }
        }
        
        delete[] m_data;
        m_data = newBlock;
        newBlock = nullptr;

    }

    //std::string& operator[](size_t index) { 
    //    if ( index >= m_size ) {
    //        assert(index < m_size, "Index out of bounds");
    //    }

    //    return m_data[index]; }
    const std::string operator[](size_t index) const { 
        //if ( index >= m_size ) {
        //    assert(index < m_size, "Index out of bounds");
        //}
        return std::string(m_data[index]); }
    
    size_t Size() const { return m_size; }
};
*/





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
