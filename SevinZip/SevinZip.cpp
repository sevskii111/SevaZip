#include <iostream>
#include <Archiver.h>
#include <fstream>

using namespace std;

int main(int argc, char* argv[])
{
	bool success = false;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "-c"))
		{
			ifstream in(argv[i + 1], std::ios::binary);
			ofstream out(argv[i + 2], std::ios::binary);
			Archiver::zip(in, out);
			success = true;
		}
		else if (!strcmp(argv[i], "-d"))
		{
			ifstream in(argv[i + 1], std::ios::binary);
			ofstream out(argv[i + 2], std::ios::binary);
			Archiver::unzip(in, out);
			success = true;
		}
	}

	if (!success) {
		cout << "Please use -c or -d command line argument";
	}

}
