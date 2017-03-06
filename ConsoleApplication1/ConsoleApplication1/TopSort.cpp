#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <unordered_set>
#include<iostream>
#include "TopSort.h"

using namespace std;

#define M 5
#define INT_MAX 32767

TopSort::TopSort(int v) {
	V = v;
	adj = new list<int>[V];
}

void TopSort::addEdge(int v, int w) {
	adj[v].push_back(w);//v到w有条边
}

void TopSort::topological_sort(int v, bool visited[], stack<int> &stack) {
	//访问过的点标记一下
	visited[v] = true;
	//对于任意的点，要遍历他的所有出边所涉及的点，并把他们入栈，最后再把本节点入栈。
	for (list<int>::iterator it = adj[v].begin(); it != adj[v].end(); it++) {
		int temp = *it;
		if (visited[temp] == false)
			topological_sort(temp, visited, stack);//遍历与v点有边相连的顶点
	}
	stack.push(v);//把v入栈
}

void TopSort::Topological_sort() {
	bool visited[100]; //这里要用V来初始化
	memset(visited, false, 100);
	stack<int> stack;
	//图上所有的点开始执行
	for (int i = V - 1; i >= 0; i--) {
		if (visited[i] == false)
			topological_sort(i, visited, stack);
	}

	//现在栈中保存了最终的拓扑排序顺序
	while (!stack.empty()) {
		cout << stack.top() << endl;
		stack.pop();
	}
}


//dijiesila算法
/**
从非工作节点里找一个节点，这个节点到源节点的距离最小
*/
int minDistance(int dist[], bool sptSet[]) {
	int min = INT_MAX;
	int min_index;
	for (int v = 0; v < M; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			//如果这个节点还不在扫描过的节点集合里并且从源节点到这个节点的距离小于当前管理的最小的距离时
			min = dist[v], min_index = v;
		}
	}
	return min_index;
}

/**
打印信息
*/
void printMST(int parent[], int n, int graph[M][M], int dist[]) {
	printf("Edge    Weight    Length    dist\n");
	for (int i = 1; i < M; i++) {
		printf("%d---%d   %d    %d\n", parent[i], i, graph[i][parent[i]], dist[i]);
	}
	for (int i = 0; i < M; i++) {
		printf("%d", parent[i]);
	}
}

/**
打印路径
*/
void printRout(int parent[], int sourc) {
	int i;
	stack<int> temp;
	for (int m = 1; m < M; m++) {
		cout << endl;
		temp.push(m);
		i = m;
		while (i != sourc) {
			temp.push(parent[i]);
			i = parent[i];
		}
		while (!temp.empty()) {
			cout << temp.top();
			temp.pop();
		}
	}
}

/**
LV算法
*/
void dijkstra(int graph[M][M], int src) {
	int dist[M];  //输出数组，记录了从src到i的最短路径
	bool sptSet[M]; //sptSet[i]为true表示i已经在当前生成的最短路径里面了或者说从src到i的最短路径已经初始化好了
	int parent[M]; //记录从源点到当前节点沿着当前最短路径的前一节点。
				   //初始化从src到节点i的距离以及sptSet[]为false
	for (int i = 0; i < M; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	//从src到src的长度为0
	dist[src] = 0;
	//src的父节点是自己
	parent[src] = src;

	//从所有的未扫描的点里找出从源节点到其的最短路径
	for (int count = 0; count < M - 1; count++) {
		int u = minDistance(dist, sptSet);

		//把选出来的节点标记为处理过
		sptSet[u] = true;

		//更新从源节点经由刚刚选出来的节点到达各个未扫描节点的最短路径
		for (int v = 0; v < M; v++) {
			if ((!sptSet[v]) && (dist[u] + graph[u][v] < dist[v])) {
				parent[v] = u, dist[v] = dist[u] + graph[u][v];
			}
		}
	}
	printMST(parent, M, graph, dist);
	printRout(parent, 0);
}
//int main() {
//	TopSort g(6);
//	g.addEdge(5, 2);
//	g.addEdge(5, 0);
//	g.addEdge(5, 4);
//	g.addEdge(4, 0);
//	g.addEdge(4, 1);
//	g.addEdge(2, 3);
//	g.addEdge(3, 1);
//	g.addEdge(1, 0);
//	cout << "Following is topological sort result: \n";
//	g.Topological_sort();
//	system("pause");
//}