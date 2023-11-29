/* 
Mobarak ALmoustafa
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include<iostream>
#include"Alignment.hpp"

int main()
{
    std::string a1;
    std::string gaps;
    std::string a2;
    Alignment test ("IMISSMISSISSIPPI", "MYMISSISAHIPPIE");
    test.compute(3, -4, -6);
    std::cout << test.getScore() << std::endl;
    test.getAlignment(a1, gaps, a2);
    std::cout << a1 << std::endl << gaps << std::endl << a2 << std::endl;
}