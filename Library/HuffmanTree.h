#pragma once
#include <bitset>
#include <vector>
#include <istream>
#include "Binary.h"

class HuffmanNode
{
private:
	unsigned char data;
	size_t count;

public:
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(unsigned char data, size_t count, HuffmanNode* left, HuffmanNode* right);
	HuffmanNode(unsigned char data) : HuffmanNode(data, 0, nullptr, nullptr) {};
	HuffmanNode(unsigned char data, size_t count) : HuffmanNode(data, count, nullptr, nullptr) {};
	HuffmanNode(HuffmanNode* left, HuffmanNode* right) : HuffmanNode(0, 0, left, right) {};
	HuffmanNode(size_t count, HuffmanNode* left, HuffmanNode* right) : HuffmanNode(0, count, left, right) {};

	bool operator <(const HuffmanNode& n);
	bool operator <=(const HuffmanNode& n);

	size_t get_count();
	unsigned char get_data();

	bool isLeaf();
};

