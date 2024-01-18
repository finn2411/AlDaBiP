/*
Maxim Daniel
Finn Thierolf
aufgabe 6: Aho-Corasick
*/ 

#include "ACTrie.hpp"
#include <stdexcept>
#include <iostream>
#include <algorithm>

ACTrie::ACTrie(const std::vector<std::string>& needles)
{
    ACNode root;
    root.index = 0;
    root.children = {};
    Trie.push_back(root);
    //Trie.

    for(std::string currentNeedle : needles)//Going through
    {
        uint32_t tempDepth = 0;
        std::cout << "loop 1" << "\n";
        uint32_t charPos = 0; // currentNeedle[charPos]
        for(uint32_t currentNode = 0; currentNode < Trie.size();)
        {
            // Problem: Wir vergleichen hier den aktuellen Character mit den Zahlen aus dem Children Vektor!!
            if ((std::find(Trie[currentNode].children.begin(), Trie[currentNode].children.end(), currentNeedle[charPos])) == Trie[currentNode].children.end())
            {
                std::cout << "if" << "\n";
                ACNode newNode;
                newNode.index = Trie.size();
                newNode.depth = tempDepth + 1;
                newNode.character = currentNeedle[charPos];
                Trie.emplace_back(newNode);
                Trie[currentNode].children.emplace_back(newNode.index.pos());
                currentNode = newNode.index.pos();
                charPos++;
                tempDepth++;
            }
            //break
            else
            {
                //charPos++;
                //tempDepth++;
                break;    
            }

            if (charPos == currentNeedle.size())
            {
                break;
            }
        }
    }

    for (int i = 0; i < Trie.size(); i++)
    {
        std::cout << Trie[i].character << "\n";
        std::cout << Trie[i].index.pos() <<"\n";
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

int main( ){
    std::vector<std::string> trie={"a","ab"};
    ACTrie test(trie);
    
}