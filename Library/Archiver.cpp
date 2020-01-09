#include "Archiver.h"

using namespace std;

void getCodes(HuffmanNode* node, vector<bool> prefix, vector<vector<bool>>& m)
{
	if (node->isLeaf()) {
		if (prefix.size() == 0) {
			prefix.push_back(false);
		}
		m[node->get_data()] = prefix;
	}
	else {
		vector<bool> l_prefix = prefix;
		l_prefix.push_back(false);
		getCodes(node->left, l_prefix, m);
		vector<bool> r_prefix = prefix;
		r_prefix.push_back(true);
		getCodes(node->right, r_prefix, m);

	}
}

vector<vector<bool>> getCodes(HuffmanNode tree) {
	vector<vector<bool>> result;
	result.resize(256);
	vector<bool> prefix;
	getCodes(&tree, prefix, result);
	return result;
}


void Archiver::zip(istream& input, ostream& output) {
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
	size_t tree_size = 0;
	for (int i = 0; i < 256; i++) {
		if (counts[i] > 0) {
			tree.insert(HuffmanNode(i, counts[i]));
			tree_size++;
		}
	}
	tree_size = tree_size * 10 - 1;

	if (tree.size() == 0)
	{
		return;
	}

	while (tree.size() > 1)
	{
		HuffmanNode mins[2] = { tree.extractMin(), tree.extractMin() };
		HuffmanNode newNode(mins[0].get_count() + mins[1].get_count(), new HuffmanNode(mins[0]), new HuffmanNode(mins[1]));
		tree.insert(newNode);
	}

	HuffmanNode root = tree.extractMin();

	vector<vector<bool>> dic = getCodes(root);

	size_t encoded_size = 0;
	for (int i = 0; i < 256; i++) {
		encoded_size += dic[i].size() * counts[i];
	}
	size_t offset = (8 - (tree_size + encoded_size) % 8);

	vector<bool> data;
	data.reserve(tree_size + encoded_size + offset + 8);

	for (int j = 0; j < 8; j++)
	{
		data.push_back((offset >> j) & 1);
	}

	for (size_t i = 0; i < offset; i++)
	{
		data.push_back(0);
	}

	root.serialize(data);

	data.resize(tree_size + encoded_size + offset + 8);
	size_t bit = 0;
	for (size_t i = 0; i < buffer.size(); i++)
	{
		for (size_t j = 0; j < dic[buffer[i]].size(); j++)
		{
			data[8 + offset + tree_size + bit] = dic[buffer[i]][j];
			bit++;
		}
	}

	for (size_t i = 0; i < data.size(); i += 8)
	{
		unsigned char byte = 0;
		for (size_t j = 0; j < 8; j++)
		{
			byte <<= 1;
			byte += data[i + 7 - j];
		}
		output << byte;
	}
}

void Archiver::unzip(istream& input, ostream& output) {

	vector<bool> data;
	std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});

	char offset = -1;
	data.resize(buffer.size() * 8);
	for (size_t i = 0;i < buffer.size();i++)
	{
		if (offset == -1)
		{
			offset = buffer[i];
		}
		for (int j = 0; j < 8; j++)
		{
			data[i * 8 + j] = ((buffer[i] >> j) & 1);
		}
	}
	if (data.size() == 0)
	{
		return;
	}

	size_t curr_bit = offset + 8;
	HuffmanNode* root = HuffmanNode::deserialize(data, curr_bit);
	if (!root->isLeaf()) {
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

			if (curr_node->isLeaf())
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
