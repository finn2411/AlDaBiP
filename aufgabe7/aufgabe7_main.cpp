/*
Maxim Daniel
FInn Thierolf
01.02.24
AlDaBi aufgabe7
*/


#include "PDA.hpp"
#include <iostream>

int main(int argc, const char *argv[])
{
    PDA::Language l = PDA::Language::HAIRPIN;
    PDA test(l);
    std::string query = "gccgcaaggc";

    PDA::State temp{};
    for (char character : query)
    {
        temp = test.next(character);
        //if(temp==PDA::State::IN_PROGRESS) std::cout<< "Progress\n";

        if (temp == PDA::State::FAIL)
        {
            break;
        }
    }

    test.reset();

    for (char character : query)
    {
        temp = test.next(character);
        if(temp==PDA::State::IN_PROGRESS) std::cout<< "Progress\n";

        if (temp == PDA::State::FAIL)
        {
            std::cout<< "BREAK!\n";
            break;
        }
    }
 
    if(temp == PDA::State::IN_PROGRESS) temp = test.next('$');

    if(temp == PDA::State::FAIL) std::cout << "Fail!!!\n";
    
    //else if(temp==PDA::State::SUCCESS) std::cout<< "SUCCESS\n";
}
