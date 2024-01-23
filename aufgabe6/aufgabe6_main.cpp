#include "ACTrie.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>

int main(int argc, const char *argv[])
{
    std::vector<std::string> needles = {"A","AB","BAB","BC","BCA","C","CAA","A"};
    ACTrie test(needles);

    //if(argc>2)
    //{
    //    ACTrie trie(const std::vector<std::string>& needles);
    //}
    //else throw std::logic_error("Command line does not have enough arguments!");
    
}