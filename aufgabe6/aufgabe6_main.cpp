#include "ACTrie.hpp"
#include <iostream>
#include <stdexcept>
#include <omp.h>

int main(int argc, const char *argv[])
{
    if (argc > 2)
    {
        std::vector<std::string> needles{};
        for (int i = 2; i < argc; i++) needles.push_back(argv[i]);
        
        ACTrie trie(needles);

        trie.setQuery(argv[1]);
        std::cout << "Hits (position in query, pattern):\n";

        std::vector<Hit> hits;
        while (trie.next(hits))
        {
            for (Hit element : hits)
            {
                std::cout << "pos " << element.pos << ", " << needles[element.index] << "\n";
            }
        }
    }
    
    else throw std::logic_error("Usage: ./aufgabe6_main query needle1 needle2 ... ");
}