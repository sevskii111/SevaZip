#pragma once
#include <bitset>
#include <vector>

class HuffmanNode
{
	unsigned char data;
	size_t count;

	static void serialize(HuffmanNode* node, std::vector<bool>& output)
	{
		if (!node->left)
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

	HuffmanNode(char data, HuffmanNode* left, HuffmanNode* right) {
		this->data = data;
		this->count = 0;
		this->left = left;
		this->right = right;
	}

	static char parseByte(std::vector<bool>& input, size_t& ind) {
		char r = 0;
		for (size_t i = ind; i < ind + 8; i++)
		{
			r *= 2;
			r += input[i] ? 1 : 0;
		}
		ind += 8;
		return r;
	}


public:
	HuffmanNode* left;
	HuffmanNode* right;

	HuffmanNode(char data, size_t count) {
		this->data = data;
		this->count = count;
		this->left = this->right = nullptr;
	}

	bool operator <(const HuffmanNode& n) {
		return count < n.count;
	}

	bool operator <=(const HuffmanNode& n) {
		return count <= n.count;
	}

	size_t get_count() {
		return count;
	}

	char get_data() {
		return data;
	}

	void serialize(std::vector<bool>& output)
	{
		serialize(this, output);
	}

	static HuffmanNode* deserialize(std::vector<bool>& input, size_t& ind)
	{
		if (input[ind++])
		{
			return new HuffmanNode(parseByte(input, ind), 0);
		}
		else {
			HuffmanNode* left = deserialize(input, ind);
			HuffmanNode* right = deserialize(input, ind);
			return new HuffmanNode('\0', left, right);
		}
	}

};

