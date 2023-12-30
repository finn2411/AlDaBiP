/*
Finn Thierolf
Mobarak Almoustafa
21.12.2023
aufgabe5
*/

#include "QGramIndex.hpp"
#include <iostream>

QGramIndex::QGramIndex(const std::string& text, const uint8_t q)
: text(text), q(q) // fill up member
{
    // check exception
    if (q < 1 || q > 13) throw std::invalid_argument("Invalid q!");

    // create bitmask for rolling hash
    bitmask = ~0 << 2*q; // q=2: ....110000 => ~bitmask: ...001111

    // create dir
    dir.resize(std::pow(alphabet.size(), q), 0);

    // counting qgram occurances
    uint32_t currentHash = hash(text.substr(0, q));
    dir[currentHash]++;

    uint32_t temp;
    for (uint32_t position = q; position < text.size(); position++)
    {
        temp = currentHash;
        currentHash = hashNext(temp, text[position]);
        dir[currentHash]++;
    }

    for (uint32_t index = 1; index < dir.size(); index++)
    {
        dir[index] += dir[index-1];
    }

    // create suftab
    suftab.resize(text.size() - q + 1);

    currentHash = hash(text.substr(0, q));
    dir[currentHash]--;
    suftab[dir[currentHash]] = 0;

    for (uint32_t position = q; position < text.size(); position++)
    {
        temp = currentHash;
        currentHash = hashNext(temp, text[position]);
        dir[currentHash]--;
        suftab[dir[currentHash]] = position - 1;
    }


    for (uint32_t element : dir)
    {
        std::cout << element << "\n";
    }

    std::cout << "\n";

    for (uint32_t element : suftab)
    {
        std::cout << element << "\n";
    }
}


std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const
{
    std::vector<uint32_t> results{};
    uint32_t temp;

    if(h == dir.size() - 1)
    {
        if (dir[h] != text.size() - q + 1)
        {
            for(temp = dir[h]; temp < text.size() - q + 1; temp++)
            {
                if (temp != text.size() - q + 1) results.push_back(suftab[temp]);
                else break;
            }
        }
    }

    else if(dir[h] != dir[h+1])
    {
        for(temp = dir[h]; temp < text.size() - q + 1; temp++)
        {
            if (temp < dir[h+1]) results.push_back(suftab[temp]);
            else  break;
        }
    }

    std::cout << "\n";
    for (uint32_t element : results)
    {
        std::cout << element << "\n";
    }

    return results;
}


uint32_t QGramIndex::hash(const std::string& qgram) const
{
    // check exceptions
    if (qgram.size() != q) throw std::invalid_argument("Invalid q-gram. Wrong length!");

    // sum up hash values (based on horner scheme: 2*4^2+0*4^1+3*4^0 = (((2*4)+0)*4)+3
    uint32_t hashValue{};
    for (char base : qgram) // works only because 4 is 2^k (bits are binary)
    {
        hashValue <<= 2; // acts like *= 4 (=> binary: 2^2 = 4)
        hashValue |= alphabet.find(base); // acts like += (=> biggest ord() is < alphabet size in binary => 100 = 4 011 = 3)
    }

    return hashValue;
}


uint32_t QGramIndex::hashNext(const uint32_t prev_hash, const char new_pos) const
{
    uint32_t new_hash = prev_hash;

    // add new value
    new_hash <<= 2;
    new_hash |= alphabet.find(new_pos);

    new_hash &= ~bitmask; // cuts the first value in bits (ord() * 4^q)

    return new_hash;
}


const std::string& QGramIndex::getText() const { return text; }

uint8_t QGramIndex::getQ() const { return q; }