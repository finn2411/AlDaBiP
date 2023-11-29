/*
Mobarak ALmoustafa
Finn Thierolf
01.11.2023
aufgabe1.cpp
*/

#include <iostream>
#include <algorithm>
#include "Alignment.hpp"

using namespace std;

Alignment::Alignment(const string &seq_v, const string &seq_h)
{
    
    this->seq_h = seq_h;
    this->seq_v = seq_v;
}

void Alignment::compute(const int match, const int mismatch, const int gap, const bool local_align)
{
    alignment.clear();

    if (seq_h != "" || seq_v != "")
    {
        // configure alignment matrix
        matrix.clear();
        uint32_t horizontalSize = seq_h.size() + 1;
        uint32_t verticalSize = seq_v.size() + 1;
        pair<int, traceback> defaultValue = make_pair(0, UP);

        matrix = vector<vector<pair<int, traceback>>>(verticalSize, vector<pair<int, traceback>>(horizontalSize, defaultValue));

        // calculate matrix
        uint32_t i = 0;
        uint32_t j = 0;
        pair<int, traceback> up;
        pair<int, traceback> left;
        pair<int, traceback> dia;
        pair<int, traceback> temp;

        for (i = 0; i < verticalSize; i++)
        {
            for (j = 0; j < horizontalSize; j++)
            {
                // set first row and column
                if (j == 0)
                {
                    matrix[i][j] = make_pair((i)*gap, LEFT);
                }
                else if (i == 0)
                {
                    matrix[i][j] = make_pair((j)*gap, UP);
                }
                else
                {
                    if (seq_h[j - 1] == seq_v[i - 1])
                    {
                        dia = make_pair(matrix[i - 1][j - 1].first + match, DIAGONAL);
                        temp = dia;
                    }
                    else
                    {
                        dia = make_pair(matrix[i - 1][j - 1].first + mismatch, DIAGONAL);
                        temp = dia;
                    }

                    left = make_pair(matrix[i - 1][j].first + gap, LEFT);
                    if (temp.first < left.first)
                    {
                        temp = left;
                    }

                    up = make_pair(matrix[i][j - 1].first + gap, UP);
                    if (temp.first < up.first)
                    {
                        temp = up;
                    }

                    matrix[i][j] = temp;
                }
            }
        }
        // alignment traceback
        i--;
        j--;
        do
        {
            alignment.push_back(matrix[i][j]);

            if (matrix[i][j].second == UP)
            {
                j--;
            }
            else if (matrix[i][j].second == DIAGONAL)
            {
                i--;
                j--;
            }
            else
            {
                i--;
            }
        } while (i != 0 || j != 0);
    }
}

int Alignment::getScore() const
{
    if (alignment.empty())
    {
        return 0;
    }
    else
    {
        return alignment[0].first;
    }
}

void Alignment::getAlignment(string &a1, string &gaps, string &a2) const
{
    a1.clear();
    gaps.clear();
    a2.clear();

    uint32_t v_count = 0;
    uint32_t h_count = 0;

    for (int i = alignment.size() - 1; i >= 0; i--)
    {
        if (alignment[i].second == UP)
        {
            a2.push_back(seq_h[h_count]);
            gaps.push_back(' ');
            a1.push_back('-');
            h_count++;
        }
        else if (alignment[i].second == LEFT)
        {
            a2.push_back('-');
            gaps.push_back(' ');
            a1.push_back(seq_v[v_count]);
            v_count++;
        }
        else if (alignment[i].second == DIAGONAL)
        {
            if (seq_h[h_count] == seq_v[v_count])
            {
                a2.push_back(seq_h[h_count]);
                gaps.push_back('|');
                a1.push_back(seq_v[v_count]);
                h_count++;
                v_count++;
            }
            else
            {
                a2.push_back(seq_h[h_count]);
                gaps.push_back(' ');
                a1.push_back(seq_v[v_count]);
                h_count++;
                v_count++;
            }
        }
    }
}
