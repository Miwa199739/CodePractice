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
//跟之前那到课程清单的题一样，我们需要建立一个图g，是一个二维数组，其中g[i]是一个一维数组，保存了i节点可以到达的所有节点。我们开始将所有只有一个连接边的节点(叶节点)都存入到一个队列queue中，然后我们遍历每一个叶节点，通过图来找到和其相连的节点，并且在其相连节点的集合中将该叶节点删去，如果删完后此节点也也变成一个叶节点了，加入队列中，再下一轮删除。
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

//这道题定义了一种类似回旋镖形状的三元组结构，要求第一个点和第二个点之间的距离跟第一个点和第三个点之间的距离相等。现在给了我们n个点，让我们找出回旋镖的个数。那么我们想，如果我们有一个点a，还有两个点b和c，如果ab和ac之间的距离相等，那么就有两种排列方法abc和acb；如果有三个点b，c，d都分别和a之间的距离相等，那么有六种排列方法，abc, acb, acd, adc, abd, adb，那么是怎么算出来的呢，很简单，如果有n个点和a距离相等，那么排列方式为n(n-1)，这属于最简单的排列组合问题了，我大天朝中学生都会做的。那么我们问题就变成了遍历所有点，让每个点都做一次点a，然后遍历其他所有点，统计和a距离相等的点有多少个，然后分别带入n(n-1)计算结果并累加到res中，只有当n大于等于2时，res值才会真正增加，
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


//
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
		//重叠了，更新result.back
		else
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
			//注意这里，我们更新result.back().end的值是为了保证把覆盖面最大的那个interval踢掉，
			//以免它继续跟下面的interval覆盖，这样能保证我们踢掉的interval数量最小
			result.back().end = min(result.back().end, intervals[i].end);
			num++;
		}
		else
			result.push_back(intervals[i]);
	}
	return num;
}

//给一个长度为n的数组和一个长度为k的增量规则向量，用增量规则对数组进行更新，返回新的数组，要求O（k+n）的时间复杂度和额外的O（1）的空间复杂度
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

bool hasPathHelperRecurion(vector<vector<int>>& maze, vector<vector<int>>& dp, vector<vector<bool>> &visited, int start_i, int start_j, int end_i, int end_j) {
	if (start_i == end_i && start_j == end_j)
		return true;
	//start_i，start_j这个点上次来过，不用再重复访问了，直接返回我们保存啊后的中间值
	if (dp[start_i][start_j] != -1)
		return dp[start_i][start_j];

	bool res = false;
	visited[start_i][start_j] = true;
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

struct TreeNode
{
	int self; //数据
	TreeNode *left; //左节点
	TreeNode * right; //右节点
};

//二叉树的竖直遍历
//基于广度优先遍历，在遍历过程中要给每个元素给一个columnno,左子节点的编号是父节点编号减一，右子节点编号是根节点编号加一，最后根据编号组织vector返回
vector<vector<int>> verticalOrder(TreeNode* root) {
	map<int, vector<int>> myMap;
	vector<vector<int>> result;
	int column_no = 0;
	queue<pair<int, TreeNode*>> myQueue;
	myQueue.push(make_pair(0, root));

	while (!myQueue.empty()) {
		TreeNode * current = myQueue.front().second;
		column_no = myQueue.front().first;
		myQueue.pop();
		myMap[column_no].push_back(current->self);
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
		//如果这个节点没放稳过，那么他肯定在另一个连通区域内，这时我们增加计数，开始从这个节点进行DFS遍历
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
bool canFinishIterative(int numCourses, vector<pair<int, int>>& prerequisites) {
	//二维数组存储有向图
	vector<vector<int>> myVector(numCourses, vector<int>(0));
	//存储每个节点的入度
	vector<int> in(numCourses, 0);

	//初始化
	for (auto a : prerequisites) {
		myVector[a.second].push_back(a.first);
		in[a.first]++;
	}

	//判断一个节点是否访问过,初始化为false;
	vector<bool> visited(numCourses, false);

	queue<int> myQueue;
	//把所有入度为0的点push进去
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

bool canFinishRecursionHelper(vector<vector<int> > &myVector, vector<int> &visited, int i) {
	if (visited[i] == -1)  //已经访问过了，还没确定是否有回路
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
// @return -1 if my number is lower, 1 if my number is higher, otherwise return 0
int guess(int num);

//为啥不对？
int guessNumber(int n) {
	int result = n;
	if (guess(result) == 1) {
		return guessNumber(result++);
	}
	else if (guess(result) == -1) {
		return guessNumber(result--);
	}
	else
		return result;
}

//二分法找
int guessNumber(int n) {
	int high = n;
	int low = 1;
	int mid;
	while (low <= n) {
		mid = low + (high - low) / 2;
		if (guess(mid) == 1)
			low = mid + 1;
		else if (guess(mid) == -1)
			high = mid - 1;
		else
			return mid;
	}
	return -1;
}

//是否为2的幂次方
bool isPowerOfTwo(int n) {
	return (n > 0) && (!(n & (n - 1)));
}

//是否为3的幂次方
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
	return (count == 1 && times % 2 == 0);
}

//数组中出了一个元素出现一次，其他元素都出现两次，找到这个元素
//利用异或操作的属性，可交换性
int singleNumber(vector<int>& nums) {
	int result = 0;
	for (int i = 0; i<nums.size(); i++) {
		result ^= nums[i];
	}
	return result;
}

//数组中出了一个元素出现一次，其他元素都出现三次，找到这个元素
int singleNumberII(vector<int>& nums) {
	int n = nums.size();
	if (n = 0) return -1;
	if (n == 1) return nums[0];
	int count = 0;;
	//先给数组进行排序
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

//
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<string> binaryTreePaths(TreeNode* root) {
	vector<string> result;
	treePaths(root, result, "");
	return result;
}

void treePaths(TreeNode* root, vector<string> &result, string str) {
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

int main() {
	//repeatedSubstringPattern("abcabcabc");
	string s = "ababab";
	Algorithm2 a2;
	//cout << a2.ifRepeatedPattern(s) << endl;;
	vector<pair<int, int> > edges(5);
	edges[0] = make_pair(0, 0);
	edges[1] = make_pair(1, 0);
	edges[2] = make_pair(-1, 0);
	edges[3] = make_pair(0, 1);
	edges[4] = make_pair(0, -1);
	//cout<<numberOfBoomerangs(edges);
	//findMinHeightTrees(4,edges);
	int a[5][5] = { { 0, 0, 1, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 0 },
	{ 1, 1, 0, 1, 1 },
	{ 0, 0, 0, 0, 0 }
	};
	vector<vector<int>> maze(5, vector<int>(5));
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			maze[i][j] = a[i][j];
		}
	}
	vector<int> start(2), end(2);
	start[0] = 0;
	start[1] = 4;
	end[0] = 4;
	end[1] = 4;
	cout << "Haspath:" << endl;
	//cout << hasPath(maze, start, end) << endl;
	int numCourses = 4;
	vector<pair<int, int>> prerequisites(4);
	prerequisites[0] = make_pair(1, 0);
	prerequisites[1] = make_pair(2, 0);
	prerequisites[2] = make_pair(3, 2);
	prerequisites[3] = make_pair(3, 1);
	cout << canFinishRecursion(numCourses, prerequisites);
	system("pause");
}