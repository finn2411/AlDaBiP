/*
Finn Thierolf
Mobarak Almoustafa
21.12.2023
aufgabe5
*/

#include "QGramIndex.hpp"
#include <fstream>
#include <iostream>
#include <exception>

int main(int argc, const char* argv[])
{

    if (argc == 3)
    {
        std::string genome{};
        std::ifstream file(argv[1]);

        if(file.is_open()) std::getline(file, genome);

        else throw std::invalid_argument("File not found!");

        std::string query = argv[2];

        QGramIndex qind = QGramIndex(genome, query.size());
        std::vector<uint32_t> results = qind.getHits(qind.hash(query));
        

        std::cout << query << ": " ;
        for(uint32_t element : results)
        {
            std::cout << element << " ";
        }

        std::cout << "\n";
        //QGramIndex qind = QGramIndex("ACCGTCGTC", 2);
        //qind.getHits(11);

        file.close();
    }

    else
    {
        throw std::logic_error("Usage: ./aufgabe5 <GENOME_FILE> <QUERY>");    
    }
}