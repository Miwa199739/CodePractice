#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <unordered_set>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <stdio.h>
#include <fstream>
#include <iomanip>
#include "Algorithm2.h"

using namespace std;

/*这道题给了我们一个字符串，问其是否能拆成n个重复的子串。
那么既然能拆分成多个子串，那么每个子串的长度肯定不能大于原字符串长度的一半，
那么我们可以从原字符串长度的一半遍历到1，如果当前长度能被总长度整除，说明可以分成若干个子字符串，
我们将这些子字符串拼接起来看跟原字符串是否相等。如果拆完了都不相等，返回false。*/
bool Algorithm2::ifRepeatedPattern(string s) {
	int size = s.size();
	for (int i = size / 2; i >= 1; i--) {
		string str = "";
		if (size % i == 0) {
			int c = size / i;
			for (int j = 0; j < c; j++) {
				str += s.substr(0, i);
			}
			if (str == s)
				return true;
		}
	}
	return false;
}


//我最先想到的解法是遍历的点，以每个点都当做根节点，算出高度，然后找出最小的，但是一时半会又写不出程序来，
//于是上网看看大家的解法，发现大家推崇的方法是一个类似剥洋葱的方法，就是一层一层的褪去叶节点，最后剩下的一个或两个节点就是我们要求的最小高度树的根节点
//跟之前那到课程清单的题一样，我们需要建立一个图g，是一个二维数组，其中g[i]是一个一维数组，保存了i节点可以到达的所有节点。
//我们开始将所有只有一个连接边的节点(叶节点)都存入到一个队列queue中，然后我们遍历每一个叶节点，通过图来找到和其相连的节点，
//并且在其相连节点的集合中将该叶节点删去，如果删完后此节点也也变成一个叶节点了，加入队列中，再下一轮删除。
//那么我们删到什么时候呢，当节点数小于等于2时候停止，此时剩下的一个或两个节点就是我们要求的最小高度树的根节点啦，
//一个图最多有两个MHT树，为距离最长的两个节点的中点。关键是怎么找出这两个相聚最远的节点。
vector<int> findMinHeightTrees(int n, vector<pair<int, int> >& edges) {
	if (n == 1) return{ 0 };
	vector<int> res;
	vector<unordered_set<int>> myVector(n);
	queue<int> q;

	//auto可以在声明变量时根据变量初始值的类型自动为此变量选择匹配的类型
	for (auto edge : edges) {
		myVector[edge.first].insert(edge.second);
		myVector[edge.second].insert(edge.first);
	}

	//叶子节点入队列
	for (int i = 0; i < n; i++) {
		if (myVector[i].size() == 1)
			q.push(i);
	}

	while (n > 2) {
		int size = q.size();
		n -= size;

		//把叶子节点一个一个踢出去
		for (int i = 0; i < size; i++) {
			int current = q.front(); q.pop();
			for (auto adj : myVector[current]) {
				myVector[adj].erase(current);
				if (myVector[adj].size() == 1)//注意这是叶子结点的条件
					q.push(adj);
			}
		}
	}

	while (!q.empty()) {
		std::cout << "height";
		std::cout << q.front() << endl;
		res.push_back(q.front());
		q.pop();
	}
	return res;
}

int value(int x1, int x2, int y1, int y2) {
	return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

//这道题定义了一种类似回旋镖形状的三元组结构，
//要求第一个点和第二个点之间的距离跟第一个点和第三个点之间的距离相等。
//现在给了我们n个点，让我们找出回旋镖的个数。
//那么我们想，如果我们有一个点a，还有两个点b和c，如果ab和ac之间的距离相等，
//那么就有两种排列方法abc和acb；如果有三个点b，c，d都分别和a之间的距离相等，
//那么有六种排列方法，abc, acb, acd, adc, abd, adb，
//那么是怎么算出来的呢，很简单，如果有n个点和a距离相等，那么排列方式为n(n-1)，
//那么我们问题就变成了遍历所有点，让每个点都做一次点a，
//然后遍历其他所有点，统计和a距离相等的点有多少个，然后分别带入n(n-1)计算结果并累加到res中
//只有当n大于等于2时，res值才会真正增加，
int numberOfBoomerangs(vector<pair<int, int>>& points) {
	int length = 0;

	for (int i = 0; i < points.size(); i++) {
		unordered_map<int, int> myMap(points.size());
		for (int j = 0; j < points.size(); j++) {
			if (i == j)
				continue;
			int currentValue = value(points[i].first, points[j].first, points[i].second, points[j].second);
			myMap[currentValue]++;
		}

		for (auto it = myMap.begin(); it != myMap.end(); it++) {
			if (it->second > 1) {
				length += it->second * (it->second - 1);
			}
		}

	}
	return length;
}

//Target Sum
void findTargetHelper(vector<int>& nums, int S, int start, int &res) {
	if (start == nums.size()) {
		if (S == 0)
			res++;
		return;
	}
	findTargetHelper(nums, S + nums[start], start + 1, res);
	findTargetHelper(nums, S - nums[start], start + 1, res);
}

int findTargetSumWays(vector<int>& nums, int S) {
	int res = 0;
	findTargetHelper(nums, S, 0, res);
	return res;
}

void mergeArray(int a[], int m, int b[], int n) {
	int k = m + n - 1;//m和n分别是A和B的长度
	int i = m;
	int j = n;
		while (k >= 0) {
			if (i >= 0 && j >= 0) {
				if (a[i] > b[j]) {
					a[k] = a[i];
					i--;
				}
				else {
					a[k] = b[j];
					j--;
				}
			}
			else if (i >= 0) {
				a[k] = a[i];
				i--;
			}
			else if (j >= 0) {
				a[k] = b[j];
				j--;
			}
			else
				break;
			k--;
		}
}

struct Interval {
	int start;
	int end;
	Interval() : start(0), end(0) {}
	Interval(int s, int e) : start(s), end(e) {}
};

//定义比较函数
bool compare(Interval a, Interval b) {
	return a.start < b.start;
}

//合并区间
vector<Interval> mergeIntervals(vector<Interval>& intervals) {
	vector<Interval> result;
	if (intervals.empty())
		return result;

	sort(intervals.begin(), intervals.end(), compare);
	result.push_back(intervals[0]);

	for (int i = 0; i < intervals.size(); i++) {
		//新的Interval的首元素比result末尾的尾元素还要大，不重叠，直接把这个Interval入向量
		//因为我们已经对intervals进行了排序，所以这里新的Interval[i]的首元素一定比栈尾的首元素大
		if (result.back().end < intervals[i].start)
			result.push_back(intervals[i]);
		else
			//重叠了，更新result.back
			result.back().end = max(result.back().end, intervals[i].end);
	}
	return result;
}

//插入一个range,返回合并后的
vector<Interval> insertInterval(vector<Interval>& intervals, Interval newInterval) {
	vector<Interval> result;
	if (intervals.empty())
		return result;

	intervals.push_back(newInterval);
	sort(intervals.begin(), intervals.end(), compare);
	result.push_back(intervals[0]);

	for (int i = 0; i < intervals.size(); i++) {
		if (result.back().end < intervals[i].start) {
			result.push_back(intervals[i]);
		}
		else
			result.back().end = max(intervals[i].end, result.back().end);
	}
	return result;
}

//移除ovrelap的interval
int eraseOverlapIntervals(vector<Interval>& intervals) {
	int num = 0;
	vector<Interval> result;
	if (intervals.empty())
		return 0;
	sort(intervals.begin(), intervals.end(), compare);

	result.push_back(intervals[0]);
	for (int i = 1; i < intervals.size(); i++) {
		if (result.back().end > intervals[i].start)
		{
			//重叠了，我们更新result.back().end的值是为了保证把覆盖面最大的那个interval踢掉，
			//以免它继续跟下面的interval覆盖，这样能保证我们踢掉的interval数量最小
			result.back().end = min(result.back().end, intervals[i].end);
			num++;
		}
		else
			result.push_back(intervals[i]);
	}
	return num;
}

//给一个长度为n的数组和一个长度为k的增量规则向量，
//用增量规则对数组进行更新，返回新的数组，
//要求O（k+n）的时间复杂度和额外的O（1）的空间复杂度
//一般做法，一个一个加，O（n2）不符合时间复杂度的要求
vector<int> getModifiedArrayForce(int length, vector<vector<int>>& updates) {
	vector<int> result;
	//循环updates，把update里的增量给对应的数组元素一个一个加上去
	for (int i = 0; i < updates.size(); i++) {
		int j = updates[i][0];
		while (j <= updates[i][1]) {
			result[j] = result[j] + updates[i][3];
		}
	}
	return result;
}

//进阶做法
vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
	vector<int> result;

	//O(k)复杂度
	for (int i = 0; i < updates.size(); i++) {
		result[updates[i][0]] += updates[i][2];
		result[updates[i][1] + 1] -= updates[i][2];
	}

	//O(n)复杂度
	for (int i = 1; i <= length; i++) {
		result[i] += result[i - 1];
	}
	result.pop_back();
	return result;
}

