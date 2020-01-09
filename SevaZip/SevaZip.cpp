#include <iostream>
#include <Archiver.h>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("input.txt", std::ios::binary);
	ofstream out("output.txt", std::ios::binary);
	Archiver a;
	a.zip(in, out);
	out.close();
	ifstream oin("output.txt", std::ios::binary);
	ofstream oout("decoded_input.txt", std::ios::binary);

	a.unzip(oin, oout);

}
