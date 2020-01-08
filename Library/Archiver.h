#pragma once
#include <iostream>
#include "BinaryHeap.hpp"
#include "HuffmanTree.h"
#include <map>
#include <vector>

using namespace std;

class Archiver
{
private:
	map<unsigned char, vector<bool>> getCodes(HuffmanNode tree) {
		map<unsigned char, vector<bool>> result;
		vector<bool> prefix;
		getCodes(&tree, prefix, result);
		return result;
	}

	void getCodes(HuffmanNode* node, vector<bool> prefix, map<unsigned char, vector<bool>>& m)
	{
		if (!node->left) {
			if (prefix.size() == 0) {
				prefix.push_back(false);
			}
			m[node->get_data()] = prefix;
		}
		else {
			if (node->left) {
				vector<bool> l_prefix = prefix;
				l_prefix.push_back(false);
				getCodes(node->left, l_prefix, m);
				vector<bool> r_prefix = prefix;
				r_prefix.push_back(true);
				getCodes(node->right, r_prefix, m);

			}
		}
	}

public:
	void zip(istream& input, ostream& output) {
		size_t counts[256];
		for (int i = 0; i < 256; i++) {
			counts[i] = 0;
		}

		std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

		for (size_t i = 0; i < buffer.size(); i++)
		{
			counts[buffer[i]]++;
		}


		BinaryHeap<HuffmanNode> tree;
		for (int i = 0; i < 256; i++) {
			if (counts[i] > 0) {
				tree.insert(HuffmanNode(i, counts[i]));
			}
		}

		if (tree.size() == 0)
		{
			return;
		}

		while (tree.size() > 1)
		{
			HuffmanNode mins[2] = { tree.extractMin(), tree.extractMin() };
			HuffmanNode newNode('\0', mins[0].get_count() + mins[1].get_count());
			newNode.left = new HuffmanNode(mins[0]);
			newNode.right = new HuffmanNode(mins[1]);
			tree.insert(newNode);
		}

		HuffmanNode root = tree.extractMin();

		vector<bool> data;
		root.serialize(data);

		map<unsigned char, vector<bool>> dic = getCodes(root);
		input.clear();
		input.seekg(0, ios::beg);
		for (size_t i = 0; i < buffer.size(); i++)
		{
			vector<bool> c = dic[buffer[i]];
			for (size_t j = 0; j < c.size(); j++)
			{
				data.push_back(c[j]);
			}
		}

		size_t offset = (8 - data.size() % 8) % 8;
		for (int i = 0; i < offset; i++)
		{
			data.insert(data.begin(), false);
		}

		std::bitset<8> bits = std::bitset<8>(offset);
		for (size_t i = 0; i < 8; i++) {
			data.insert(data.begin(), bits[7 - i]);
		}


		std::vector<char> bytes((int)std::ceil((float)data.size() / 8));
		for (int byteIndex = 0; byteIndex < bytes.size(); ++byteIndex) {
			for (int bitIndex = 0; bitIndex < 8; ++bitIndex) {
				int bit = data[byteIndex * 8 + bitIndex];

				bytes[byteIndex] |= bit << bitIndex;
			}
			output << bytes[byteIndex];
		}

	}

	void unzip(istream& input, ostream& output) {

		vector<bool> data;
		char c;
		int offset = -1;
		while (input >> std::noskipws >> c)
		{
			if (offset == -1)
			{
				offset = c;
			}
			for (int i = 0; i < 8; i++)
			{
				data.push_back((c >> i) & 1);
			}
		}
		if (data.size() == 0)
		{
			return;
		}

		size_t curr_bit = 8 + offset;
		HuffmanNode* root = HuffmanNode::deserialize(data, curr_bit);
		if (root->left) {
			HuffmanNode* curr_node = root;
			while (curr_bit < data.size())
			{

				if (data[curr_bit])
				{
					curr_node = curr_node->right;
				}
				else {
					curr_node = curr_node->left;
				}

				if (!curr_node->left)
				{
					output << curr_node->get_data();
					curr_node = root;
				}

				curr_bit++;
			}
		}
		else {
			while (curr_bit < data.size())
			{
				output << root->get_data();
				curr_bit++;
			}
		}
	}
};

