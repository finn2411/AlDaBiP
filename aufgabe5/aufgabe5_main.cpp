/*
Finn Thierolf
Mobarak Almoustafa
21.12.2023
aufgabe5
*/

#include "QGramIndex.hpp"
#include <fstream>

int main(int argc, const char* argv[])
{
    //std::string genome{};
    //std::ifstream file(argv[1]);
//
    //if(file.is_open()) std::getline(file, genome);
//
    //else throw std::invalid_argument("File not found!");
//
    //std::string query = argv[2];
    QGramIndex qind = QGramIndex("ACCGTCGTC", 2);
    qind.getHits(11);

    //file.close();
}