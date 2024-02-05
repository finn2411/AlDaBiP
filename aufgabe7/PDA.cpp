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
        for (char counter = '0'; counter <= '2'; counter++)
        {
            // attention states are in reverse order!!!
            std::string temp{};
            temp += counter + 1;
            grammar.emplace_back(Rule(counter, 'a', 'u' + temp)); // temp + 'u' a1u (original state) (reversed for next(char))
            grammar.emplace_back(Rule(counter, 'c', 'g' + temp)); // temp + 'g' a1g (original state)
            grammar.emplace_back(Rule(counter, 'g', 'c' + temp));
            grammar.emplace_back(Rule(counter, 'u', 'a' + temp));
        }

        grammar.emplace_back(Rule('3', 'g', "a4"));

        grammar.emplace_back(Rule('4', 'a', "a"));
        grammar.emplace_back(Rule('4', 'c', "a"));

        alphabet = "acgu";
        varLength = false;
    }

    else if (l == Language::BRACKETS)
    {
        grammar.emplace_back(Rule('0', '(', ")1"));

        grammar.emplace_back(Rule('1', '(', "2"));
        grammar.emplace_back(Rule('1', ')', "0"));

        grammar.emplace_back(Rule('2', '(', "2"));
        grammar.emplace_back(Rule('2', ')', "1"));

        alphabet = "()";
        varLength = true;
        endingNTs = "01";
    }

    stack.push('0'); // Start (S) für stack!
}


PDA::State PDA::next(const char a)
{
    // std::cout << stack.top() << "\n";

    if (alphabet.find(a) == std::string::npos && a != '$')
        return State::FAIL;

    if ((varLength == true) && a == '$' && curNT.size() == 0 && stack.size() == 0)
        return State::FAIL;

    if ((varLength == true) && a == '$' && endingNTs.find(curNT[0].nonTerminal) != std::string::npos)
    {
        std::stack<char> tempStack{};
        while (!stack.empty())
        {
            if (alphabet.find(stack.top()) != std::string::npos)
                tempStack.push(stack.top());
            stack.pop();
        }

        stack = tempStack;
    }

    curNT.clear();

    if ((a == '$' && varLength == true) && (stack.size() < 3))
    {
        if (alphabet.find(stack.top()) != std::string::npos)
            return State::SUCCESS;
        else
            return State::FAIL;
    }

    else if (a == '$' && stack.empty())
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


    // wenn std::string .find() char/substring gefunden hat dann ist der rückgabewert != std::string::npos
    if (alphabet.find(stack.top()) != std::string::npos)
    {
        if (a == stack.top())
            curState = State::IN_PROGRESS;

        else
            curState = State::FAIL;

        stack.pop();
    }

    else
    {
        std::copy_if(grammar.begin(), grammar.end(), std::back_inserter(curNT), [this](Rule x)
                     { return x.nonTerminal == stack.top(); });

        stack.pop();

        for (Rule element : curNT)
        {
            if (element.input == a)
            {
                for (char character : element.state)
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
    // std::stack<char>().swap(stack);
    while (!stack.empty())
    {
        stack.pop();
    }
    stack.push('0');

    PDA::curState = State::FAIL;
}