#pragma once
#include <vector>
#include <iostream>

class Binary
{
public:
	static char getBit(std::vector<unsigned char>& input, size_t ind);
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

class BinaryReader
{
private:
	unsigned char byte, index;
	std::istream& input;
	bool finished;
public:
	BinaryReader(std::istream& in);
	char read();
	unsigned char readByte();
	bool isFinished();
};