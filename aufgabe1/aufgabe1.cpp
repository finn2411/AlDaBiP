/* 
Mobarak ALmoustafa
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
    std::vector<size_t> hits{};
    size_t text_pos = 0;
    size_t maskpos = 0;
    if ((text.size() < pattern.size()) || text.empty() || pattern.empty()) // HIER (direkt abbrechen, falls pattern größer als Text (kann nicht passen), ODER falls Pattern oder text leer sind)
    {
        return {};
    }
    while (text_pos <= text.size() - Horspool::pattern.size())
    {
        maskpos = Horspool::pattern.size();
        while ((maskpos > 0 && (text[text_pos + maskpos - 1] == Horspool::pattern[maskpos - 1])) || (maskpos > 0 && text[text_pos + maskpos - 1] == '?') || (maskpos > 0 && Horspool::pattern[maskpos - 1] == '?')) // HIER (-1 hinzugefügt, aufgrund der Indizes)
        {
            maskpos--;
        }

        if (maskpos == 0) // HIER (kürzeres if, der Rest war unnötig)
        {
            hits.push_back(text_pos);
        }

        // std::cout << text_pos << std::endl;
        alignCheck_(text_pos);
        // std::cout << Horspool::getShift_(text[text_pos + Horspool::pattern.size() - 1]) << std::endl; 
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
        return Horspool::lookuptab.at(last_char);   // char in lookuptab
    }
    else
    {
        return Horspool::pattern.size();    // char not in lookuptab
    }
}