//小球穿越迷宫，能否从起始点到达终点
bool hasPathHelperRecurion(vector<vector<int>>& maze, vector<vector<int>>& dp, vector<vector<bool>> &visited, int start_i, int start_j, int end_i, int end_j) {
	if (start_i == end_i && start_j == end_j)
		return true;
	//start_i，start_j这个点上次来过，不用再重复访问了，直接返回我们保存好的中间值
	if (dp[start_i][start_j] != -1)
		return dp[start_i][start_j];

	bool res = false;
	visited[start_i][start_j] = true;
	//如果涉及到向上下左右四个方向移动，就是用dirs数组
	vector<vector<int>> dirs = { { -1,0 },{ 0,-1 } ,{ 1,0 },{ 0,1 } };
	for (vector<int> dir : dirs) {
		int x = start_i;
		int y = start_j;
		while (x > 0 && x < maze.size() && y > 0 && y < maze[0].size() && maze[x][y] != 1) {
			x += dir[0];
			y += dir[1];
		}
		//走到墙了或者数组越界了，退回去一步
		x -= dir[0];
		y -= dir[1];
		//下一次换方向的时候从这一点开始
		if (!visited[x][y]) {
			res |= hasPathHelperRecurion(maze, dp, visited, x, y, end_i, end_j);
		}
	}
	visited[start_i][start_j] = false;
	dp[start_i][start_j] = res;
	return res;
}

bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
	int end_i = destination[0];
	int end_j = destination[1];
	int start_i = start[0];
	int start_j = start[1];
	vector<vector<bool>> visited(maze.size(), vector<bool>(maze[0].size(), false));
	vector<vector<int>> dp(maze.size(), vector<int>(maze[0].size(), -1));
	return hasPathHelperRecurion(maze, dp, visited, start_i, start_j, end_i, end_j);
}

bool hasPathHelperIterative(vector<vector<int>>& maze, vector<vector<bool>> &visited, int start_i, int start_j, int end_i, int end_j) {
	vector <vector<int>> dirs = { { -1,0 },{ 1,0 },{ 0,1 },{ 0,-1 } };
	queue<pair<int, int>> kicked;
	kicked.push(make_pair(start_i, start_j));
	visited[start_i][start_j] = true;
	while (!kicked.empty()) {
		int current_i = kicked.front().first;
		int current_j = kicked.front().second;
		if (current_i == end_i && current_j == end_j)
			return true;
		kicked.pop();
		//重点：沿着一个方向一直走，直到遇到墙
		for (vector<int> dir : dirs) {
			while (current_i > 0 && current_i < maze.size() && current_j > 0 && current_j < maze[0].size() && maze[current_i][current_j] != 1) {
				current_i += dir[0];
				current_j += dir[1];
			}
			//走到墙了或者数组越界了，退回去一步
			current_i -= dir[0];
			current_j -= dir[1];
			//下一次换方向的时候从这一点开始
			if (!visited[current_i][current_j]) {
				visited[current_i][current_j] = true;
				kicked.push(make_pair(current_i, current_j));
			}
		}
	}
	return false;
}

//二叉树的竖直遍历
//基于广度优先遍历，在遍历过程中要给每个元素给一个columnno,
//左子节点的编号是父节点编号减一，右子节点编号是根节点编号加一，
//最后根据编号组织vector返回
vector<vector<int>> verticalOrder(Algorithm2::TreeNode* root) {
	map<int, vector<int>> myMap;
	vector<vector<int>> result;
	int column_no = 0;
	queue<pair<int, Algorithm2::TreeNode*>> myQueue;
	myQueue.push(make_pair(0, root));

	while (!myQueue.empty()) {
		Algorithm2::TreeNode * current = myQueue.front().second;
		column_no = myQueue.front().first;
		myQueue.pop();
		myMap[column_no].push_back(current->val);
		if (current->left != NULL) {
			myQueue.push(make_pair(column_no - 1, current->left));
		}
		if (current->right != NULL) {
			myQueue.push(make_pair(column_no + 1, current->right));
		}
	}

	for (auto a : myMap) {
		result.push_back(a.second);
	}

	return result;
}

//找无向图中的所有连通区域
int countComponents(int n, vector<pair<int, int>>& edges) {
	map<int, vector<int>> myMap;
	//把图初始化成每个节点和其相邻节点的map，方便下面的DFS
	for (auto a : edges) {
		myMap[a.first].push_back(a.second);
		myMap[a.second].push_back(a.first);
	}
	//判断一个节点是否访问过,初始化为false;
	vector<bool> visited(n, false);
	int i = 0;
	int count = 0;
	//以所有节点为遍历的开始节点
	while (i < n) {
		//如果这个节点访问过了，说明他在一个连通区域内，我们不增加count，直接跳到下一个节点进行判断
		if (visited[i]) {
			i++;
			continue;
		}
		//如果这个节点没访问过，那么他肯定在另一个连通区域内，
		//这时我们增加计数，开始从这个节点进行DFS遍历
		count++;
		stack<int> myStack;
		myStack.push(i);
		//开始从i点进行DFS
		while (!myStack.empty()) {
			int current = myStack.top();
			myStack.pop();
			visited[current] = true;
			for (auto a : myMap[current]) {
				myStack.push(a);
			}
		}
		i++;
	}
	return count;
}

