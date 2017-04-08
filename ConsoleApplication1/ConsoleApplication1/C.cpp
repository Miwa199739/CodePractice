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
using namespace std;

double dp[1000010];
//滑动解锁
int T, num, A, B, cnt, aim_depth;
string line;
int myMap[10][10];
int visited[10];
int record[10][10];

void init()
{
	record[1][3] = record[3][1] = record[1][7] = record[7][1] = 1;
	record[1][9] = record[9][1] = record[3][7] = record[7][3] = 1;
	record[9][3] = record[3][9] = record[9][7] = record[7][9] = 1;
	record[2][8] = record[8][2] = record[4][6] = record[6][4] = 1;
}

void dfsForCount(int cur, int depth, int edge) {
	//找到的条件是：把小明看到的边都用上了，并且符合目前要求的节点数
	if (depth == aim_depth && edge == num) {
		cnt++;
		return;
	}

	for (int i = 1; i < 10; i++) {
		if (!visited[i]) {
			if (record[cur][i] && !visited[(cur + i) / 2])
				continue;
			visited[i] = 1;
			//是myMap里的边
			if (myMap[cur][i])
				dfsForCount(i, depth + 1, edge + 1);
			//不是myMap里的边
			else
				dfsForCount(i, depth + 1, edge);
			visited[i] = 0;
		}
	}

}

void unlock() {
	init();
	freopen("D:/offer/Microsoft/a.txt", "r", stdin);
	freopen("D:/offer/Microsoft/a.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> num;
		if (num == 0) {
			cout << 389112 << endl;
			continue;
		}
		memset(visited, 0, sizeof(visited));
		memset(myMap, 0, sizeof(myMap));

		//二维数组存储有向图
		vector<vector<int>> myVector(num, vector<int>(0));
		for (int i = 1; i <= num; i++) {
			//初始化
			cin >> A >> B;
			myMap[A][B] = myMap[B][A] = 1;
		}
		cnt = 0;
		//这层循环控制节点数，范围是从max(4, num + 1)到9
		for (aim_depth = max(4, num); aim_depth <= 9; aim_depth++) {
			//从每个点开始进行dfs
			for (int i = 1; i <= 9; i++) {
				visited[i] = 1;
				dfsForCount(i, 1, 0);
				visited[i] = 0;
			}
		}
		cout << cnt << endl;
	}
}

//出勤记录1
void attendanceRecord() {
	freopen("D:/offer/Microsoft/a.txt", "r", stdin);
	freopen("D:/offer/Microsoft/a.out", "w", stdout);
	cin >> T;
	string line;
	bool res = true;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> line;
		if (count(line.begin(), line.end(), 'A') > 1) {
			cout << "NO" << endl;
			continue;
		}
		int count = 0;
		int i = 0;
		for (i = 0; i < line.length(); i++) {
			if (line[i] == 'L') {
				count++;
				if (count == 3) {
					cout << "NO" << endl;
					break;
				}
			}
			else {
				count = 0;
			}
		}
		if (i == line.length())
			cout << "YES" << endl;
	}
}

//判断记录是否合格
bool isAttendanceValid(string line) {
	if (count(line.begin(), line.end(), 'A') > 1) {
		return false;
	}
	int count = 0;
	int i = 0;
	for (i = 0; i < line.length(); i++) {
		if (line[i] == 'L') {
			count++;
			if (count == 3) {
				return false;
			}
		}
		else {
			count = 0;
		}
	}
	return true;
}


int countOfValid = 0;
vector<int> LAO = { 'L','A','O' };

void dfsForAttendance(string& str) {
	int l = str.length();
	if (str.length() == T) {
		if (isAttendanceValid(str))
			countOfValid++;
		return;
	}
	for (auto a : LAO) {
		str.push_back(a);
		dfsForAttendance(str);
		str.pop_back();
	}
	return;
}

