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
    map<char, vector<bool>> getCodes(HuffmanNode tree) {
        map<char, vector<bool>> result;
        vector<bool> prefix;
        getCodes(&tree, prefix, result);
        return result;
    }

    void getCodes(HuffmanNode* node, vector<bool> prefix, map<char, vector<bool>>& m)
    {
        if (node->get_data()) {
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

    vector<bool> getMeta(map<char, vector<bool>> dic)
    {
        

    }
public:
    std::vector<char> zip(istream& input) {
        size_t counts[256];
        for (int i = 0; i < 256; i++) {
            counts[i] = 0;
        }

        char t;
        while (input >> std::noskipws >> t) {
            counts[t]++;
        }

        BinaryHeap<HuffmanNode> tree;
        for (int i = 0; i < 256; i++) {
            if (counts[i] > 0) {
                tree.insert(HuffmanNode(i, counts[i]));
            }
        }


        while (tree.size() > 1)
        {
            HuffmanNode mins[2] = {tree.extractMin(), tree.extractMin()};
            HuffmanNode newNode('\0', mins[0].get_count() + mins[1].get_count());
            newNode.left = new HuffmanNode(mins[0]);
            newNode.right = new HuffmanNode(mins[1]);
            tree.insert(newNode);
        }

        HuffmanNode n = tree.extractMin();
        map<char, vector<bool>> dic = getCodes(n);

        vector<bool> at;
        n.serialize(at);
        
        input.clear();
        input.seekg(0, ios::beg);
        while (input >> std::noskipws >> t) {
            vector<bool> c = dic[t];
            for (size_t i = 0; i < c.size(); i++)
            {
                at.push_back(c[i]);
            }
        }

        size_t diff = 8 - at.size() % 8;
        for (int i = 0; i < diff; i++)
        {
            at.insert(at.begin(), false);
        }

        std::bitset<8> bits = std::bitset<8>(diff);
        for (size_t i = 0; i < 8; i++) {
            at.insert(at.begin(), bits[7 - i]);
        }

        std::vector<char> bytes((int)std::ceil((float)at.size() / 8));
        for (int byteIndex = 0; byteIndex < bytes.size(); ++byteIndex) {
            for (int bitIndex = 0; bitIndex < 8; ++bitIndex) {
                int bit = at[byteIndex * 8 + bitIndex];

                bytes[byteIndex] |= bit << bitIndex;
            }
        }

        return bytes;
    }

    ifstream& unzip(char* input) {

    }
};

