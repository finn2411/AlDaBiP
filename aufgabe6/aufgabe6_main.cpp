#include "ACTrie.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>

int main(int argc, const char *argv[])
{
    std::vector<std::string> needles = {"A","AB","BAB","BC","BCA","C","CAA","A"};
    ACTrie test(needles);
    test.setQuery("NBCA");

    std::vector<Hit> hits{};

    bool nextBool = true;

    while (nextBool == true)
    {
        nextBool = test.next(hits);
    }

    for(Hit element : hits)
    {
        std::cout << element.index << " " << element.pos << "\n";
    }
    

    //if(argc>2)
    //{
    //    ACTrie trie(const std::vector<std::string>& needles);
    //}
    //else throw std::logic_error("Command line does not have enough arguments!");
    
}