//给定长度，判断有哪些是合格的
//求出全排列，把不合格的筛选掉
int attendanceRecordII() {
	freopen("D:/offer/Microsoft/a.txt", "r", stdin);
	freopen("D:/offer/Microsoft/a.out", "w", stdout);
	cin >> T;
	string str = "";
	dfsForAttendance(str);
	cout << countOfValid << endl;
	return countOfValid;
}


//hiho字符串
int charOf[256];
int ans = 1000000;
void hihoStr() {
	freopen("D:/offer/Microsoft/a.txt", "r", stdin);
	freopen("D:/offer/Microsoft/a.out", "w", stdout);
	string str = "";
	cin >> str;
	int len = str.length();

	memset(charOf, 0, sizeof(charOf));

	for (int i = 0, j = 0; i < len; i++) {
		while (j < len && (charOf['h'] < 2 || charOf['i'] < 1 || charOf['o'] < 1)) {
			charOf[str[j]]++;
			j++;
			//一旦发现不满足条件了，以i开头的子串不满足，直接break
			if (charOf['h'] > 2 || charOf['i'] > 1 || charOf['o'] > 1)
				break;
		}

		if (charOf['h'] == 2 && charOf['i'] == 1 && charOf['o'] == 1) {
			ans = min(ans, j - i);
		}

		charOf[str[i]]--;
	}
	if (ans == 1000000)
		cout << "-1" << endl;
	else
		cout << ans << endl;
	return;
}

int valuehelper(vector<int>& nums, int l, int r) {
	int res = 0;
	unordered_map<int, int> myMap;
	for (int i = l; i <= r; i++) {
		myMap[nums[i]]++;
	}

	for (auto a : myMap) {
		res += (a.second * (a.second - 1)) / 2;
	}

	return res;
}

//区间价值
void valueOfInterval() {
	freopen("D:/offer/Microsoft/a.txt", "r", stdin);
	freopen("D:/offer/Microsoft/a.out", "w", stdout);
	cin >> T;
	int n, k;
	string line = "";
	string empty = "";
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> n >> k;
		getline(cin, empty);
		getline(cin, line);
		//第k小的值，用优先队列来做，我们始终维持这个优先队列里有k个数，最后把堆顶返回就好了
		priority_queue <int, vector<int>> q;
		vector<int> nums;
		//SplitStringToIntII(line, nums, " ");
		for (int i = 0; i < n; i++) {
			for (int j = i; j < n; j++) {
				int cur = valuehelper(nums, i, j);
				//如果当前队列个数小于k
				if (q.size() < k) {
					q.push(cur);
				}
				//队列个数等于k,开始比较谁更小
				else if (cur < q.top()) {
					q.push(cur);
					q.pop();
				}
			}
		}
		if (q.size() == k)
			cout << q.top() << endl;
		else
			cout << 0 << endl;
	}
}
//dp[n] = (dp[n-1]+1)*p+(dp[n-1]+1)*(100-p)*(p+q)+(dp[n-1]+3)*(100-(p+q))*(p+2q)+...(dp[n-1]+level)*(100-(level-2)*(p+q))*(p+(level-1)*q)
//直到p+(level-1)*q大于等于100
int legendaryItems() {
	int n, p, q;
	cin >> p >> q >> n;
	memset(dp, 0, sizeof(dp));
	dp[0] = 0;

	for (int i = 1; i <= n; i++) {
		//走到每层的概率
		int gailv = floor(p / pow(2, n - i));
		double acc_gailv = 1.0;
		int lev = 1;
		while (gailv <= 100) {
			dp[i] += (double(gailv) / 100) * acc_gailv * (dp[i - 1] + lev);
			if (gailv == 100)
				break;
			acc_gailv *= (double)(100 - gailv) / 100;
			lev++;
			gailv = ((gailv + q) > 100) ? 100 : (gailv + q);
		}
	}
	printf("%.2f", dp[n]);
	return 0;
}