//安排课程顺序
//要上a.second先上a.first
bool canFinishIterative(int numCourses, vector<pair<int, int>>& prerequisites) {
	//二维数组存储有向图
	vector<vector<int>> myVector(numCourses, vector<int>(0));
	//存储每个节点的出度
	vector<int> in(numCourses, 0);

	//初始化
	for (auto a : prerequisites) {
		myVector[a.second].push_back(a.first);
		in[a.first]++;
	}

	//判断一个节点是否访问过,初始化为false;
	vector<bool> visited(numCourses, false);

	queue<int> myQueue;
	//把所有出度为0的点push进去
	for (int i = 0; i < numCourses; i++) {
		if (in[i] == 0)
			myQueue.push(i);
	}

	//开始BFS
	while (!myQueue.empty()) {
		int current = myQueue.front();
		myQueue.pop();
		for (auto a : myVector[current]) {
			in[a]--;
			//出度为0，为叶子结点
			if (in[a] == 0)
				myQueue.push(a);
		}
	}

	for (int i = 0; i < numCourses; i++) {
		if (in[i] != 0)
			return false;
	}

	return true;
}

//安排课程顺序错误解法，没有考虑这是有向图
bool canFinishRecursion(int numCourses, vector<pair<int, int>>& prerequisites) {
	//二维数组存储有向图
	vector<vector<int> > myVector(numCourses, vector<int>(0));
	//初始化
	for (auto a : prerequisites) {
		myVector[a.second].push_back(a.first);
	}
	int i = 0;
	while (i < numCourses) {
		//判断一个节点是否访问过,初始化为false;
		vector<bool> visited(numCourses, false);
		//判断一个节点是否已经入栈；
		vector<bool> inQueue(numCourses, false);
		stack<int> myQueue;
		myQueue.push(i);
		inQueue[i] = true;
		while (!myQueue.empty()) {
			int current = myQueue.top();
			myQueue.pop();
			inQueue[current] = false;
			visited[current] = true;
			for (auto a : myVector[current]) {
				//注意：这里的判断除了过滤掉了环，还过滤掉了连在一起的几个元素但没构成环的，注意环是有向的，这里过滤掉了无向的环
				//所以应该换一种解法
				if (visited[a]) {
					bool res = false;
					//加条件，从a出去的边不到已经为true的那些点
					//34/37个用例，不知道问题在哪里，改用另外一种方法吧
					for (auto m : myVector[a]) {
						res |= visited[m];
					}
					if (res)
						return false;
				}
				myQueue.push(a);
			}
		}
		i++;
	}
	return true;
}

bool canFinishRecursionHelper(vector<vector<int> > &myVector, vector<int> &visited, int i) {
	if (visited[i] == -1)  //已经访问过了，再次访问就说明是回路
		return false;
	if (visited[i] == 1)  //记录中间状态,已经访问过了且从这一点到图结束不存在回路
		return true;
	visited[i] = -1;
	for (auto a : myVector[i]) {
		if (!canFinishRecursionHelper(myVector, visited, a))
			return false;
	}
	visited[i] = 1;
	return true;
}

//安排课程顺序,递归解法，参考别人的
bool canFinishRecursionReference(int numCourses, vector<pair<int, int>>& prerequisites) {
	//二维数组存储有向图
	vector<vector<int> > myVector(numCourses, vector<int>(0));
	//初始化
	for (auto a : prerequisites) {
		myVector[a.second].push_back(a.first);
	}
	int i = 0;
	//判断一个节点是否访问过,初始化为false;
	vector<int> visited(numCourses, 0);
	while (i < numCourses) {
		if (!canFinishRecursionHelper(myVector, visited, i))
			return false;
		i++;
	}
	return true;
}

//只翻转元音字母
string reverseVowels(string s) {
	string result = s;
	vector<int> indexOfVowels;
	//记录元音位置
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
			indexOfVowels.push_back(i);
		}
	}
	int len = indexOfVowels.size();
	for (int j = 0; j < len / 2; j++) {
		result[indexOfVowels[j]] = s[indexOfVowels[len - j - 1]];
		result[indexOfVowels[len - j - 1]] = s[indexOfVowels[j]];
	}
	return result;
}
//return -1 if my number is lower, 1 if my number is higher, 
//otherwise return 0
int guess(int num) {
	return 0;
}

//二分法找
int guessNumber(int n) {
	int high = n;
	int low = 1;
	int mid;
	int money = 0;
	while (low <= n) {
		mid = low + (high - low) / 2;
		if (guess(mid) == 1) {
			money += mid;
			low = mid + 1;
		}
		else if (guess(mid) == -1) {
			money += mid;
			high = mid - 1;
		}
		else {
			return money;
		}
	}
	return money;
}

//是否为2的幂次方
bool isPowerOfTwo(int n) {
	return (n > 0) && (!(n & (n - 1)));
}

//是否为3的幂次方
//1162261467为int范围内最大的3的倍数
bool isPowerOfThree(int n) {
	return (n > 0 && 1162261467 % n == 0);
}

//是否为4的幂次方
bool isPowerOfFour(int num) {
	//2的幂次方转换而来，2的偶数次方就是4的次方
	int count = 0;
	int times = 1;
	while (num > 0) {
		count += (num & 1);
		num >>= 1;
		times++;
	}
	//被2整除的条件加上2的偶数次方的条件
	return (count == 1 && times % 2 == 0);
}

//数组中出了一个元素出现一次，其他元素都出现两次，找到这个元素
//利用异或操作的属性，可交换性
//int singleNumber(vector<int>& nums) {
//	int result = 0;
//	for (int i = 0; i<nums.size(); i++) {
//		result ^= nums[i];
//	}
//	return result;
//}

//数组中出了一个元素出现一次，其他元素都出现三次，找到这个元素
int singleNumberII(vector<int>& nums) {
	int n = nums.size();
	if (n = 0) return -1;
	if (n == 1) return nums[0];
	int count = 0;
	//先排序
	sort(nums.begin(), nums.end());
	for (int i = 0; i < n; i++) {
		if (nums[i] == nums[i + 1])
			count++;
		else {
			if (count < 3)
				return nums[i];
			count = 1;
		}
	}
	return nums[n - 1];
}

//两个元素只出现一次，其余的元素都出现两次
vector<int> singleNumberIII(vector<int>& nums) {
	int n = nums.size();
	vector<int> result;
	if (n <= 0) return result;
	if (n == 2) {
		result.push_back(nums[0]);
		result.push_back(nums[1]);
		return result;
	}
	sort(nums.begin(), nums.end());
	int count = 1;
	for (int i = 0; i < nums.size(); i++)
	{
		if (nums[i] == nums[i + 1])
			count++;
		else
		{
			if (count < 2) {
				result.push_back(nums[i]);
			}
			count = 1;
		}
	}
	return result;
}

