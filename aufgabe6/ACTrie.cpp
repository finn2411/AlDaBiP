/*
Maxim Daniel
Finn Thierolf
aufgabe 6: Aho-Corasick
*/

#include "ACTrie.hpp"
#include <stdexcept>
#include <iostream>
#include <queue>
#include <algorithm>
#include <cstdint>

ACTrie::ACTrie(const std::vector<std::string> &needles) : needles(needles)
{
    if (needles.empty() == true)
        throw std::logic_error("Input vector is empty!");

    // create root node
    ACNode root;
    root.index = 0;
    root.children = {};
    Trie.push_back(root);

    // create variables for later
    bool isChild = false;
    uint32_t tempDepth{};
    uint32_t charPos{};
    uint32_t maxDepth = 0; // for suffix links

    // ------------------- BUILD TRIE --------------------------------------------------------------------------------------

    // step through needles (keep track of needle indeces!)
    uint32_t needleIndex = 0;
    for (std::string currentNeedle : needles)
    {
        // reset tempDepth and charPos for every needle
        tempDepth = 0;
        charPos = 0;

        // step through tree to create new nodes (starting from root -> index 0)
        for (uint32_t currentNode = 0; currentNode < Trie.size();)
        {
            if (currentNeedle[charPos] < 41 || currentNeedle[charPos] > 90)
                throw std::logic_error("Character out of ranfe 'A' - 'Z'!");

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
                    if (maxDepth < tempDepth)
                    {
                        maxDepth = tempDepth;
                    }
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
                newNode.parent_link = currentNode;

                // if current char is last char of needle add needle index/indeces
                if (charPos == currentNeedle.size() - 1)
                {
                    newNode.needle_indices.emplace_back(needleIndex);
                }

                // add new node to Trie and to children of current node
                Trie.emplace_back(newNode);
                Trie[currentNode].children.emplace_back(newNode.index.pos());

                // set new node to current node
                currentNode = newNode.index.pos();

                // look at next char in needle
                charPos++;
                tempDepth++;
                if (maxDepth < tempDepth)
                {
                    maxDepth = tempDepth;
                }
            }

            // move to next needle if viewed at all chars
            if (charPos == currentNeedle.size())
                break;
        }

        // don't forget!!
        needleIndex++;
    }

    // ------------------- ADD SUFFIX-LINKS --------------------------------------------------------------------------------------

    // create queue (recycle tempDepth and use maxDepth)
    std::queue<ACNode> queue{};

    for (tempDepth = 1; tempDepth <= maxDepth; tempDepth++)
    {
        for (ACNode element : Trie)
        {
            if (tempDepth == element.depth)
            {
                queue.push(element);
            }
        }
    }

    // copy queue for output links
    std::queue<ACNode> outputQueue = queue;

    while (queue.empty() == false)
    {
        // nodes on level 1 always have root as suffix link
        if (queue.front().depth == 1)
        {
            Trie[queue.front().index.pos()].suffix_link = 0;
        }

        else
        {
            ACNode currentNode = Trie[Trie[queue.front().parent_link].suffix_link];
            do
            {
                for (uint32_t nodeIndex : currentNode.children)
                {
                    if (Trie[nodeIndex].character == queue.front().character)
                    {
                        Trie[queue.front().index.pos()].suffix_link = nodeIndex;
                    }
                }

                currentNode = Trie[currentNode.suffix_link];
            } while ((currentNode.index.pos() != 0) || (queue.front().suffix_link != 0));

            // last round with roots children
            if (Trie[queue.front().index.pos()].suffix_link == 0 && queue.front().depth != 1)
            {
                for (uint32_t nodeIndex : currentNode.children)
                {
                    if (Trie[nodeIndex].character == queue.front().character)
                    {
                        Trie[queue.front().index.pos()].suffix_link = nodeIndex;
                    }
                }
            }
        }

        queue.pop();
    }

    // ------------------- ADD OUTPUT-LINKS --------------------------------------------------------------------------------------

    // step through queue
    while (outputQueue.empty() == false)
    {
        // skip nodes with depth 1 and 0 (no output links)
        if (outputQueue.front().depth > 1)
        {
            // set currentNode to suffix linked node of first element in queue
            ACNode currentNode = Trie[Trie[outputQueue.front().index.pos()].suffix_link];

            // follow the suffix links until at root or until output link is found
            while (currentNode.index.pos() != 0)
            {
                // to check if end node see if needle_indeces is empty
                if (currentNode.needle_indices.empty() == false)
                {
                    Trie[outputQueue.front().index.pos()].output_link = currentNode.index.pos();
                    break;
                }
                currentNode = Trie[currentNode.suffix_link];
            }
        }
        outputQueue.pop();
    }
}

