#pragma once
#ifndef TOPSORT_H
#define TOPSORT_H

#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <unordered_set>
using namespace std;

class Algorithm2 {
public:
	//ÅÐ¶ÏÖØ¸´Ä£Ê½
	bool ifRepeatedPattern(string s);

	//
	struct TreeNode {
		int val;
		TreeNode *left;
		TreeNode *right;
		TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	};
};

#endif