void treePaths(Algorithm2::TreeNode* root, vector<string> &result, string str) {
	str += to_string(root->val);
	if (!root->left && !root->right)
		result.push_back(str);
	else {
		if (root->left) {
			treePaths(root->left, result, str + "->");
		}
		if (root->right) {
			treePaths(root->right, result, str + "->");
		}
	}
}

vector<string> binaryTreePaths(Algorithm2::TreeNode* root) {
	vector<string> result;
	treePaths(root, result, "");
	return result;
}

//判断一个字符串能组成的最长回文串的长度
int lengthOflongestPalindrome(string s) {
	unordered_map<char, int> myMap;
	int length = 0;
	for (int i = 0; i < s.size(); i++) {
		myMap[s[i]]++;
	}
	for (auto a : myMap) {
		length += a.second / 2;
	}
	length = length * 2 + 1;
	if (length > s.size())
		return s.size();
	return length;
}

//最长公共子串
string commonLongestSubstringWithDP(string &a, string &b) {
	int size_a = a.size();
	int size_b = b.size();
	int maxLength = 0;

	//保存以a[i]和b[j]结尾的最长的子串长度
	vector<vector<int>> myVector(size_a, vector<int>(size_b));

	//考虑到L[i+1,j+1]=(s[i+1]==t[j+1]?L[i,j]+1:0)，
	//我们应该先把L[i,j]算出来
	//临界条件，以a[0]结尾的字符串
	for (int j = 0; j < size_b; j++) {
		if (a[0] == b[j])
			myVector[0][j] = 1;
		else
			myVector[0][j] = 0;
	}

	//临界条件，以b[0]结尾的字符串
	for (int i = 1; i < size_a; i++) {
		if (a[i] == b[0])
			myVector[i][0] = 1;
		else
			myVector[i][0] = 0;

		for (int j = 1; j < size_b; j++) {
			if (a[i] == b[j])
				myVector[i][j] = myVector[i - 1][j - 1] + 1;
			else
				myVector[i][j] = 0;
		}
	}

	int index_i;
	int index_j;
	for (int i = 0; i < size_a; i++) {
		for (int j = 0; j < size_b; j++) {
			if (myVector[i][j] > maxLength) {
				maxLength = myVector[i][j];
				index_i = i;
				index_j = j;
			}
		}
	}
	string result = "";
	for (int i = index_i; i > index_i - maxLength; i--) {
		result += a[i];
	}
	return result;
}

//返回最长回文子串
//想法：把字符串翻转，最长回文串就是原字符串与翻转后字符串的最长公共子串
string longestPalindrome(string s) {
	int size_s = s.size();
	string reverse_s = "";
	if (size_s == 0 || size_s == 1)
		return s;
	for (int i = size_s - 1; i >= 0; i--) {
		reverse_s += s[i];
	}
	return commonLongestSubstringWithDP(s,reverse_s);
}

//直接做法，从字符串首部开始扫描
string longestPalindromeII(string s) {
	int size_s = s.size();
	if (size_s == 0 || size_s == 1)
		return s;
	int start, maxlength = 0;
	int currentLength = 0;
	int k, j;
	for (int i = 0; i < size_s;) {
		//如果剩下的元素个数比maxlength还少的话，直接跳出循环
		if (size_s - i <= maxlength)
			break;
		//j往后找，k往前找
		j = i;
		k = i;
		//碰到相同元素了，j一直往前走直到碰到不同元素为止
		while (j + 1 < size_s && s[j] == s[j + 1]) {
			j++;
		}
		//i下次从j+1的位置开始，j之前的我们已经查验过了
		i = j + 1;
		//判断j+1和k-1两个元素是否相等，是的话，继续向两边扩展
		while (j + 1 <  size_s && k - 1 >= 0 &&  s[j + 1] == s[k - 1]) {
			j++;
			k--;
		}
		//记长度
		currentLength = j - k + 1;
		if (currentLength > maxlength) {
			maxlength = currentLength;
			start = k;
		}
	}
	return s.substr(start, maxlength);
}

//DP解法，P[i,j]表示i，j区间的最长回文串长度
string longestPalindromeWithDP(string s) {
	int size = s.size();
	int maxLength = 0,start = 0,end = 0;
	if (size == 0)
		return"";
	vector<vector<int>> dp(size, vector<int>(size, 0));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i; j++) {
				dp[j][i] = ((s[j] == s[i])&& (i - j < 2 || dp[j + 1][i - 1]));
				if (dp[j][i] && (i - j + 1) > maxLength) {
					maxLength = i - j +1;
					start = j;
					end = i;
				}
		}
		dp[i][i] = 1;
	}
	return s.substr(start, end - start + 1);
}
//判断一个数字是否是回文
bool isPalindrome(int x) {
	if(x == 0)
		return true;
	if (x < 0)
		return false;
	int temp = x;
	int y = 0;
	while (x != 0) {
		//原来的数：x/10 * 10 + x % 10
		//反转以后，低位变高位，高位变低位
		y = y * 10 + x % 10;
		x = x / 10;

		//判断一个数的二进制是否为回文串
		/*y = y * 2 + x % 2;
		x = x / 2;*/

		//八进制的话就是
		/*y = y * 8 + x % 8;
		x = x / 8;*/
	}
	if (y == temp)
		return true;
	return false;
}

//记住这种思路，两个变量控制各往数组两边走
bool isPalindrome(string s) {
	int front = s.size() - 1;
	int back = 0;
	while(front > back){
		if(!isalnum(s[back])) {
			back++;
			continue;
		}
		if (!isalnum(s[front])) {
			front--;
			continue;
		}

		if (tolower(s[front]) != tolower(s[back]))
			return false;
		back++;
		front--;
	}
	return true;
}

//求最长不下降子串的长度
//动态规划思想，以每个元素结尾的递增序列长度初始化为1，然后利用L[i+1] = L[i+1] > L[i] + 1 ? L[i+1] : L[i] + 1
int lengthOfLIS(vector<int>& nums) {
	int size_nums = nums.size();
	int maxLength = 0;
	vector<int> L(size_nums);
	for (int i = 0; i < size_nums; i++) {
		L[i] = 1;
		//j从0循环到i
		for (int j = 0; j < i; j++) {
			if (nums[j] < nums[i]) {
				L[i] = L[i] < L[j] + 1 ? L[j] + 1 : L[i];
			}
		}
		if (L[i] > maxLength)
			maxLength = L[i];
	}
	return maxLength;
}



//把一个数的二进制表示翻转，再返回翻转后的数
int reverseBits(int n) {
	int y = 0;  //0000 0000 0000 0000 0000 0000
	int digit = 0;
	for (int i = 0; i < 32; i++) {
		y = y << 1; //将y左移，腾出最低位的位置
		y = y | n & 1; //将n与1做与运算，目的是为了将n的最低位复制下来，再去跟y做或运算，即把n的最低位放到y的最低位
		n = n >> 1;  //将n右移,把高位的数放到最低位来，等待下次循环和1做&操作
	}
	return y;
}

