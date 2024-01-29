#include "ACTrie.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>

int main(int argc, const char *argv[])
{
    //std::vector<std::string> needles = {"A", "AB", "BAB", "BC", "BCA", "C", "CAA"};
    std::vector<std::string> needles = {"A","B","C","D","E", "AB", "ABC", "ABE", "BABC"};
    ACTrie test(needles);
    test.setQuery("BABCZBABC");
    //test.setQuery("NBCA");

    std::vector<Hit> hits{};

    bool nextBool = true;

    uint16_t counter = 1;

    while (nextBool == true)
    {
        std::cout << "next" << counter << ": \n";
        nextBool = test.next(hits);
        counter++;
        for (Hit element : hits)
        {
            std::cout << element.index << " " << element.pos << "\n";
        }
    }

    std::cout << test.getTree() << "\n";
    

    //if(argc>2)
    //{
    //    ACTrie trie(const std::vector<std::string>& needles);
    //}
    //else throw std::logic_error("Command line does not have enough arguments!");
    
}