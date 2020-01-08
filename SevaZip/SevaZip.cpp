#include <iostream>
#include <Archiver.h>
#include <fstream>

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    Archiver a;
    vector<char> zip = a.zip(in);
    for (int i = 0; i < zip.size(); i++)
    {
        out << zip[i];
    }
}