//两个用string表示的整数相加，返回用string表示的和
string addStrings(string num1, string num2) {
	string res = "";
	int size1 = num1.size();
	int size2 = num2.size();
	int i = size1 - 1;
	int j = size2 - 1;
	int incre = 0;
	while (i >= 0 && j >= 0) {
		int sum = num1[i] + num2[j] + incre - '0' - '0';
		incre = sum / 10;
		//每次都插入到前面，因为我们是从各位开始算的
		res.insert(res.begin(), sum % 10 + '0');
		i--;
		j--;
	}
	if (i < 0) {
		while (j >= 0) {
			int sum = num2[j] + incre - '0';
			incre = sum / 10;
			res.insert(res.begin(), sum % 10 + '0');
			j--;
		}
	}
	if (j < 0) {
		while (i >= 0) {
			int sum = num1[i] + incre - '0';
			incre = sum / 10;
			res.insert(res.begin(), sum % 10 + '0');
			i--;
		}
	}
	//如果最后还有进位
	if (incre != 0) {
		res.insert(res.begin(), 1+'0');
	}
	return res;
}

void SplitStringToString(const string& s, vector<std::string>& v, const string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));
}

void SplitStringToInt(const string& s, vector<int>& v, const string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(atoi(s.substr(pos1, pos2 - pos1).c_str()));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(atoi(s.substr(pos1).c_str()));
}

//sizeOfCase 测试用例个数
//myVector 每个用例里的矩阵
//allTarget 每个用例规定的达到字符的个数
void readFromTxt(int &sizeOfCase,vector<vector<vector<char>>> &allInfo, vector<int> &allTarget, string filename_in) {
	ifstream in(filename_in);// "B-small-practice.in"
	//读文件
	string line;
	if (in) {
		//第一行先读进来
		getline(in, line);
		sizeOfCase = atoi(line.c_str());
		//for (int caseMe = 0; caseMe < sizeOfCase; caseMe++) {
			vector<vector<char>> myVector;
			int count = 1;
			int sizeOfVector = 0;
			while (getline(in, line)) {
				if (sizeOfVector == 0) {
					//存储到所有信息里
					if (myVector.size() > 0) {
						allInfo.push_back(myVector);
						myVector.clear();
					}
					//开始读target
					vector<int> temp;
					SplitStringToInt(line, temp, " ");
					//记录target
					allTarget.push_back(temp[1]);
					sizeOfVector = temp[0];
				}
				else{
					vector<char> temp_char;
					for (int i = 0; line[i] != '\0'; i++) {
						temp_char.push_back(line[i]);
					}
					myVector.push_back(temp_char);
					sizeOfVector--;
				}
			}
			allInfo.push_back(myVector);
			myVector.clear();
		//}
	}
	else {
		cout << "No such file" << endl;
	}
}

//读取某一行的数据，返回是int，lineno从1开始
int readCertainLineFromTxt(string filename_in, int lineno) {
	ifstream in(filename_in);// "B-small-practice.in"
	string line;
	int count = 1;
	if (in) {
		while (getline(in, line)) {
			if (count == lineno) {
				return atoi(line.c_str());
			}
			count++;
		}
	}
	else {
		cout << "No such file" << endl;
	}
	return -1;
}

void writeToTxt(vector<vector<string>> &myVector,string filename_out) {
	ofstream out(filename_out);
	for (int i = 0; i < myVector.size(); i++) {
		string line;
		for (int j = 0; j < myVector[i].size(); j++) {
			line += myVector[i][j] + " ";
		}
		line = line.substr(0, line.size() - 1);
		out << "Case #" << i+1 << ": "<< line << endl;
		//调试用
		//cout << "Case #" << i+1 << ": " << line << endl;
	}
}

void reverseList(int &n,vector<vector<string>> &myVector) {
	string filename_in = "C:/Users/Miwa/Downloads/codejam/A-small-practice.in";
	string filename_out = "C:/Users/Miwa/Downloads/codejam/B-large-practice-out.out";
	//readFromTxt(n, myVector, filename_in);
	vector<vector<string>> result;
	for (int i = 0; i < n; i++) {
		int size_j = myVector[i].size();
		vector<string> temp = myVector[i];
		for (int j = 0; j < size_j / 2; j++) {
			temp[j] = myVector[i][size_j - j - 1];
			temp[size_j - j - 1] = myVector[i][j];
		}
		result.push_back(temp);
	}
	writeToTxt(result, filename_out);
}

//整数转字符串与字符串转整数
void intTostrToint() {
	//整数转字符串
	string s = "";
	s.append(1, 1 + '0');  //在尾部插入
	s += 1 + '0';
	s.insert(s.begin(), 1 + '0'); //在开头插入
	//字符串转整数
	int n;
	//先利用c_str()转成C string，再用atoi()或atof(),windows平台特有的，跨平台不适用。
	n = atoi(s.c_str());
	//n = stoi(s);
}

void twoSum(string filename_in,string filename_out) {
	ifstream in(filename_in);// "B-small-practice.in"
	ofstream out(filename_out);
	vector<vector<int>> products;
	int sizeOfCase = 0;
	vector<int> allTarget;
	//读文件
	string line;
	int caseMe = 0;
	if (in) {
		//第一行先读进来
		getline(in, line);
		sizeOfCase = atoi(line.c_str());
		for (int caseMe = 0; caseMe < sizeOfCase; caseMe++) {
			int count = 1;
			while (getline(in, line)) {
				if (count == 1) {
					allTarget.push_back(atoi(line.c_str()));
				}
				else if (count == 3) {
					vector<int> temp;
					SplitStringToInt(line, temp, " ");
					products.push_back(temp);
					break;
				}
				count++;
			}
		}
	}
	//开始操作
	for (int i = 0; i < sizeOfCase; i++) {
		int target = allTarget[i];
		vector<int> numbers = products[i];
		vector<int> ret;
		//新建一个map<key,value> 模式的来存储numbers里面的元素和index，
		//这里的unordered_map相当于hash_map
		unordered_map<int, int> myMap;
		for (int i = 0; i < numbers.size(); ++i)
			myMap[numbers[i]] = i;
		for (int i = 0; i < numbers.size(); ++i)
		{
			int rest_val = target - numbers[i];
			if (myMap.find(rest_val) != myMap.end())
			{
				int index = myMap[rest_val];
				if (index == i)
					continue; //如果是同一个数字， 我们就pass， 是不会取这个值的
				if (index < i)
				{
					ret.push_back(index + 1); //这里+1是因为题目说明白了要non-zero based index
					ret.push_back(i + 1);
				}
				else
				{
					ret.push_back(i + 1);
					ret.push_back(index + 1);
				}
			}
		}
		out << "Case #" << i + 1 << ": " << ret[0] << " "<< ret[1] << endl;
	}
}

