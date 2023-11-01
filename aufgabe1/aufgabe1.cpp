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

    uint8_t length = pat.size();
    for (uint8_t position = 0; position < (length-1); position++)
    {
        Horspool::lookuptab[pat[position]] = length - position;
    }

    if (pat[length] != pat[length-1])
    {
        Horspool::lookuptab.erase(length);
    }
    Horspool::lookuptab['*'] = length;
}

const std::string& Horspool::getPattern() const
{
    return Horspool::pattern;
}

std::vector<size_t> Horspool::getHits(const std::string& text) const
{
    std::string mask = {};
    uint8_t length = Horspool::pattern.size();
    for (uint8_t begin = 0; begin < text.size() - length; )
    {
        mask = text.substr(begin, begin+length);
    }
}