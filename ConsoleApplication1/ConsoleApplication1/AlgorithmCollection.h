#pragma once
#ifndef ALGORITHMCOLLECTION_H
#define ALGORITHMCOLLECTION_H
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_set>
using namespace std;
class AlgorithmCollection {
public:
	AlgorithmCollection();
	int binSearch(int m[], int start, int end, int target);
	void insertSorting(int m[], int length);
	void insertSortingByBinSearch(int m[], int length);
	void bubbleSort(int m[], int length);
	int partion(int m[], int left, int right);
	void quickSort(int m[], int left, int right);
	void mergeSort(int m[]);
	void permutationOfString(char *pStr, int begin, int end);
	int digitToValue(char c);
	int ConvertToBase(string number, int base);
	void swapForInt(int &m, int &n);
	void swapForChar(char &m, char &n);
	void reverse(int m[], int length);
	int removeDuplicates(int A[], int n);
	vector<int> plusOne(vector<int> &digits);
	list<char> LetterCount(list<char> listSource);
	struct Node
	{
		int self; //数据
		Node *left; //左节点
		Node * right; //右节点
	};
	queue<Node*> depthFirstSearch();
	queue<Node*> widthFirstSearch();

	//单词阶梯 Word Ladder
	int ladderLength(string start, string end, unordered_set<string> &dict);
	//在一个装满字母的二维数组里搜索某个词，搜索规则是字母必须是上下左右相邻的，搜到以后就返回true，没有就返回false
	bool wordSearch(vector<vector<char>> &board, vector<vector<bool>> &visited, int row, int col, string word, int index);
	bool exist(vector<vector<char>> &board, string word);
	//Surrounded Regions,将所有以O组成、但不连通到网格边缘的区域变为X
	void solve(vector<vector<char>> &board);
	void fill(vector<vector<char>> &board, int i, int j, char target, char c);
	void fillBorders(vector<vector<char>> &board, char target, char c);
	void replace(vector<vector<char>> &board, char target, char c);
	//最长不重复子序列
	int lengthOfLongestNonRepeatedSubs(string s);
	//寻找最长连续子串的长度
	int findLongestSequence(int a[], int size);
	//寻找两个字符串的最长公共字串长度
	//暴力解法
	int findCommonLongestSubstring(string &a, string &b);
	//动态规划法
	int findCommonLongestSubstringWithDP(string &a, string &b);
	//最长公共前缀
	string findLongestCommonPrefix(vector<string> &myVector);
};

//无向图的结点
class UndirectedGraphNode {
public:
	int label; //结点标签
	vector<UndirectedGraphNode*> neighbors; //结点的邻居结点
	UndirectedGraphNode(int mylabel) {
		label = mylabel;
	}
	UndirectedGraphNode *cloneGraph(UndirectedGraphNode *node);
};


#endif