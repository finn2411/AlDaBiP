/* 
Mobarak ALmoustafa
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include<iostream>
#include"Alignment.hpp"


Alignment::Alignment(const std::string& seq_v, const std::string& seq_h)
{
    this -> seq_h = seq_h;
    this -> seq_v = seq_v;
}

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align = false)
{
    // configure alignment matrix
    matrix.clear();
    int horizontalSize = seq_h.length() - 1; 
    int verticalSize = seq_v.length() - 1; 
    int defaultValue = 0;

    matrix = std::vector<std::vector<int>>(verticalSize, std::vector<int>(horizontalSize, defaultValue));
}

int Alignment::getScore() const
{

}

void Alignment::getAlignment(std::string& a1, std::string& gaps, std::string& a2) const
{

}


int main()
{
    Alignment("test", "test1");
}