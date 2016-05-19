#include "common.hpp"
#include <sstream>
#include<cctype>

vector<string> split(string s, char delimiter)
{
    vector<string> elems;
    stringstream ss(s);
    string item;
    while (getline(ss, item, delimiter))
    {
        elems.push_back(item);
    }
    return elems;
}

string escape(string str, char toEscape, char substitute)
{
    string newString;
    for (char c: str)
    {
        if (c != toEscape)
        {
            newString += c;
        }
        else if (substitute)
        {
            newString += substitute;
        }
    }
    return newString;
}
vector<string> splitword(string text)
{
    vector<string> words;
    int j = 0;
    int k = 0;
    bool isinword = false;
    for (int i = 0; i < text.size; i++)
    {
        if (isalpha(text[i]))
        {
            words[j][k++] = text[i];
            isinword = true;
        }
        else
        {
            if (isinword)
            {
                isinword = false;
                k = 0;
                j++;
            }
        }
    }
    return words;
}