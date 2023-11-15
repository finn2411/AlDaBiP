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
            if (a + index >= text.size() || b + index >= text.size())
            {
                break;
            }
        }
        return a > b;
    });
}


void find(const std::string& query, const std::vector<uint32_t>& sa, const std::string& text, std::vector<uint32_t>& hits)
{
    // falls query leer
    if (query == "")
    {
        return;
    }

    // sonst:
    hits.clear();
    uint32_t l = 0;
    uint32_t r = 0;
    uint32_t M = 0;
    uint32_t equal = 0; // zählt gleiche Stellen für mlr
    std::pair<uint32_t, uint32_t> LR (0,sa.size()-1);

    // lambda function to compare strings
    auto isSmalEq = [query, text] (const uint32_t& saPos, const uint32_t& mlr, uint32_t& equal)
    {
        // reset equal
        equal = 0;
        for (uint32_t counter = saPos+mlr; counter-saPos < query.size() && counter < text.size();)
        {
            if (query[counter-saPos] == text[counter])
            {
                counter ++;
                equal++;
            }
            else
            {
                return query[counter-saPos] <= text[counter];
            }
        }
        return true;
    };

    auto isGreEq = [query, text] (const uint32_t& saPos, const uint32_t& mlr, uint32_t& equal)
    {
        // reset equal
        equal = 0;
        for (uint32_t counter = saPos+mlr; counter-saPos < query.size() && counter < text.size();)
        {
            if (query[counter-saPos] == text[counter])
            {
                counter ++;
                equal++;
            }
            else
            {
                return query[counter-saPos] >= text[counter];
            }
        }
        return true;
    };

    // calculate Lp
    uint32_t Lp = 0;

    if (isSmalEq(sa[0], 0, equal))
    {
        Lp = 0;
    }

    else if (!isSmalEq(sa[sa.size()-1], std::min(l,r), equal))
    {
        Lp = sa.size();
    }

    else
    {
        while(LR.second - LR.first > 1)
        {
            M = static_cast<uint32_t>(std::ceil(static_cast<double>(LR.second + LR.first) / 2));
            if (isSmalEq(sa[M], std::min(l,r), equal))
            {
                LR.second = M;
                r = equal;
            }
            else
            {
                LR.first = M;
                l = equal;
            }
        }
        Lp = LR.second;
    }

    // reset values
    l = 0;
    r = 0;
    LR = {0,sa.size()-1};

    // calculate Rp
    uint32_t Rp = 0;

    if (isGreEq(sa[sa.size()-1], 0, equal))
    {
        Rp = sa.size() - 1;
    }

    else if (!isGreEq(sa[0], std::min(l,r), equal))
    {
        Rp = 0;
    }

    else
    {
        while(LR.second - LR.first > 1)
        {
            M = static_cast<uint32_t>(std::ceil(static_cast<double>(LR.second + LR.first) / 2));
            if (isGreEq(sa[M], std::min(l,r), equal))
            {
                LR.first = M;
                l = equal;
            }
            else
            {
                LR.second = M;
                r = equal;
            }
        }
        Rp = LR.first;
    }



    for (uint32_t counter = Lp; counter <= Rp; counter++)
    {
        hits.push_back(sa[counter]);
    }
    std::sort(hits.begin(), hits.end());
}

