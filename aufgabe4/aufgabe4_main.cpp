/*
Mobarak Almoustafa
Finn Thierolf
06.12.23
aufgabe4
*/

#include "BLAST_Neighborhood.hpp"
#include <omp.h>

int main(int argc, const char* argv[])
{
    if (argc == 6)
    {
        BLAST_Neighborhood neighborhood;
        ScoreMatrix matrix;
        matrix.load(argv[2]);

        double start = omp_get_wtime();
        std::vector<NHResult> results = neighborhood.generateNeighborhood(argv[1], matrix, std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
        double end = omp_get_wtime();

        for (NHResult element : results)
        {
            std::cout << element.infix << ": ";
            for (std::pair tuple : element.neighbors)
            {
                std::cout << "(" << tuple.first << ", " << tuple.second << ") ";
            }
            std::cout << std::endl;
        }

        std::cout << end - start << "s" << std::endl;
    }

    else
    {
        throw std::logic_error("Input: ./aufgabe4_main sequence score_matrix word_size threshold threads");
    }
    
}