/*
Maxim Daniel
Finn Thierolf
aufgabe 6: Aho-Corasick
*/ 

#include "ACTrie.hpp"
#include <stdexcept>
#include <iostream>

ACTrie::ACTrie(const std::vector<std::string>& needles)
{
    // create root node
    ACNode root;
    root.index = 0;
    root.children = {};
    Trie.push_back(root);

    // create variables for later
    bool isChild = false;
    uint32_t tempDepth{};
    uint32_t charPos{};

    // step through needles (keep track of needle indeces!)
    uint32_t needleIndex = 0;
    for(std::string currentNeedle : needles) 
    {
        // reset tempDepth and charPos for every needle 
        tempDepth = 0;
        charPos = 0;

        // step through tree to create new nodes (starting from root -> index 0)
        for(uint32_t currentNode = 0; currentNode < Trie.size();)
        {
            // reset isChild for every node looked at
            isChild = false;

            // go through children of current node to see if current char is one of them
            for (uint32_t element : Trie[currentNode].children)
            {
                // if current char is one of the children go to its node and look at next char in needle
                if (Trie[element].character == currentNeedle[charPos])
                {
                    isChild = true;
                    currentNode = element;

                    // if current char is last char of needle add needle index/indeces
                    if (charPos == currentNeedle.size() - 1)
                    {
                        Trie[currentNode].needle_indices.emplace_back(needleIndex);
                    }
                    
                    charPos++;
                    tempDepth++;
                    break;
                }
            }

            // if current char is no child of current node create new node
            if (isChild == false)
            {
                ACNode newNode;
                newNode.index = Trie.size();
                newNode.depth = tempDepth + 1;
                newNode.character = currentNeedle[charPos];

                // if current char is last char of needle add needle index/indeces
                if (charPos == currentNeedle.size() - 1)
                {
                    newNode.needle_indices.emplace_back(needleIndex);
                }

                // add new node to Trie and to children of current node
                Trie.emplace_back(newNode);
                Trie[currentNode].children.emplace_back(newNode.index.pos());

                currentNode = newNode.index.pos();


                // look at next char in needle
                charPos++;
                tempDepth++;
            }

            // move to next needle if viewed at all chars
            if (charPos == currentNeedle.size()) break;
        }

        // don't forget!!
        needleIndex++;
    }

    for (int i = 0; i < Trie.size(); i++)
    {
        std::cout << Trie[i].character << " ";
    }

    std::cout << "\n";

    for (int i = 0; i < Trie.size(); i++)
    {
        std::cout << Trie[i].index.pos() <<" ";
    }

    std::cout << "\n";

    for (int i = 0; i < Trie.size(); i++)
    {
        std::cout << Trie[i].depth <<" ";
    }

    std::cout << "\n";

    for (int i = 0; i < Trie.size(); i++)
    {
        for (int j = 0; j < Trie[i].needle_indices.size(); j++)
        {
            std::cout << Trie[i].needle_indices[j]<< ",";
        }

        if (Trie[i].needle_indices.empty())
        {
            std::cout << 'X';
        }

        std::cout << " ";
    }
    
}


//void ACTrie::setQuery(const std::string& haystack)
//{
//
//}
//
//bool ACTrie::next(std::vector<Hit>& hits)
//{
//
//}
//
//std::string ACTrie::getTree() const
//{
//
//}

//int main( )
//{
//    std::vector<std::string> trie={"a","ab","bab","bc","bca","c","caa"};
//    ACTrie test(trie);
//    
//}