void rotate(int &sizeOfCase, vector<vector<vector<char>>> &allInfo) {
	for (int i = 0; i < sizeOfCase; i++) {
		vector<vector<char>> myVector = allInfo[i];
		int size_vector = myVector.size();
		vector<vector<char>> myVectorTemp(size_vector, vector<char>(size_vector,'.'));
		for (int m = 0; m < size_vector; m++) {
			for (int n = 0; n < size_vector; n++) {
				if(myVector[m][n] != '.')
					myVectorTemp[n][size_vector - m - 1] = myVector[m][n];
			}
		}
		allInfo[i] = myVectorTemp;
	}
}

void gravity(int &sizeOfCase, vector<vector<vector<char>>> &allInfo) {
	for (int i = 0; i < sizeOfCase; i++) {
		vector<vector<char>> myVector = allInfo.at(i);
		int size_vector = myVector.size();
		for (int n = 0; n <= size_vector - 1; n++) {
			int start = 0;
			for (int m = size_vector - 1; m >=0; m--) {
				if (myVector[m][n] == '.') {
					//从上到下找到第一个slot
					if(m > start)
						start = m;
					continue;
				}
				else {
					//在slot上方找到字母了，字母可以往下移
					if (m < start) {
						myVector[start][n] = myVector[m][n];
						myVector[m][n] = '.';
						start--;
					}
				}
			}
		}
		allInfo[i] = myVector;
	}
}

bool searchRow(vector<vector<char>> &myVector, vector<vector<bool>> &visited, int row, int col, int target, char color) {
	if (target == 0)
		return true;
	if (row < 0 || col < 0 || row >= myVector.size() || col >= myVector[0].size() || visited[row][col] || myVector[row][col] != color) {
		return false;
	}

	//注意，当从这个（row,col）开始上下左右搜索的时候，本节点是访问过了的，所以要写成true
	visited[row][col] = true;
	bool res = searchRow(myVector, visited, row - 1, col, target - 1, color) ||
		searchRow(myVector, visited, row + 1, col, target - 1, color);
	//以下一个结点作为起始搜索结点时，本节点是可被访问的，理解。
	visited[row][col] = false;

	return res;
}

bool searchColumn(vector<vector<char>> &myVector, vector<vector<bool>> &visited, int row, int col, int target, char color) {
	if (target == 0)
		return true;
	if (row < 0 || col < 0 || row >= myVector.size() || col >= myVector[0].size() || visited[row][col] || myVector[row][col] != color) {
		return false;
	}

	//注意，当从这个（row,col）开始上下左右搜索的时候，本节点是访问过了的，所以要写成true
	visited[row][col] = true;
	bool res = searchColumn(myVector, visited, row, col - 1, target - 1, color) ||
		searchColumn(myVector, visited, row, col + 1, target - 1, color);
	//以下一个结点作为起始搜索结点时，本节点是可被访问的，理解。
	visited[row][col] = false;

	return res;
}

bool searchobliqueUp(vector<vector<char>> &myVector, vector<vector<bool>> &visited, int row, int col, int target, char color) {
	if (target == 0)
		return true;
	if (row < 0 || col < 0 || row >= myVector.size() || col >= myVector[0].size() || visited[row][col] || myVector[row][col] != color) {
		return false;
	}

	//注意，当从这个（row,col）开始上下左右搜索的时候，本节点是访问过了的，所以要写成true
	visited[row][col] = true;
	bool res = searchobliqueUp(myVector, visited, row - 1, col - 1, target - 1, color);
	//以下一个结点作为起始搜索结点时，本节点是可被访问的，理解。
	visited[row][col] = false;

	return res;
}

bool searchobliqueDown(vector<vector<char>> &myVector, vector<vector<bool>> &visited, int row, int col, int target, char color) {
	if (target == 0)
		return true;
	if (row < 0 || col < 0 || row >= myVector.size() || col >= myVector[0].size() || visited[row][col] || myVector[row][col] != color) {
		return false;
	}

	//注意，当从这个（row,col）开始上下左右搜索的时候，本节点是访问过了的，所以要写成true
	visited[row][col] = true;
	bool res = searchobliqueDown(myVector, visited, row + 1, col - 1, target - 1, color);
	//以下一个结点作为起始搜索结点时，本节点是可被访问的，理解。
	visited[row][col] = false;

	return res;
}

void check(string filename_in, string filename_out) {
	int sizeOfCase = 0;
	vector<vector<vector<char>>> allInfo;
	vector<int> allTarget;
	ofstream out(filename_out);
	readFromTxt(sizeOfCase, allInfo, allTarget, filename_in);
	rotate(sizeOfCase, allInfo);
	gravity(sizeOfCase, allInfo);
	for (int caseMe = 0; caseMe < sizeOfCase; caseMe++) {
		vector<vector<char>> myVector = allInfo[caseMe];
		int target = allTarget[caseMe];
		vector<vector<bool>> visitedR(myVector.size(), vector<bool>(myVector[0].size(), false));
		bool red = false;
		vector<vector<bool>> visitedB(myVector.size(), vector<bool>(myVector[0].size(), false));
		bool blue = false;
		for (int i = 0; i < myVector.size(); i++) {
			for (int j = 0; j < myVector.size(); j++) {
				red |= searchRow(myVector, visitedR, i, j, target, 'R')||
					searchColumn(myVector, visitedR, i, j, target, 'R') ||
					searchobliqueUp(myVector, visitedR, i, j, target, 'R') ||
					searchobliqueDown(myVector, visitedR, i, j, target, 'R');
				blue |= searchRow(myVector, visitedB, i, j, target, 'B') ||
					searchColumn(myVector, visitedB, i, j, target, 'B') ||
					searchobliqueUp(myVector, visitedB, i, j, target, 'B') ||
					searchobliqueDown(myVector, visitedB, i, j, target, 'B');
			}
		}
		if (red && blue) {
			out << "Case #" << caseMe + 1 << ": " << "Both" << endl;
			cout << "Case #" << caseMe + 1 << ": " << "Both" << endl;
		}
		else if (red && !blue) {
			out << "Case #" << caseMe + 1 << ": " << "Red" << endl;
			cout << "Case #" << caseMe + 1 << ": " << "Red" << endl;
		}
		else if (blue && !red) {
			out << "Case #" << caseMe + 1 << ": " << "Blue" << endl;
			cout << "Case #" << caseMe + 1 << ": " << "Blue" << endl;
		}
		else {
			out << "Case #" << caseMe + 1 << ": " << "Neither" << endl;
			cout << "Case #" << caseMe + 1 << ": " << "Neither" << endl;
		}
	}
}

int findLongestFilePath(string s) {
	int res = 0;
	int n = s.size();
	int level = 0;
	unordered_map<int, int> myMap{ {0,0} };
	for (int i = 0; i < n; i++) {
		int start = i;
		while (i < n && s[i] != '\n' && s[i] != '\t')
			i++;
		//走到了分隔符
		if (i >= n || s[i] == '\n') {
			string line = s.substr(start,i - start);
			int len = line.size();
			//现在看这一层是子目录还是文件
			if (line.find('.') != string::npos) {
				//走到文件了
				res = max(res, myMap[level] + len);
			}
			else {
				//还是目录
				level++;
				myMap[level] = myMap[level - 1] + len;
			}
			//把level置为0，下次要重算
			level = 0;
		}
		else {
			//\t分隔符表示目录深了一层，直接递增level
			level++;
		}
	}
	return res;
}

