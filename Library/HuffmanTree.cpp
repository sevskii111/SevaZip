#include "HuffmanTree.h"

char parseByte(std::vector<bool>& input, size_t& ind) {
	char r = 0;
	for (size_t i = ind; i < ind + 8; i++)
	{
		r *= 2;
		r += input[i] ? 1 : 0;
	}
	ind += 8;
	return r;
}

void HuffmanNode::serialize(HuffmanNode* node, std::vector<bool>& output)
{
	if (node->isLeaf())
	{
		output.push_back(1);
		std::bitset<8> bits = std::bitset<8>(node->data);
		for (size_t i = 0; i < 8; i++) {
			output.push_back(bits[7 - i]);
		}
	}
	else
	{
		output.push_back(0);
		serialize(node->left, output);
		serialize(node->right, output);
	}
}




HuffmanNode::HuffmanNode(unsigned char data, size_t count, HuffmanNode* left, HuffmanNode* right)
{
	this->data = data;
	this->count = count;
	this->left = left;
	this->right = right;
}

bool HuffmanNode::operator<(const HuffmanNode& n)
{
	return count < n.count;
}

bool HuffmanNode::operator<=(const HuffmanNode& n)
{
	return count <= n.count;
}

size_t HuffmanNode::get_count() {
	return count;
}

unsigned char HuffmanNode::get_data() {
	return data;
}

void HuffmanNode::serialize(std::vector<bool>& output)
{
	serialize(this, output);
}

bool HuffmanNode::isLeaf()
{
	return !this->left;
}

HuffmanNode* HuffmanNode::deserialize(std::vector<bool>& input, size_t& ind)
{
	if (input[ind++])
	{
		return new HuffmanNode(parseByte(input, ind));
	}
	else {
		HuffmanNode* left = deserialize(input, ind);
		HuffmanNode* right = deserialize(input, ind);
		return new HuffmanNode(left, right);
	}
}

