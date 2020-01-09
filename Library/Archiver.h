#pragma once
#include <iostream>
#include "BinaryHeap.hpp"
#include "HuffmanTree.h"
#include <map>
#include <vector>

class Archiver
{
public:
	void zip(std::istream& input, std::ostream& output);
	void unzip(std::istream& input, std::ostream& output);
};

