/*
    Mobarak Almoustafa
    Finn Thierolf
    AlDaBi Praktikum
    Aufgabe 3 (main)
*/

#include <iostream>
#include "aufgabe2.hpp"

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cout << "suffix array: " << argv[0] << " <TEXT>" << std::endl;
        std::cout << "for binary search: " << argv[0] << " <TEXT> <SEARCHWORD1> <SEARCHWORD2> ..." << std::endl;
        return 1;
    }

    std::vector<uint32_t> suffixArray = {};

    if (argc < 3)
    {
        construct(suffixArray, argv[1]);
        for (const uint32_t element : suffixArray)
        {
            std::cout << element << std::endl;
        }
    }

}