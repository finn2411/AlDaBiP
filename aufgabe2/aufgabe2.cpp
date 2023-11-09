/*
    Mobarak Almoustafa
    Finn Thierolf
    AlDaBi Praktikum
    Aufgabe 3 (.cpp)
*/

#include <iostream>
#include <algorithm>
#include <numeric>
#include "aufgabe2.hpp"


void construct(std::vector<uint32_t>& sa, const std::string& text)
{
    // reset suffix array to new length
    sa.clear();
    sa.resize(text.size());
    std::iota(sa.begin(), sa.end(), 0);
    
    // defining and executing sort function
    std::sort(sa.begin(), sa.end(), [text] (const uint32_t &a, const uint32_t &b)
    {
        // if first letter of a is "smaller" or, if the first letters are the same, if the substring
        // from this position on is shorter a is "smaller" than b
        if (text[a] < text[b] || (text[a] == text[b] && a > b))
        {
            return true;
        }
        else
        {
            return false;
        }
    });
}