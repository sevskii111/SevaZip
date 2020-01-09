#pragma once
#include <vector>
#include <istream>
#include <iostream>

class Binary
{
public:
	static char getBit(std::vector<unsigned char>& input, size_t ind);
	static char parseByte(std::vector<unsigned char>& input, size_t& ind);
};

class BinaryWriter
{
private:
	unsigned char buffer, index;
	std::ostream& output;
public:
	BinaryWriter(std::ostream& out);
	void write(bool d);
};