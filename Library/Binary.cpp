#include "Binary.h"

char Binary::getBit(std::vector<unsigned char>& input, size_t ind)
{
	char r = (input[ind / 8] >> (ind % 8)) & 1;
	return r;
}

BinaryWriter::BinaryWriter(std::ostream& out) : output(out)
{
	buffer = index = 0;
}

void BinaryWriter::write(bool d)
{
	buffer += (d ? 1 : 0) << index;
	index++;
	if (index == 8)
	{
		output << buffer;
		buffer = index = 0;
	}
}

BinaryReader::BinaryReader(std::istream& in) : input(in)
{
	index = 0;
	char* s = new char[1];
	input.read(s, 1);
	byte = s[0];
	finished = input.eof();
}

char BinaryReader::read()
{
	char result = byte >> index & 1;
	index++;
	if (index == 8)
	{
		char* s = new char[1];
		input.read(s, 1);
		byte = s[0];
		index = 0;
		if (input.eof())
		{
			finished = true;
		}
	}
	return result;
}

unsigned char BinaryReader::readByte()
{
	unsigned char r = 0;
	for (size_t i = 0; i < 8; i++)
	{
		r <<= 1;
		r += read();
	}
	return r;
}

bool BinaryReader::isFinished()
{
	return finished;
}
