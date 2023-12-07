/*
Mobarak Almoustafa
Finn Thierolf
06.12.23
aufgabe4
*/

#include "BLAST_Neighborhood.hpp"

int main(int argc, const char* argv[])
{
    BLAST_Neighborhood test;
    ScoreMatrix matrix;
    matrix.load("blosum62");
    test.generateNeighborhood("AAHILNMY", matrix, 3, 14, 1);
}