void ACTrie::setQuery(const std::string &haystack)
{
    // set query and reset current node
    query = haystack;
    curTrieNode = Trie[0];
    curHayPos = 0;
    tempPos = 0;
}

bool ACTrie::next(std::vector<Hit> &hits)
{
    hits.clear();

    bool hit = false;
    bool isChild = false;

    while (hit == false)
    {
        if (tempPos >= query.length())
            return false;
        if (curTrieNode.children.empty())
        {
            curTrieNode = Trie[0];
            curHayPos = tempPos;
            // curHayPos++;
            // tempPos=curHayPos;
        }

        // std::cout << "curHayPos: " << curHayPos << "; tempPos:  " << tempPos << "\n";
        // std::cout << "Vergleich: " << curTrieNode.character<<".children"  << " - " << query[tempPos] << tempPos << "\n";
        for (uint32_t child : curTrieNode.children)
        {
            if (query[tempPos] == Trie[child].character)
            {
                isChild = true;

                if (!Trie[child].needle_indices.empty())
                {
                    // std::cout << "Hit!\n";
                    hit = true;
                    for (uint32_t index : Trie[child].needle_indices)
                    {
                        if(curHayPos + Trie[child].depth == query.size() - 1)
                        {
                            hits.emplace_back(Hit(index, curHayPos + 1 ));    
                        }
                        else
                        {
                            hits.emplace_back(Hit(index, curHayPos));
                        }
                        // std::cout << "curHayPos: "<<curHayPos<<"\n";
                    }
                    uint32_t curOutputlink = Trie[child].output_link;
                    while (curOutputlink != 0)
                    {
                        for (uint32_t index : Trie[curOutputlink].needle_indices)
                        {
                            hits.emplace_back(Hit(index, curHayPos + (Trie[child].depth - Trie[curOutputlink].depth)));
                            // std::cout << "tempPos: "<<tempPos<<"\n";
                        }

                        curOutputlink = Trie[curOutputlink].output_link;
                    }

                    tempPos++;
                    curTrieNode = Trie[child];
                    return true;
                }

                else
                {
                    uint32_t curOutputlink = Trie[child].output_link;
                    while (curOutputlink != 0)
                    {
                        for (uint32_t index : Trie[curOutputlink].needle_indices)
                        {
                            hits.emplace_back(Hit(index, curHayPos + (Trie[child].depth - Trie[curOutputlink].depth)));
                            // std::cout << "tempPos: "<<tempPos<<"\n";
                        }
                        curOutputlink = Trie[curOutputlink].output_link;
                    }

                    tempPos++;
                    curTrieNode = Trie[child];
                    if (curTrieNode.output_link != 0)
                    {

                        return true;
                    }
                    break;
                }
            }
        }

        if (!isChild)
        {
            curHayPos++;
            tempPos++;
            if (!curTrieNode.index.pos() == 0)
            {
                curHayPos++;
                curTrieNode = Trie[curTrieNode.suffix_link];
            }
        }
        isChild = false;
    }
}

std::string ACTrie::getTree() const
{
    // Start DFS from the root node
    return getSubtree(0);
}

std::string ACTrie::getSubtree(uint32_t nodeIndex) const
{
    if (nodeIndex >= Trie.size()) {
        // Handle the case where the index is out of bounds...
        return "";
    }

    const ACNode &node = Trie[nodeIndex];

    std::string result;
    result += node.character;

    // Sort children nodes in alphabetical order
    std::vector<uint32_t> sortedChildren = node.children;
    std::sort(sortedChildren.begin(), sortedChildren.end(), [this](uint32_t a, uint32_t b)
              { return Trie[a].character < Trie[b].character; });

    // Append string representation of each child subtree
    for (uint32_t childIndex : sortedChildren)
    {
        if (childIndex < Trie.size() && Trie[childIndex].depth > node.depth)
        // Only consider edges which increase in depth
        {
            result += "(" + getSubtree(childIndex) + ")";
        }
    }

    return result;
}