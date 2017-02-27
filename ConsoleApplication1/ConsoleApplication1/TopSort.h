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

class TopSort {
public:
	int V;
	list<int> * adj;
	TopSort(int v);
	void addEdge(int v, int w);
	void topological_sort(int v, bool visited[], stack<int> & stack);
	void Topological_sort();
};




#endif // !TOPSORT_H
