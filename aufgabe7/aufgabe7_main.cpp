/*
Maxim Daniel
FInn Thierolf
01.02.24
AlDaBi aufgabe7
*/


#include "PDA.hpp"
#include <iostream>
#include <algorithm>

int main(int argc, const char *argv[])
{
    if(argc==2)
    {
        //saving sequence in variable
        std::string seq= argv[1];

        //setting language as stabndard (HAIRPIN)
        PDA::Language l=PDA::Language::HAIRPIN;
        //checking if sequence has language BRACKETS
        if(seq.find('(')!=std::string::npos || seq.find(')')!=std::string::npos)
        {
            std::string tempSeq{};
            l=PDA::Language::BRACKETS;

            //filtering non-bracket symbols  + #include <algorithm>
            seq.erase(std::remove_if(seq.begin(), seq.end(), [](char c) {
                return c != '(' && c != ')';
            }), seq.end());
        }
        std::cout << seq <<std::endl;
        PDA automat(l);

        //putting '$' on the end of the string!
        seq+='$'; 
        PDA::State curState=PDA::State::IN_PROGRESS;

        for(char c : seq)
        {
            curState=automat.next(c);
            if(curState==PDA::State::FAIL) break;
        }
        
        if(curState==PDA::State::FAIL || curState==PDA::State::IN_PROGRESS)
        {
            std::cout << "FAIL\n";
            return 0;
        }
        else
        {
            std::cout << "ACCEPT\n";
            return 1;
        }
    }
    else throw std::logic_error("Expected different Commandline arguments! E.g.: ./aufgabe7_main gccgcaaggc");
}
