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


void serialize_tree(HuffmanNode* node, BinaryWriter& w)
{
	if (node->isLeaf())
	{
		w.write(1);
		std::bitset<8> bits = std::bitset<8>(node->get_data());
		for (size_t i = 0; i < 8; i++) {
			w.write(bits[7 - i]);
		}
	}
	else
	{
		w.write(0);
		serialize_tree(node->left, w);
		serialize_tree(node->right, w);
	}
}

HuffmanNode* deserialize_tree(BinaryReader& r)
{
	char bit = r.read();
	if (bit)
	{
		return new HuffmanNode(r.readByte());
	}
	else {
		HuffmanNode* left = deserialize_tree(r);
		HuffmanNode* right = deserialize_tree(r);
		return new HuffmanNode(left, right);
	}
}



void Archiver::zip(istream& input, ostream& output) {
	size_t counts[256];
	for (int i = 0; i < 256; i++) {
		counts[i] = 0;
	}

	char* s = new char[1];
	while (input.read(s, 1))
	{
		counts[(unsigned char)s[0]]++;
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

	BinaryWriter bw(output);

	for (int j = 0; j < 8; j++)
	{
		bw.write((offset >> j) & 1);
	}

	for (size_t i = 0; i < offset; i++)
	{
		bw.write(0);
	}

	serialize_tree(&root, bw);

	input.clear();
	input.seekg(ios::beg);

	while (input.read(s, 1))
	{
		for (size_t j = 0; j < dic[(unsigned char)s[0]].size(); j++)
		{
			bw.write(dic[(unsigned char)s[0]][j]);
		}
	}

}

void Archiver::unzip(istream& input, ostream& output) {
	BinaryReader br(input);
	if (br.isFinished()) 
	{
		return;
	}
	char offset = 0;
	for (size_t i = 0; i < 8; i++)
	{
		offset += br.read() << i;
	}
	for (size_t i = 0; i < offset; i++)
	{
		br.read();
	}

	HuffmanNode* root = deserialize_tree(br);

	if (!root->isLeaf()) {
		HuffmanNode* curr_node = root;
		while (!br.isFinished())
		{

			if (br.read())
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

		}
	}
	else {
		while (!br.isFinished())
		{
			output << root->get_data();
			br.read();
		}
	}
}