int match(vector<vector<string>> &existed, vector<string> newVector) {
	int count = 0;
	if (existed.size() == 0) 
		return newVector.size();
	if (newVector.size() == 0)
		return 0;
	int res = 65535;
	for (int i = 0; i < existed.size(); i++) {
		vector<string> temp = existed[i];
		int m = 0;
		int n = 0;
		while (m < newVector.size() && n < temp.size()) {
			if (newVector[m] != temp[n])
				break;
			else {
				m++;
				n++;
			}
		}
		if (m != newVector.size()) {
			//需要这些命令
			count = newVector.size() - m;
		}
		//m遍历完了，说明m里的元素n里都有，不需要添加了
		else{
			count = 0;
		}
		if (count < res) {
			res = count;
		}
	}
	return res;
}

//两条线是否相交
int countIntersections() {
	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
	int T, num, A, B, intersection;
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> num;
		vector<pair<int, int>> lines;
		intersection = 0;
		for (int i = 0; i < num; i++) {
			cin >> A >> B;
			lines.push_back(make_pair(A,B));
		}
		for (int j = 1; j < lines.size(); j++) {
			pair<int, int> temp = lines[j];
			for (int m = 0; m < j; m++) {
				if (temp.first > lines[m].first && temp.second < lines[m].second
					|| temp.first < lines[m].first && temp.second > lines[m].second) {
					intersection++;
				}
			}
		}
		cout << "Case #" << caseID << ": " << intersection << endl;
	}
	return intersection;
}

int filePath() {
	int T;
	int existedNO;
	int expectedNo;
	int num = 0;

	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		num = 0;
		cin >> existedNO >> expectedNo;
		vector<vector<string>> existed;
		vector<vector<string>> expected;
		for (int i = 1; i <= existedNO; i++) {
			string t;
			vector<string> temp;
			cin >> t;
			SplitStringToString(t, temp, "/");
			temp.erase(temp.begin());
			existed.push_back(temp);
		}
		for (int i = 1; i <= expectedNo; i++) {
			string t;
			vector<string> temp;
			cin >> t;
			SplitStringToString(t, temp, "/");
			temp.erase(temp.begin());
			expected.push_back(temp);
		}
		//开始匹配
		for (int n = 0; n < expected.size(); n++) {
			num += match(existed, expected[n]);
			existed.push_back(expected[n]);
		}
		cout << "Case #" << caseID << ": " << num << endl;
	}
	return num;
}

//int countTestCases() {
//	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
//	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
//	int T, L, P, C;
//	cin >> T;
//	for (int caseID = 1; caseID <= T; caseID++) {
//		cin >> L >> P >> C;
//		int n = L;
//		int count = 0;
//		if (L * C == P)
//			count = 0;
//		else {
//			while (n < P) {
//				//测试网站能不能支持n*C人
//				count++;
//				n = n * C;
//			}
//		}
//	}
//}

//int largestSize(vector<vector<int>> &sizeOfBoard, vector<vector<int>> &board,int i,int j) {
//	if (i == 0 && j == 0) {
//		sizeOfBoard[i][j] = 1;
//		return 1;
//	}
//	if (i - 1 >= 0 && j - 1 >= 0 && 
//		board[i][j] == board[i - 1][j - 1] &&
//		board[i][j] != board[i][j - 1] &&
//		board[i][j] == board[i - 1][j]) {
//		sizeOfBoard[i][j] = 1 + min(largestSize(sizeOfBoard, board, i - 1, j), 
//									largestSize(sizeOfBoard, board, i, j - 1),
//									largestSize(sizeOfBoard, board, i - 1, j - 1));
//		return sizeOfBoard[i][j];
//	}
//	return 0;
//}

//int findChessBoard() {
//	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
//	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
//	int T, ROW, COL;
//	vector<vector<int>> sizeOfBoard(ROW,vector<int>(COL,0));//存储每个节点对应的最大的棋盘大小
//	cin >> T;
//	for (int caseID = 1; caseID <= T; caseID++) {
//		vector<vector<int>> board;
//		cin >> ROW >> COL;
//		for (int i = 0; i < ROW; i++) {
//			string line;
//			cin >> line;
//			int m = 0;
//			while (line[m] != '\0') {
//				int n = line[m] - '0';
//				char str[4];
//				itoa(n, str, 2);
//				for (char c : str) {
//					board[i].push_back(c - '0');
//				}
//			}
//		}
//		//所有信息输入了
//		largestSize(sizeOfBoard, board, ROW-1, COL-1);
//
//	}
//}

void removeBlank(string &str) {
	int begin = 0;
	begin = str.find("*", begin);  //查找*在str中第一次出现的位置
	while (begin != -1)  //表示字符串中存在空格
	{
		str.replace(begin, 1, "....");  // 用空串替换str中从begin开始的1个字符
		begin = str.find("*", begin);  //查找空格在替换后的str中第一次出现的位置
	}
}

void WhoIsLeader(){
	int T;
	int num;
	string empty;

	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> num;
		getline(cin, empty);
		int current = 0;
		int res = 0;
		string res_name;
		for (int i = 1; i <= num; i++) {
			string line, lineOld;
			int m = 0;
			getline(cin, line);
			lineOld = line;
			removeBlank(line);
			//开始判断
			unordered_map<char, int> myMap;
			while (line[m] != '\0') {
				myMap[line[m]]++;
				m++;
			}
			current = myMap.size();
			if (current > res || (current == res && res_name > lineOld)) {
				res = current;
				res_name = lineOld;
			}
		}
		cout << "Case #" << caseID << ": " << res_name << endl;
	}
}

void voters() {
	int T;
	int num;
	string empty;
	int M, N;
	double res;

	freopen("C:/Users/Miwa/Downloads/codejam/B-small-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/B-small-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> N >> M;
		if (M == 0 && N != 0) {
			res = (double)1.00000000;
			cout << "Case #" << caseID << ": " << fixed << setprecision(8) << res << endl;
			continue;
		}
		vector<vector<double>> probability(M+1, vector<double>(N+1,0));
		probability[0][0] = 1;
		int i = 0;
		int j = 0;
		//i= 0边界
		for (j = 1; j <= N; j++) {
			probability[0][j] = probability[0][j - 1] * 0.5;
		}
		//除边界的中间部分
		for (i = 1; i < M; i++) {
			for (j = i + 1; j < N; j++) {
				probability[i][j] = (probability[i - 1][j] + probability[i - 1][j - 1]) * 0.5;
			}
		}
		//j = N边界
		for (i = 1; i < M; i++) {
			probability[i][N] = probability[i - 1][N] + probability[i][N - 1] * 0.5;
		}

		//i= M的边界
		for (j = M + 1; j <= N; j++) {
			probability[M][j] = probability[M][j - 1] + probability[M - 1][j] * 0.5;
		}

		cout << "Case #" << caseID << ": ";
		cout << fixed <<setprecision(8) << probability[M][N] << endl;
	}
}

