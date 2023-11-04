/*
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include "aufgabe1.h"
#include <iostream>

void Horspool::setPattern(const std::string &pat)
{
    Horspool::pattern = pat;

    uint32_t length = pat.size();
    for (uint32_t position = 0; position < (length - 1); position++)
    {
        Horspool::lookuptab[pat[position]] = length - position - 1;
    }
}

const std::string &Horspool::getPattern() const
{
    return Horspool::pattern;
}

std::vector<size_t> Horspool::getHits(const std::string &text) const
{
    std::vector<size_t> hits;
    size_t text_pos = 0;
    while (text_pos <= text.size() - Horspool::pattern.size())
    {
        size_t maskpos = Horspool::pattern.size() - 1;
        while ((maskpos > 0 && text[text_pos + maskpos] == Horspool::pattern[maskpos]) || (maskpos > 0 && Horspool::pattern[maskpos] == '?') || (maskpos > 0 && text[text_pos + maskpos] == '?'))
        {
            maskpos--;
        }

        if ((maskpos == 0 && text[text_pos] == Horspool::pattern[0]) || (maskpos == 0 && Horspool::pattern[maskpos] == '?') || (maskpos == 0 && text[text_pos + maskpos] == '?'))
        {
            hits.push_back(text_pos);
        }

        Horspool::alignCheck_(text_pos);
        text_pos += Horspool::getShift_(text[text_pos + Horspool::pattern.size() - 1]);
    }
    return hits;
}

uint32_t Horspool::getShift_(const char last_char) const
{
    if (Horspool::pattern.back() == '?')
    {
        return 1;
    }
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