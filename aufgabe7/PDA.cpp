/*
Maxim Daniel
FInn Thierolf
01.02.24
AlDaBi aufgabe7
*/

#include "PDA.hpp"
#include <iostream>
#include <algorithm>

PDA::PDA(const Language l)
{
    if (l == Language::HAIRPIN)
    {
        for(char counter = '0'; counter <= '2'; counter++)
        {
            // attention states are in reverse order!!!
            std::string temp{};
            temp += counter+1;
            grammar.emplace_back(Rule(counter, 'a', 'u' + temp)); // temp + 'u' a1u (original state) (reversed for next(char))
            grammar.emplace_back(Rule(counter, 'c', 'g' + temp)); // temp + 'g' a1g (original state)
            grammar.emplace_back(Rule(counter, 'g', 'c' + temp));
            grammar.emplace_back(Rule(counter, 'u', 'a' + temp));
        }

        grammar.emplace_back(Rule('3', 'g', "a4"));

        grammar.emplace_back(Rule('4', 'a', "a"));
        grammar.emplace_back(Rule('4', 'c', "a"));

        alphabet="acgu";
    }

    stack.push('0'); // Start (S) für stack!
    
}


PDA::State PDA::next(const char a)
{
    //std::string alphabet ="acgt$";
    //if(!alphabet.find(a)) return State::FAIL;
    //if(a != 'a' && a != 'c' && a != 'g' && a != 'u' && a != '$') return State::FAIL;
    if(alphabet.find(a)==std::string::npos && a !='$') return State::FAIL;


    curNT.clear();

    if (a == '$' && stack.empty())
    {
        return State::SUCCESS;
    }

    else if (a == '$')
    {
        return State::FAIL;
    }

    else if (stack.empty())
    {
                return State::FAIL;
    }
    
    

    /*if(stack.top() == 'a' || stack.top() == 'c' || stack.top() == 'g' || stack.top() == 'u')
    {

        if(a == stack.top()) curState = State::IN_PROGRESS;

        else curState = State::FAIL;

        stack.pop();
    }*/
    //wenn std::string .find() char/substring gefunden hat dann ist der rückgabewert != std::string::npos
    if(alphabet.find(stack.top())!=std::string::npos)
    {
        if(a == stack.top()) curState = State::IN_PROGRESS;

        else curState = State::FAIL;

        stack.pop();  
    }


    else
    {
        std::copy_if(grammar.begin(), grammar.end(), std::back_inserter(curNT), [this](Rule x)
        { return x.nonTerminal == stack.top(); });
        
        stack.pop();

        for(Rule element : curNT)
        {
            if(element.input == a)
            {
                for(char character : element.state)
                {
                    stack.push(character);
                }
                curState = State::IN_PROGRESS;
                break;
            }
        }
    }

    return curState;
}


void PDA::reset()
{
    //std::stack<char>().swap(stack);
    while(!stack.empty())
    {
        stack.pop();
    }
    stack.push('0');

    PDA::curState=State::IN_PROGRESS;

}