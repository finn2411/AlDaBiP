/*
    Mobarak Almoustafa
    Finn Thierolf
    AlDaBi Praktikum
    Aufgabe 3 (.cpp)
*/

#include <iostream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include "aufgabe2.hpp"


void construct(std::vector<uint32_t>& sa, const std::string& text)
{
    // reset suffix array to new length
    sa.clear();
    sa.resize(text.size());
    std::iota(sa.begin(), sa.end(), 0);
    
    // defining and executing sort function
    std::sort(sa.begin(), sa.end(), [&text] (const uint32_t &a, const uint32_t &b)
    {
        uint32_t index = 0;
        while (a + index < text.size() && b + index < text.size())
        {
            if (text[a + index] != text[b + index])
            {
                return text[a + index] < text[b + index];
            }
            ++index;
        }
        return a > b;
    });
}


void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits)
{
    hits.clear();
    // position of query in text
    uint32_t queryPos = text.rfind(query);
    // positon of query in suffix array
    uint32_t queryPosSa = std::distance(sa.begin(), std::find(sa.begin(), sa.end(), queryPos));

    // calculate Lp
    // create (L,R) pair
    std::pair<uint32_t, uint32_t> LR (0,sa.size()-1);
    uint32_t Lp = 0;

    if (queryPosSa <= 1)
    {
        Lp = 0;
    }

    else if (queryPosSa > sa.size())
    {
        Lp = sa.size() + 1;
    }

    else
    {
        while (LR.second - LR.first > 1)
        {
            uint32_t M = static_cast<uint32_t>(std::ceil(static_cast<double>(LR.second + LR.first) / 2));
            if (queryPosSa <= M)
            {
                LR.second = M;
            }
            else
            {
                LR.first = M;
            }
        }
        Lp = LR.second;
    }

    // create (L,R) pair
    LR = {0,sa.size()-1};
    uint32_t Rp = 0;

    if (queryPosSa > sa.size())
    {
        Rp = sa.size() + 1;
    }

    else
    {
        while (LR.second - LR.first > 1)
        {
            uint32_t M = static_cast<uint32_t>(std::ceil(static_cast<double>(LR.second + LR.first) / 2));
            if (queryPosSa >= M)
            {
                LR.second = M;
            }
            else
            {
                LR.first = M;
            }
        }
        Rp = LR.first;
    }


    for (size_t counter = Lp; counter < Rp; counter ++)
    {
        hits.push_back(sa[counter]);
        std::cout << sa[counter] << std::endl;
    }
}

int main()
{
    std::vector<uint32_t> suffixArray = {};
    std::vector<uint32_t> hits = {};

    construct(suffixArray, "banana");
    find("a", suffixArray, "banana", hits);
}