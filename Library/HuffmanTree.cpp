#include "HuffmanTree.h"


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

bool HuffmanNode::isLeaf()
{
	return !this->left;
}