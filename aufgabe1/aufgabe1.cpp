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


std::vector<size_t> Horspool::getHits(const std::string& text) const
{
    std::vector<size_t> hits;
    hits.resize(0);
    size_t pos = 0;
    while (pos <= text.size() - Horspool::pattern.size())
    {
        size_t maskpos = Horspool::pattern.size() - 1;
        while (maskpos > 0 && text[pos+maskpos] == Horspool::pattern[maskpos])
        {
            Horspool::alignCheck_(pos+maskpos);
            maskpos--;
        }
        
        if (maskpos == 0)
        {
            Horspool::alignCheck_(pos);
            hits.push_back(pos+1);
        }

        pos += Horspool::getShift_(text[pos+Horspool::pattern.size()]);
    }
    return hits;
}


/*
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
*/
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