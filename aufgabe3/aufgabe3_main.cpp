/* 
Mobarak ALmoustafa
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include<iostream>
#include"Alignment.hpp"

int main(int argc, const char* argv[])
{
    if (argc == 3)
    {                   
        std::string a1;
        std::string gaps;
        std::string a2;
        Alignment align (argv[1], argv[2]);
        align.compute(3, -1, -2);
        align.getAlignment(a1, gaps, a2);
        std::cout << a1 << std::endl;
        std::cout << gaps << std::endl;
        std::cout << a2 << std::endl;
        std::cout << "score: " << align.getScore() << std::endl;
    }

    else if (argc == 6)
    {
        std::string a1;
        std::string gaps;
        std::string a2;
        Alignment align (argv[1], argv[2]);
        align.compute(std::stoi(argv[3]), std::stoi(argv[4]), std::stoi(argv[5]));
        align.getAlignment(a1, gaps, a2);
        std::cout << a1 << std::endl;
        std::cout << gaps << std::endl;
        std::cout << a2 << std::endl;
        std::cout << "score: " << align.getScore() << std::endl;
    }

    else
    {
        std::cout << "unexpected input"<< std::endl;
        return 1;
    }
    
}