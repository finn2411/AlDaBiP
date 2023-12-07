/*
Mobarak Almoustafa
Finn Thierolf
06.12.23
aufgabe4
*/

#include "BLAST_Neighborhood.hpp"
#include <iostream>
#include <queue>


std::vector<std::string> getPermutations(std::string str, int length) 
{
    std::queue<std::string> q;
    std::vector<std::string> result;

    // a queue is filled up with all amino acids
    for (char acid : str) 
    {
        q.push(std::string(1, acid));
    }

    std::string perm;

    // as long as the que isn't empty add first acid to a permutation in progress
    while (!q.empty()) 
    {
        perm = q.front();
        q.pop();

        // if current permutation has desired length put in result vector
        if (perm.size() == length) 
        {
            result.push_back(perm);
        } 

        // if not add each acid to current permutation an push the new string into the queue
        else 
        {
            for (char acid : str) 
            {
                q.push(perm + acid);
            }
        }
    }


    // example: string: abcd length: 3
    //          1. q =  a, b, c, d 
    //          2. q = aa, ab, ac, ad, ba, bb, bc, bd
    //          3. ...
    return result;
}


std::vector<NHResult> BLAST_Neighborhood::generateNeighborhood(const std::string& query,
                                                               const ScoreMatrix& matrix,
                                                               const int word_size,
                                                               const int score_threshold,
                                                               const int threads)
{
    // create and set up results vector
    std::vector<NHResult> results{};


    std::string alphabet = "ARNDCQEGHILKMFPSTWYV";
    std::vector<std::string> permutations = getPermutations(alphabet, word_size);
    for (size_t i = 0; i <= query.size() - word_size; i++)
    {
        results.emplace_back();
        results[i].infix = query.substr(i, word_size);

        int currentScore;
        for(std::string word : permutations)
        {
            currentScore = 0;
            for (size_t k = 0; k < word.size(); k++)
            {
                currentScore += matrix.score(results[i].infix[k], word[k]);
            }
            
            if (currentScore >= score_threshold)
            {
                results[i].neighbors.emplace_back(std::make_pair(word, currentScore));
            }
        }
    }



    // tests

    for (NHResult element : results)
    {
        std::cout << element.infix << std::endl;
        for (std::pair tuple : element.neighbors)
        {
            std::cout << "(" << tuple.first << ", " << tuple.second << ") ";
        }
        std::cout << std::endl;
    }

    return results;
}


