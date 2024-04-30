/*
    Mobarak Almoustafa
    Finn Thierolf
    AlDaBi Praktikum
    Aufgabe 3 (main)
*/

#include <iostream>
#include <algorithm>
#include "aufgabe2.hpp"

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "unexpected input"<< std::endl;
        return 1;
    }

    std::vector<uint32_t> suffixArray = {};
    std::vector<uint32_t> hits = {};

    construct(suffixArray, argv[1]);

    if (argc < 3)
    {
        for (const uint32_t element : suffixArray)
        {
            std::cout << element << std::endl;
        }
    }

    else
    {
        for (int32_t counter = 2; counter < argc; counter++)
        {
            std::cout << argv[counter] << ": ";
            find(argv[counter], suffixArray, argv[1], hits);
            for (uint32_t element : hits)
            {
                std::cout << element << " ";
            }
            std::cout << std::endl;
        }
    }
}