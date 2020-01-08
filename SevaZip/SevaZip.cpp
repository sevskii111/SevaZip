#include <iostream>
#include <Archiver.h>
#include <fstream>

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");
    Archiver a;
    a.zip(in, out);
}
