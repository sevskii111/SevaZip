#include "Binary.h"

char Binary::getBit(std::vector<unsigned char>& input, size_t ind)
{
	char r = (input[ind / 8] >> (ind % 8)) & 1;
	return r;
}

char Binary::parseByte(std::vector<unsigned char>& input, size_t& ind) {
	char r = 0;
	for (size_t i = 0; i < 8; i++, ind++)
	{
		r <<= 1;
		r += Binary::getBit(input, ind);
	}
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
