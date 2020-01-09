#pragma once
#include <iostream>
#include "BinaryHeap.hpp"
#include "HuffmanTree.h"
#include "Binary.h"
#include <map>
#include <vector>

class Archiver
{
public:
	static void zip(std::istream& input, std::ostream& output);
	static void unzip(std::istream& input, std::ostream& output);
};

