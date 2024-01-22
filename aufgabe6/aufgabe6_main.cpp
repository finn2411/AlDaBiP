#include "ACTrie.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>

int main(int argc, const char *argv[])
{
    std::vector<std::string> needles = {"a","ab","bab","bc","bca","c","caa","a"};
    ACTrie test(needles);

    //if(argc>2)
    //{
    //    ACTrie trie(const std::vector<std::string>& needles);
    //}
    //else throw std::logic_error("Command line does not have enough arguments!");
    
}