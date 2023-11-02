/*
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include "aufgabe1.h"
#include <iostream>

void Horspool::setPattern(const std::string& pat)
{
    Horspool::pattern = pat;

    uint32_t length = pat.size();
    for (uint32_t position = 0; position < (length-1); position++)
    {
        Horspool::lookuptab[pat[position]] = length - position - 1;
    }
}

const std::string& Horspool::getPattern() const
{
    return Horspool::pattern;
}

/*
std::vector<size_t> Horspool::getHits(const std::string& text) const
{
    std::vector<size_t> hits ={};
    std::string mask = {};
    uint32_t length = Horspool::pattern.size();


    for (uint32_t begin = 0; begin < text.size() - length; )
    {
        mask = text.substr(begin, begin+length);

        for (uint32_t currpos = length; currpos >= 0; )
        {
            if (currpos == 0 && mask[currpos] == Horspool::pattern[currpos])
            {
                Horspool::alignCheck_(currpos);
                hits.push_back(begin);
            }
            else if(mask[currpos] == Horspool::pattern[currpos])
            {
                Horspool::alignCheck_(currpos);
                currpos--;
            }
            else
            {
                Horspool::alignCheck_(currpos);
                begin += Horspool::getShift_(mask[currpos]);
                break;
            }
        }
    }
    return hits;
}
*/

std::vector<size_t> Horspool::getHits(const std::string& text) const {
    std::vector<size_t> hits;
    size_t text_len = text.size();
    size_t pattern_len = Horspool::pattern.size();

    size_t i = pattern_len - 1;
    while (i < text_len) {
        size_t k = 0;
        while (k < pattern_len && Horspool::pattern[pattern_len - 1 - k] == text[i - k]) {
            k++;
        }
        if (k == pattern_len) {
            hits.push_back(i - pattern_len + 1);
        }
        Horspool::alignCheck_(i);
        i += getShift_(text[i]);
    }

    return hits;
}

uint32_t Horspool::getShift_(const char last_char) const
{
    auto it = Horspool::lookuptab.find(last_char);
    if (it != Horspool::lookuptab.end())
    {
        return Horspool::lookuptab.at(last_char);
    }
    else
    {
        return Horspool::pattern.size();
    }
}