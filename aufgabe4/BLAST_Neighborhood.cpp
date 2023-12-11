/*
Mobarak Almoustafa
Finn Thierolf
06.12.23
aufgabe4
*/

#include "BLAST_Neighborhood.hpp"
#include <iostream>
#include <queue>
#include <omp.h>
#include <stdexcept>

std::vector<std::string> getPermutations(std::string str, size_t length)
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

    // example: string: abcd; length: 3
    //          1. q =  a, b, c, d
    //          2. q = aa, ab, ac, ad, ba, bb, bc, bd
    //          3. ...
    return result;
}

std::vector<NHResult> BLAST_Neighborhood::generateNeighborhood(const std::string &query,
                                                               const ScoreMatrix &matrix,
                                                               const int word_size,
                                                               const int score_threshold,
                                                               const int threads)
{
    // make sure that threads is positive
    if (threads < 1)
        throw std::logic_error("Invalid number of threads!");

    // set number of threads to operate on
    omp_set_num_threads(threads);

    // create and set up results vector
    std::vector<NHResult> results{};

    // to prevent warning int compared with uint
    int qSize = query.size();

    // return empty vector if word size is greater than query size
    if (qSize < word_size)
    {
        return results;
    }

    // resize results vector
    results.resize(query.size() - word_size + 1);

    // aminoacid alphabet
    std::string alphabet = "ACDEFGHIKLMNPQRSTVWY";

    // calculate all posible word_size permutations of the alphabet using getPermutations
    std::vector<std::string> permutations = getPermutations(alphabet, word_size);

    // fill up results vector
    #pragma omp parallel for
    for (size_t i = 0; i <= query.size() - word_size; i++)
    {
        // add new infix
        results[i].infix = query.substr(i, word_size);

        // calculate neighborhood of current infix
        int currentScore;
        for (std::string word : permutations)
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

    return results;
}