void parentheses() {
	int T;
	int num;
	string empty;
	unsigned long long int L, R, n, result;

	freopen("C:/Users/Miwa/Downloads/codejam/C-large-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/C-large-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> L >> R;
		n = min(L, R);
		if (L > R)
			n = R;
		else
			n = L;
		result = (n / 2) * (n + 1);
		cout << "Case #" << caseID << ": " << result << endl;
	}
}

void rain() {
	int T;
	int num;
	string empty,line;
	int ROW, COL;

	freopen("C:/Users/Miwa/Downloads/codejam/B-large-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/B-large-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> ROW >> COL;
		int num = 0;
		getline(cin, empty);
		vector<vector<int>> board(ROW,vector<int>(COL));
		for (int i = 0; i < ROW; i++) {
			getline(cin, line);
			vector<int> temp;
			SplitStringToInt(line, temp," ");
			board.push_back(temp);
		}
		for (int i = 1; i < ROW - 1; i++) {

		}

	}
}

//int main() {
	//repeatedSubstringPattern("abcabcabc");
	//string s = "ababab";
	//Algorithm2 a2;
	////cout << a2.ifRepeatedPattern(s) << endl;;
	//vector<pair<int, int> > edges(5);
	//edges[0] = make_pair(0, 0);
	//edges[1] = make_pair(1, 0);
	//edges[2] = make_pair(-1, 0);
	//edges[3] = make_pair(0, 1);
	//edges[4] = make_pair(0, -1);
	////cout<<numberOfBoomerangs(edges);
	////findMinHeightTrees(4,edges);
	//int a[5][5] = { { 0, 0, 1, 0, 0 },
	//{ 0, 0, 0, 0, 0 },
	//{ 0, 0, 0, 1, 0 },
	//{ 1, 1, 0, 1, 1 },
	//{ 0, 0, 0, 0, 0 }
	//};
	//vector<vector<int>> maze(5, vector<int>(5));
	//for (int i = 0; i < 5; i++) {
	//	for (int j = 0; j < 5; j++) {
	//		maze[i][j] = a[i][j];
	//	}
	//}
	//vector<int> start(2), end(2);
	//start[0] = 0;
	//start[1] = 4;
	//end[0] = 4;
	//end[1] = 4;
	//cout << "Haspath:" << endl;
	////cout << hasPath(maze, start, end) << endl;
	//int numCourses = 4;
	//vector<pair<int, int>> prerequisites(4);
	//prerequisites[0] = make_pair(1, 0);
	//prerequisites[1] = make_pair(2, 0);
	//prerequisites[2] = make_pair(3, 2);
	//prerequisites[3] = make_pair(3, 1);
	//cout << canFinishRecursion(numCourses, prerequisites);
	//cout << longestPalindrome("babcbabcbaccba ");
	//cout << isPalindrome("0P");
	//cout << addStrings("9133", "0");
	////int n = 0;
	////vector<vector<string>> myVector;
	//////reverseList(n,myVector);
	////string filename_in = "C:/Users/Miwa/Downloads/codejam/A-large-practice.in";
	////string filename_out = "C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out";
	//////twoSum(filename_in, filename_out);
	//////check(filename_in, filename_out);
	////string filepath = "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext";
	////cout << findLongestFilePath(filepath);
	//countIntersections();
	//WhoIsLeader();
	//voters();
	//parentheses();
	//freopen("C:/Users/Miwa/Downloads/codejam/length of data type.out", "w", stdout);
	//cout << "type: \t\t" << "************size**************" << endl;
	//cout << "bool: \t\t" << "所占字节数：" << sizeof(bool);
	//cout << "\t最大值：" << (numeric_limits<bool>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<bool>::min)() << endl;
	//cout << "char: \t\t" << "所占字节数：" << sizeof(char);
	//cout << "\t最大值：" << (numeric_limits<char>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<char>::min)() << endl;
	//cout << "signed char: \t" << "所占字节数：" << sizeof(signed char);
	//cout << "\t最大值：" << (numeric_limits<signed char>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<signed char>::min)() << endl;
	//cout << "unsigned char: \t" << "所占字节数：" << sizeof(unsigned char);
	//cout << "\t最大值：" << (numeric_limits<unsigned char>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<unsigned char>::min)() << endl;
	//cout << "wchar_t: \t" << "所占字节数：" << sizeof(wchar_t);
	//cout << "\t最大值：" << (numeric_limits<wchar_t>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<wchar_t>::min)() << endl;
	//cout << "short: \t\t" << "所占字节数：" << sizeof(short);
	//cout << "\t最大值：" << (numeric_limits<short>::max)();
	//cout << "\t\t最小值：" << (numeric_limits<short>::min)() << endl;
	//cout << "int: \t\t" << "所占字节数：" << sizeof(int);
	//cout << "\t最大值：" << (numeric_limits<int>::max)();
	//cout << "\t最小值：" << (numeric_limits<int>::min)() << endl;
	//cout << "unsigned: \t" << "所占字节数：" << sizeof(unsigned);
	//cout << "\t最大值：" << (numeric_limits<unsigned>::max)();
	//cout << "\t最小值：" << (numeric_limits<unsigned>::min)() << endl;
	//cout << "long: \t\t" << "所占字节数：" << sizeof(long);
	//cout << "\t最大值：" << (numeric_limits<long>::max)();
	//cout << "\t最小值：" << (numeric_limits<long>::min)() << endl;
	//cout << "unsigned long: \t" << "所占字节数：" << sizeof(unsigned long);
	//cout << "\t最大值：" << (numeric_limits<unsigned long>::max)();
	//cout << "\t最小值：" << (numeric_limits<unsigned long>::min)() << endl;
	//cout << "double: \t" << "所占字节数：" << sizeof(double);
	//cout << "\t最大值：" << (numeric_limits<double>::max)();
	//cout << "\t最小值：" << (numeric_limits<double>::min)() << endl;
	//cout << "long double: \t" << "所占字节数：" << sizeof(long double);
	//cout << "\t最大值：" << (numeric_limits<long double>::max)();
	//cout << "\t最小值：" << (numeric_limits<long double>::min)() << endl;
	//cout << "float: \t\t" << "所占字节数：" << sizeof(float);
	//cout << "\t最大值：" << (numeric_limits<float>::max)();
	//cout << "\t最小值：" << (numeric_limits<float>::min)() << endl;
	//cout << "size_t: \t" << "所占字节数：" << sizeof(size_t);
	//cout << "\t最大值：" << (numeric_limits<size_t>::max)();
	//cout << "\t最小值：" << (numeric_limits<size_t>::min)() << endl;
	//cout << "string: \t" << "所占字节数：" << sizeof(string) << endl;
	//// << "\t最大值：" << (numeric_limits<string>::max)() << "\t最小值：" << (numeric_limits<string>::min)() << endl;  
	//cout << "type: \t\t" << "************size**************" << endl;
	//voters();
//}