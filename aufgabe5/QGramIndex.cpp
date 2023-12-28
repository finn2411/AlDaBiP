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
    std::vector<uint32_t> dir(std::pow(alphabet.size(), q), 0);

    // first hash value
    uint32_t currentHash = hash(text.substr(0, q));
    dir[currentHash]++;

    // other hash values with rolling hash
    uint32_t temp;
    for (uint32_t position = q; position < text.size(); position++)
    {
        temp = currentHash;
        currentHash = hashNext(temp, text[position]);
        dir[currentHash]++;
    }

    for (uint32_t element : dir)
    {
        std::cout << element << "\n";
    }
}


std::vector<uint32_t> QGramIndex::getHits(const uint32_t h) const
{

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