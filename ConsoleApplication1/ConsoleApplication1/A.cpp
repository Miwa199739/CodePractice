#include "stdafx.h"
#include <cstring>
#include <vector>
#include <list>
#include <queue>
#include <map>
#include <stack>
#include <unordered_set>
#include <iostream>
#include <unordered_map>
#include <stdio.h>
#include <iomanip>
#include <cmath>
#include <sstream>
#include "Algorithm2.h"

using namespace std;

#define MAX_INT 65535

//从字母获得电话号码
void gettingDigits() {
	int T;
	string line;

	//测试用
	//freopen("C:/Users/Miwa/Downloads/codejam/test.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/A-small-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/A-small-practice-out.out", "w", stdout);
	cin >> T;
	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> line;
		unordered_map<char, int> myMap = { {0,0} };
		for (int i = 0; line[i] != '\0'; i++) {
			myMap[line[i]]++;
		}
		string res;
		while (myMap['Z'] > 0 && myMap['E'] > 0 && myMap['R'] > 0 && myMap['O'] > 0) {
			myMap['Z']--;
			myMap['E']--;
			myMap['R']--;
			myMap['O']--;
			res.append(1,'0');
		}
		while (myMap['O'] > 0 && myMap['N'] > 0 && myMap['E'] > 0) {
			myMap['O']--;
			myMap['N']--;
			myMap['E']--;
			res.append(1, '1');
		}
		while (myMap['T'] > 0 && myMap['W'] > 0 && myMap['O'] > 0) {
			myMap['T']--;
			myMap['W']--;
			myMap['O']--;
			res.append(1, '2');
		}
		while (myMap['T'] > 0 && myMap['H'] > 0 && myMap['R'] > 0 && myMap['E'] > 1) {
			myMap['T']--;
			myMap['H']--;
			myMap['R']--;
			myMap['E']--;
			myMap['E']--;
			res.append(1, '3');
		}
		while (myMap['F'] > 0 && myMap['O'] > 0 && myMap['U'] > 0 && myMap['R']> 0) {
			myMap['F']--;
			myMap['O']--;
			myMap['U']--;
			myMap['R']--;
			res.append(1, '4');
		}
		while (myMap['F'] > 0 && myMap['I'] > 0 && myMap['V'] > 0 && myMap['E']> 0) {
			myMap['F']--;
			myMap['I']--;
			myMap['V']--;
			myMap['E']--;
			res.append(1, '5');
		}
		while (myMap['S'] > 0 && myMap['I'] > 0 && myMap['X'] > 0) {
			myMap['S']--;
			myMap['I']--;
			myMap['X']--;
			res.append(1, '6');
		}
		while (myMap['S'] > 0 && myMap['E'] > 0 && myMap['V'] > 0 && myMap['E'] > 0 && myMap['N']> 0) {
			myMap['S']--;
			myMap['E']--;
			myMap['V']--;
			myMap['E']--;
			myMap['N']--;
			res.append(1, '7');
		}
		while (myMap['E'] > 0 && myMap['I'] > 0 && myMap['G'] > 0 && myMap['H'] > 0 && myMap['T']> 0) {
			myMap['E']--;
			myMap['I']--;
			myMap['G']--;
			myMap['H']--;
			myMap['T']--;
			res.append(1, '8');
		}
		while (myMap['N'] > 1 && myMap['I'] > 0  && myMap['E']> 0) {
			myMap['N']--;
			myMap['I']--;
			myMap['N']--;
			myMap['E']--;
			res.append(1, '9');
		}
		cout << "Case #" << caseID << ": " << res << endl;
	}
}

//flag = 0:str1[0] = 0;str2[0] = 1;
//flag = 1:str1[0] = 1;str2[0] = 0;
//flag = 2:str1[0] = str2[0] = 0;
long long calculate(string &str1,string &str2,int flag) {
	int i = 0, j = 0;
	while (i < str1.length() && j < str2.length()) {

		if (str1[i] != '?' && str2[j] == '?') {
			if (i == 0 && j == 0) {
				str2[j] = str1[i];
				continue;
			}

			auto temp1 = stoll(str1.substr(0, i));
			auto temp2 = stoll(str2.substr(0, j));
			if (temp1 < temp2) {
				str2[j] = 0 + '0';
			}
			else if (temp1 > temp2) {
				str2[j] = 9 + '0';
			}
			else {
				str2[j] = str1[i];
			}
		}
		else if (str1[i] == '?' && str2[j] != '?') {
			if (i == 0 && j == 0) {
				str1[i] = str2[j];
				continue;
			}

			auto temp1 = stoll(str1.substr(0, i));
			auto temp2 = stoll(str2.substr(0, j));
			if (temp1 < temp2) {
				str1[i] = 9 + '0';
			}
			else if (temp1 > temp2) {
				str1[i] = 0 + '0';
			}
			else {
				str1[i] = str2[j];
			}
		}
		else if (str1[i] == '?' && str2[j] == '?') {
			//res[i][j] = res[i - 1][j - 1] * 10 + abs(str1[i] - str2[j]);
			if (i == 0 && j == 0) {
				if (flag == 0) {
					str1[i] = 0 + '0';
					str2[j] = 1 + '0';
				}
				else if (flag == 1) {
					str1[i] = 1 + '0';
					str2[j] = 0 + '0';
				}
				else if (flag == 2) {
					str1[i] = str2[j] = 0 + '0';
				}
			}
			else {
				auto temp1 = stoll(str1.substr(0, i));
				auto temp2 = stoll(str2.substr(0, j));
				if (temp1 == temp2) {
					str1[i] = 0 + '0';
					str2[j] = 0 + '0';
				}
				else if (temp1 > temp2) {
					str1[i] = 0 + '0';
					str2[j] = 9 + '0';
				}
				else if (temp1 < temp2) {
					str1[i] = 9 + '0';
					str2[j] = 0 + '0';
				}
			}
		}
		i++;
		j++;
	}
	return abs(stoll(str1) - stoll(str2));
}

//猜两个数字使其差值最小
void closeMatch() {
	int T;
	string line;

	//测试用
	//freopen("C:/Users/Miwa/Downloads/codejam/test.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/B-small-practice.in", "r", stdin);
	freopen("C:/Users/Miwa/Downloads/codejam/B-small-practice-out.out", "w", stdout);
	cin >> T;
	string str1, str2, temp1, temp2,temp3,temp4;;

	for (int caseID = 1; caseID <= T; caseID++) {
		cin >> str1 >> str2;

		temp3 = temp1 = str1;
		temp2 = temp4 = str2;

		vector<vector<int>> res(18,vector<int>(18,MAX_INT));
		long long diff1 = calculate(str1, str2, 0);
		long long diff2 = calculate(temp1, temp2, 1);
		long long diff3 = calculate(temp3, temp4, 2);
		if (diff1 <= min(diff2, diff3)) {
			cout << "Case #" << caseID << ": " << str1 << " " << str2 << endl;
		}
		else if (diff3 <= min(diff1, diff2)) {
			cout << "Case #" << caseID << ": " << temp3 << " " << temp4 << endl;
		}
		else if (diff2 <= min(diff1, diff3)) {
			cout << "Case #" << caseID << ": " << temp1 << " " << temp2 << endl;
		}
	}
}

//阶乘函数
int fac(int n) {
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	int res = 1;
	while (n > 1) {
		res *= n;
		n--;
	}
	return res;
}

//翻转nums从begin end之间的元素
void reverse(vector<int> &nums, int begin, int end) {
	int f = begin;
	int e = end;
	int temp = 0;
	vector<int> newInt = nums;
	if (begin == end)
		return;
	int len = (end - begin) / 2;
	for(int i = begin; i <= begin + len; i++) {
		nums[i] = newInt[end - i + begin];
		nums[end - i + begin] = newInt[i];
	}
}

//字典序的下一个排列
vector<int> nextPermutation(vector<int>& nums) {
	int i = nums.size() - 1;
	int j = 0;

	//是全部相同的数字
	int n;
	for (n = 0; n < nums.size() - 1;n++) {
		if (nums[n] != nums[n + 1])
			break;
	}
	if (n == nums.size() - 1)
		return nums;

	//找最后一个升序的位置(i,i+1)
	while (i > 0) {
		if (nums[i - 1] >= nums[i]) {
			i--;
		}
		else
			break;
	}

	//是降序排列的数字
	if (i == 0 && nums[i] >= nums[i + 1])
		return nums;

	//找到最后一个升序后面比i-1大的数字
	j = nums.size() - 1;
	while (j > i - 1) {
		if (nums[j] <= nums[i-1])
			j--;
		else
			break;
	}
	//j与i对应的值交换
	swap(nums[j], nums[i - 1]);
	//i后面的数全部反转排列
	reverse(nums, i, nums.size() - 1);
	return nums;
}

void print(vector<int>& nums) {
	for (int a : nums) {
		cout << a << " ";
	}
	cout << endl;
}

//定义比较函数
static bool compare(int a, int b) {
	return a > b;
}

//找出一串数字的全排列组合
vector<vector<int>> permute(vector<int>& nums) {
	//初始状态从升序开始
	sort(nums.begin(), nums.end());
	vector<int> nummsNew = nums;
	sort(nummsNew.begin(), nummsNew.end(), compare);
	int size_N = nums.size();
	vector<vector<int>> res;
	res.push_back(nums);
	for (int i = 0; i < fac(size_N); i++) {
		print(nums);
		if (nums == nummsNew)
			break;
		res.push_back(nextPermutation(nums));
	}
	return res;
}

//全排列DFS解法
void dfsForPermute(vector<int>& nums,vector<int> &str, vector<vector<int>> result) {
	if (str.size() == nums.size()) {
		result.push_back(str);
		return;
	}
	for (auto a : nums) {
		if (find(str.begin(), str.end(), a) == str.end()) {
			str.push_back(a);
			dfsForPermute(nums, str, result);
			str.pop_back();
		}
	}
}

vector<vector<int>> permuteII(vector<int>& nums) {
	vector<vector<int>> result;
	vector<int> str;
	if (nums.empty())
		return result;
	dfsForPermute(nums, str,result);
	return result;
}


//反转一个字符串，较快的解法
void reverseStr(string s) {
	int len = s.length();
	string newstr = s;
	for (int i = 0; i < len / 2; i++) {
		newstr[i] = s[len - i - 1];
		newstr[len - i - 1] = s[i];
	}
	cout << newstr << endl;
}

//移除几位，使数变得最小
string removeKdigits(string num, int k) {
	int n = num.length();
	int remain = n - k;
	string res = "";
	for (char c : num) {
		while (k && res.size() && res[res.size() - 1] > c) {
			res.pop_back();
			k--;
		}
		res.push_back(c);
	}
	//有可能最后一个数字还不满足要求，直接把string裁剪到n-k大小就好了
	res.resize(remain);
	while (!res.empty() && res[0] == 0)
		res.erase(res.begin());
	return res;
}

//一个数组只留下m个数，得到的值是最大的
vector<int> maxValue(vector<int> nums,int m) {
	vector<int> res;
	if (m >= nums.size())
		return nums;
	if (m == 0)
		return res;
	//要移除的元素个数
	int dele = nums.size() - m;
	for (auto a:nums) {
		while (!res.empty() && a > res.back() && dele) {
			res.pop_back();
			dele--;
		}
		res.push_back(a);
	}
	//保留m个
	res.resize(m);
	return res;
}

vector<int> mergeVector(vector<int> nums1, vector<int> nums2) {
	vector<int> res;
	while (nums1.size() + nums2.size()) {
		vector<int> &temp = nums1 > nums2 ? nums1 : nums2;  //temp是引用，无需额外空间
		res.push_back(temp[0]);
		temp.erase(temp.begin());
	}
	return res;
}

//从两个向量中选出k个数字，组成最大的整数
vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
	vector<int> res;
	int i;
	for (i = 0; i <= k; i++) {
		//注意：分三种情况：
		//1、只从nums1中取
		//2、只从nums2中取
		//3、从两个里面都取，但分别取多少个要循环计算。
		vector<int> temp1 = maxValue(nums1, i);
		vector<int> temp2 = maxValue(nums2, k - i);
		//不能先merge再开始计算，这样得到的值未必是最大的。
		vector<int> temp3 = mergeVector(temp1, temp2);
		if(temp3.size() == k)
			res = max(res, temp3);
	}
	return res;
}

vector<string> myVector = { " ","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz" };

void combine(string &digits, int cur, string str, vector<string> &result) {
	if (cur == digits.size()) {
		cout << str << endl;
		result.push_back(str);
		return;
	}
	for (auto a : myVector[digits[cur] - '0' + 1]) {
		combine(digits, cur + 1, str + a, result);
	}
} 

//字母组合,注意因为这道题是一直往一个方向的dfs，所以我们要设置变量记录当前处理的下标，然后每一迭代都把下标加一
vector<string> letterCombinations(string digits) {
	vector<string> res;
	string str;
	if (digits.size() == 0)
		return{};
	combine(digits, 0, str, res);
	return res;
}

void dfs(vector<vector<int>>& matrix,int row,int rowlen,int col,int collen,vector<int> &res) {
	if (rowlen <= 0 || collen <= 0)
		return;

	//只有一行
	if (rowlen == 1) {
		for (int j = col; j < col + collen; j++) {
			res.push_back(matrix[row][j]);
		}
		return;
	}
	//只有一列
	if (collen == 1) {
		for (int i = row; i < row + rowlen; i++) {
			res.push_back(matrix[i][col]);
		}
		return;
	}

	//最上面一排
	for (int j = col; j < col + collen - 1; j++) {
		res.push_back(matrix[row][j]);
	}
	//最左边一排
	for (int i = row; i < row + rowlen - 1; i++) {
		res.push_back(matrix[i][col + collen - 1]);
	}
	//最下面一排
	for (int j = col + collen - 1; j > col; j--) {
		res.push_back(matrix[row + rowlen - 1][j]);
	}
	//最右面一排
	for (int i = row + rowlen - 1; i > row; i--) {
		res.push_back(matrix[i][col]);
	}
	dfs(matrix, row + 1, rowlen - 2, col + 1, collen - 2, res);
}

//螺旋形状访问矩阵
vector<int> spiralOrder(vector<vector<int>>& matrix) {
	vector<int> res;
	//空
	if (matrix.empty() || matrix.size() == 0)
		return res;
	dfs(matrix, 0, matrix.size(), 0, matrix[0].size(), res);
	return res;
}

void dfsII(vector<vector<int>>& matrix, int row, int rowlen, int col, int collen, vector<int> &res,int index) {
	if (rowlen <= 0 || collen <= 0)
		return;

	//只有一行
	if (rowlen == 1) {
		for (int j = col; j < col + collen; j++) {
			matrix[row][j] = res[index];
			index++;
		}
		return;
	}
	//只有一列
	if (collen == 1) {
		for (int i = row; i < row + rowlen; i++) {
			matrix[i][col] = res[index];
			index++;
		}
		return;
	}

	//最上面一排
	for (int j = col; j < col + collen - 1; j++) {
		matrix[row][j] = res[index];
		index++;
	}
	//最右边一排
	for (int i = row; i < row + rowlen - 1; i++) {
		matrix[i][col + collen - 1] = res[index];
		index++;
	}
	//最下面一排
	for (int j = col + collen - 1; j > col; j--) {
		matrix[row + rowlen - 1][j] = res[index];
		index++;
	}
	//最左面一排
	for (int i = row + rowlen - 1; i > row; i--) {
		matrix[i][col] = res[index];
		index++;
	}
	dfsII(matrix, row + 1, rowlen - 2, col + 1, collen - 2, res,index);
}

//获得螺旋矩阵
vector<vector<int>> generateMatrix(int n) {
	if (n == 0)
		return{ {} };
	if (n == 1)
		return{ { 1 } };

	vector<int> res;
	for (int i = 1; i <= n * n; i++) 
		res.push_back(i);

	vector<vector<int>> matrix(n, vector<int>(n, -1));
	dfsII(matrix, 0, n, 0, n, res,0);
	return matrix;
}

/**
* Definition for singly-linked list.*/
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
 };

//统计1的个数
int numberOfOne(int n) {
	int count = 0;
	if (n == 0)
		return count;
	while (n > 0) {
		count += n & 1;
		n >>= 1;
	}
	return count;
}

//翻转链表，把后几位翻到前面来
ListNode* rotateRight(ListNode* head, int k) {
	if (head == NULL)
		return head;

	int size = 0;
	for (ListNode* node = head; node != NULL;node = node->next){
		size++;
	}
	k = k%size;
	if (k == 0)
		return head;

	ListNode* fast = head;
	ListNode* newHead = head;
	ListNode* newHeadbefore = head;
	for (int i = 0; i < size; i++) {
		if (i == size - k - 1) {
			newHead = fast->next; //记录新的头节点
			newHeadbefore = fast; //记录新的头节点之前的节点，为了在下面将他的next设置成null
		}
		fast = fast->next;
	}
	fast->next = head;
	newHeadbefore->next = NULL;
	return newHead;
}

//翻转数组，把右边k位翻到前面来
void rotateArray(vector<int>& nums, int k) {
	int size = nums.size();
	k = k % size;
	if (k == 0)
		return;
	while(k > 0) {
		nums.insert(nums.begin(),nums[size - 1]);
		nums.pop_back();
		k--;
	}
	return;
}

//实现x的n次方
//直接方法，超时
double myPow(double x, int n) {
	double result = 1;
	int n_abs = abs(n);
	int i = n_abs;
	while (i > 0) {
		result *= x;
		i--;
	}
	return n_abs == n ? result:1 / result;
}

//二分法优化
//递归公式为：x^n = x^(n/2) * x^(n/2) * x^(n%2)，我们就不用将x相乘n次，而只要logN次就行了
double powRecursion(double x, int n) {
	if (n == 0)
		return 1;
	double result = powRecursion(x, n / 2);
	result *= result;
	//奇数
	if (n % 2)
		result *= x;
	return result;
}

double myPowII(double x, int n) {
	return n >= 0 ? powRecursion(x,n) : powRecursion(x, -n);
}

//买股票和抛股票的最佳时机,只进行一次交易，即买一次抛一次
//O(n),在一遍循环里，一边记录当前的最小价格，一边记录当前的最大利润
int maxProfit(vector<int>& prices) {
	if (prices.size() <= 1)
		return 0;

	int maxProfit = prices[1] - prices[0];
	int minPrice = prices[0];

	for (int i = 1; i < prices.size() - 1; i++) {
		minPrice = min(minPrice, prices[i]);
		maxProfit = max(maxProfit, prices[i+1] - minPrice);
	}
	return (maxProfit>0)? maxProfit:0;
}

//买股票和抛股票的最佳时机,只进行一次交易，即买一次抛一次
//O(n),local[i]记录在第i天卖出股票的最大收益，global[i]记录第i天的最大收益，包括在第i天卖出股票和不卖出股票两种情况
int maxProfitDP(vector<int>& prices) {
	if (prices.size() <= 1)
		return 0;

	int local = 0;
	int global = 0;

	for (int i = 1; i < prices.size() - 1; i++) {
		local = max(local+prices[i] - prices[i - 1], 0);
		global = max(local, global);
	}
	return global;
}

//买股票和抛股票的最佳时机,可进行多次交易，但下次买之前必须先抛出去
//只要发现第i天比第i-1天的价钱高，就直接抛出去，把利润加上来
int maxProfitII(vector<int>& prices) {
	int profit = 0;
	for (int i = 1; i < prices.size(); i++) {
		if (prices[i] > prices[i - 1]) {
			profit += prices[i] - prices[i - 1];
		}
	}
	return profit;
}

//买股票和抛股票的最佳时机,可进行最多k次交易，但下次买之前必须先抛出去
int maxProfitIII(vector<int>& prices,int k) {
	if (prices.size() <= 1)
		return 0;
	if (k >= prices.size())
		return maxProfitII(prices);

	vector<int> local(k + 1,0);
	vector<int> global(k + 1,0);

	for (int i = 0; i < prices.size() - 1; i++) {
		int diff = prices[i + 1] - prices[i];
		for (int j = k; j >= 1; j--) {
			local[j] = max(global[j - 1] + max(diff, 0), local[j] + diff);
			global[j] = max(local[j], global[j]);
		}
	}
	return global[k];
}


//买股票和抛股票的最佳时机,可进行多次交易，但下次买之前必须先抛出去,而且抛出去以后必须隔一天再买。
int maxProfitWithColdown(vector<int>& prices) {
	int buy = INT_MIN, pre_buy = 0, sell = 0, pre_sell = 0;
	for (auto price : prices) {
		pre_buy = buy;
		buy = max(pre_sell - price, pre_buy);
		pre_sell = sell;
		sell = max(pre_buy + price, pre_sell);
	}
	return sell;
}


//定义两个string的商，然后发起一系列查询，需要输出可以推出的商，不能得出的商为-1.0。
//- 建图：根据每个输入得到a/b=k和b/a=1/k两条有向边，时间复杂度O(n) 
//-遍历：遍历搜索是否有解，时间复杂度O(n)（最坏情况历遍所有的点才能得到解）
double thisOne;
void dfsForDivision(unordered_map<string, vector<pair<string, double>>> graphs, unordered_set<string> visited, string pstart, string pend, double val) {
	if (pstart == pend) {
		thisOne = val;
		return;
	}
	vector<pair<string, double>> temps = graphs[pstart];
	for (auto tmp : temps) {
		if (visited.find(tmp.first) == visited.end()) {
			visited.insert(tmp.first);
			dfsForDivision(graphs, visited, tmp.first,pend, (val * tmp.second));
		}
		//一旦发现thisOne不为0，说明找到了一条路径，直接返回，注意这里！
		if (thisOne)
			break;
	}
}
vector<double> calcEquation(vector<pair<string, string>> equations, vector<double>& values, vector<pair<string, string>> queries) {
	
	//存储整个图
	unordered_map<string, vector<pair<string, double>>> graphs;
	unordered_set<string> visited;
	vector<double> ans(queries.size());
	for (int i = 0; i < equations.size(); i++) {
		graphs[equations[i].first].push_back(make_pair(equations[i].second, values[i]));
		graphs[equations[i].second].push_back(make_pair(equations[i].first, 1.0 / values[i]));
	}

	//查询
	for (int i = 0; i < queries.size(); i++) {
		//每个查询开始之前清空visited和thisOne
		visited.clear();
		thisOne = 0;
		string pstart = queries[i].first;
		string pend = queries[i].second;

		//如果出现不存在的字符
		if (graphs.find(pstart) == graphs.end() || graphs.find(pend) == graphs.end()) {
			ans[i] = -1.0;
		}
		else {
			//从pstart开始找了
			visited.insert(pstart);
			dfsForDivision(graphs,visited,pstart, pend, 1.0);
			//thisOne不为0，找到路径了
			if (thisOne)
				ans[i] = thisOne;
			else
				ans[i] = -1.0;
		}
	}
	return ans;
}

class Iterator {
	struct Data;
	Data* data;
public:
	Iterator(const vector<int>& nums);
	Iterator(const Iterator& iter);
	virtual ~Iterator();
	// Returns the next element in the iteration.
	int next();
	// Returns true if the iteration has more elements.
	bool hasNext() const;
};

//实现PeekingIterator
class PeekingIterator : public Iterator {
public:
	PeekingIterator(const vector<int>& nums) : Iterator(nums) {
		// Initialize any member here.
		// **DO NOT** save a copy of nums and manipulate it directly.
		// You should only use the Iterator interface methods.

	}

	// Returns the next element in the iteration without advancing the iterator.
	int peek() {
		return Iterator(*this).next();
	}

	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() {
		return Iterator::next();
	}

	bool hasNext() const {
		return Iterator::hasNext();
	}
};


//实现一个数据结构，确保常数时间的插入删除获取随机数操作
class RandomizedSet {
public:
	/** Initialize your data structure here. */
	RandomizedSet() {}

	/** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
	bool insert(int val) {
		if (m.count(val)) return false;
		nums.push_back(val);
		m[val] = nums.size() - 1;
		return true;
	}

	/** Removes a value from the set. Returns true if the set contained the specified element. */
	bool remove(int val) {
		if (!m.count(val)) return false;
		int last = nums.back();
		m[last] = m[val];
		//注意，把删除的元素所对应的hash值赋值给最后一个元素所对应的hash值。
		nums[m[val]] = last;
		nums.pop_back();
		m.erase(val);
		return true;
	}

	/** Get a random element from the set. */
	int getRandom() {
		return nums[rand() % nums.size()];
	}
private:
	vector<int> nums;
	unordered_map<int, int> m;
};

/**
* Your RandomizedSet object will be instantiated and called as such:
* RandomizedSet obj = new RandomizedSet();
* bool param_1 = obj.insert(val);
* bool param_2 = obj.remove(val);
* int param_3 = obj.getRandom();
*/

string intToString(long long int n) {
	stringstream ss;
	ss << n;
	return ss.str();
}

//统计连续区间
vector<string> summaryRanges(vector<int>& nums) {
	int size = nums.size();
	vector<string> res;
	string str = "";
	if (size == 0)
		return res;
	if (size == 1) {
		str = intToString(nums[0]);
		res.push_back(str);
		return res;
	}

	int i = 1, j = 1;
	while (i < size) {
		j = i;
		while(j < size && nums[j] == nums[j - 1] + 1) {
			j++;
		}
		if (j > i) {
			str = intToString(nums[i - 1]) + "->" + intToString(nums[j - 1]);
		}
		else {
			str = intToString(nums[j - 1]);
		}
		//最后一个元素在最后一个range里
		//if (j == size) {
			//str.resize(str.size() - 1);
		//}
		res.push_back(str);
		i = j + 1;
		str.clear();
	}
	//最后一个元素不在上一个range里
	if (nums[size - 1] != nums[size - 2] + 1) {
		str = intToString(nums[size - 1]);
		res.push_back(str);
	}
	return res;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//中序遍历
void inOrder(TreeNode* root, int k,int& flag, int& result) {
	if (root == NULL)
		return;
	if (result != -1)
		return;
	inOrder(root->left, k, flag, result);
	flag++;
	if (flag == k) {
		result = root->val;
		return;
	}
	inOrder(root->right, k, flag, result);
	return;
}

//寻找第k个最小的元素
//想法：中序遍历整棵树，结果存储在vector，每到一个节点count++，直到加到k的时候，返回结果
int kthSmallest(TreeNode* root, int k) {
	int flag = 0;
	int result = -1;
	inOrder(root, k,flag,result);
	return result;
}

//
void inOrderForMinDiff(TreeNode* root, vector<int>& res, int& minDiff) {
	if (root == NULL)
		return;

	inOrderForMinDiff(root->left, res, minDiff);
	
	if (!res.empty() && (abs(root->val - res.back()) < minDiff))
			minDiff = root->val - res.back();
	res.push_back(root->val);

	inOrderForMinDiff(root->right, res, minDiff);
}

int getMinimumDifference(TreeNode* root) {
	int minDiff = INT_MAX;
	vector<int> res;
	inOrderForMinDiff(root, res, minDiff);
	return minDiff;
}

//判断s是否是合法的括号串,不可交叉出现
bool isValidII(string s) {
	//s长度为0
	if (s.size() == 0)
		return true;
	//奇数个
	if (s.size() % 2 == 1)
		return false;
	vector<char> leftPart = {'{','[','('};
	vector<char> rightPart = { '}',']',')' };

	if (find(leftPart.begin(), leftPart.end(), s[s.size() - 1]) != leftPart.end() ||
		find(rightPart.begin(), rightPart.end(), s[0]) != rightPart.end()) {
		return false;
	}
	stack<char> stack;
	stack.push(s[0]);
	int i = 1;
	while (i < s.size()) {
		if (!stack.empty()) {
			char c = stack.top();
			if (abs(s[i] - c) == 1 || abs(s[i] - c) == 2)
				stack.pop();
			else
				stack.push(s[i]);
		}
		else
			stack.push(s[i]);
		i++;
	}
	if (!stack.empty())
		return false;
	return true;
}

//判断s是否是合法的括号串,可交叉出现
bool isValid(string s) {
	//s长度为0
	if (s.size() == 0)
		return true;
	//奇数个
	if (s.size() % 2 == 1)
		return false;
	vector<char> leftPart = { '{','[','(' };
	vector<char> rightPart = { '}',']',')' };

	if (find(leftPart.begin(), leftPart.end(), s[s.size() - 1]) != leftPart.end() ||
		find(rightPart.begin(), rightPart.end(), s[0]) != rightPart.end()) {
		return false;
	}
	queue<char> queue;
	queue.push(s[0]);
	int i = 1;
	while (i < s.size()) {
		if (!queue.empty()) {
			char c = queue.front();
			if (abs(s[i] - c) == 1 || abs(s[i] - c) == 2)
				queue.pop();
			else
				queue.push(s[i]);
		}
		else
			queue.push(s[i]);
		i++;
	}
	if (!queue.empty())
		return false;
	return true;
}

//123变成231，-123变成-231，注意整数的overflow
int reverse(int x) {
	int res = 0;
	int m = 0;
	int y = abs(x);
	while (y != 0) {
		m = y % 10;
		res = res * 10 + m;
		if (res > INT_MAX / 10 || res < INT_MIN / 10) {
			return 0;
		}
		y /= 10;
	}
	return (x > 0) ? res : -res;
}

//求岛的周长
int islandPerimeter(vector<vector<int>>& grid) {
	if (grid.empty() || grid[0].empty())
		return 0;
	int m = grid.size();
	int n = grid[0].size();
	int res;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			if (grid[i][j] == 0)
				continue;
			if (j == 0 || grid[i][j - 1] == 0)
				res++;
			if (i == 0 || grid[i - 1][j] == 0)
				res++;
			if (j == n - 1 || grid[i][j + 1] == 0)
				res++;
			if (i == m - 1 || grid[i + 1][j] == 0)
				res++;
		}
	}
}

//解法二
int islandPerimeterII(vector<vector<int>>& grid) {
	if (grid.empty() || grid[0].empty()) return 0;
	int res = 0, m = grid.size(), n = grid[0].size();
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			if (grid[i][j] == 0) continue;
			res += 4;
			if (i < m - 1 && grid[i + 1][j] == 1) res -= 2;
			if (j < n - 1 && grid[i][j + 1] == 1) res -= 2;
		}
	}
	return res;
}

//找到peak元素，比两边的元素都大，用二分法提高效率
int findPeakElement(vector<int>& nums) {
	if (nums.empty())
		return 0;
	if (nums.size() == 1)
		return nums[0];
	int start = 0;
	int end = nums.size() - 1;
	int middle = 0;
	while (start <= end) {
		middle = start + (end - start) / 2;
		//注意下面的条件，需要理解，这是于或运算的分配律
		if ((middle == 0 || nums[middle] >= nums[middle - 1]) &&
			(middle == nums.size() - 1 || nums[middle] >= nums[middle + 1]))
			return middle;
		else if (middle > 0 && nums[middle] < nums[middle - 1]) {
			end = middle - 1;
		}
		else if (middle < nums.size() && nums[middle] < nums[middle + 1]) {
			start = middle + 1;
		}
	}
	return middle;
}

//看一个字符串能否被分为字典
bool wordBreak(string s, vector<string>& wordDict) {
	//定义possible[i] 为S字符串上[0,i - 1]的子串是否可以被segmented by dictionary.
	int len = s.size();
	vector<bool> possible(len + 1,false);
	possible[0] = true;
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= i; j++) {
			if (possible[j] && (find(wordDict.begin(), wordDict.end(), s.substr(j, i - j + 1)) != wordDict.end())) {
				possible[i + 1] = true;
				break;
			}
		}
	}
	return possible[len];
}

void findWordBreak(string s, vector<string>& wordDict, int start, vector<string>& result, vector<string>& str) {
	//递归的终止条件，当s走到底了并且目前保存起来的
	if (start == s.size() && !str.empty()) {
		string temp = str[0];
		for (int i = 1; i < str.size(); i++) {
			temp.append(" " + str[i]);
		}
		result.push_back(temp);
	}
	
	string word;
	//依次从s的首字母开始，一个一个加到word里
	for (int i = start; i < s.size(); i++) {
		word.push_back(s[i]);
		//如果dict里存在word，那么接着往下找i+1以后的在不在
		if (find(wordDict.begin(), wordDict.end(), word) != wordDict.end()) {
			str.push_back(word);
			findWordBreak(s, wordDict, i + 1, result, str);
			str.pop_back();
		}
	}
}

//记录所有路径的wordbreak
vector<string> wordBreakII(string s, vector<string>& wordDict) {
	vector<string> result;
	vector<string> str;
	findWordBreak(s,wordDict,0,result,str);
	return result;
}

class MinStack {
public:
	/** initialize your data structure here. */
	MinStack() {

	}

	void push(int x) {
		element.push(x);
		if (mins.empty() || x <= mins.top()) {
			mins.push(x);
		}
	}

	void pop() {
		if (element.empty())
			return;
		if (element.top() == mins.top())
			mins.pop();
		element.pop();
	}

	int top() {
		return element.top();
	}

	int getMin() {
		return mins.top();
	}
private:
	stack<int> element;
	//依次存储最小元素，从栈顶到栈底依次递减。
	stack<int> mins;
};

//最长回文子序列
int longestPalindromeSubseq(string s) {
	if (s.empty())
		return 0;
	//代表从0-i区间里的最长回文子序列
	int size = s.size();
	vector<vector<int>> dp(size,vector<int>(size));
	for (int i = size - 1; i >= 0; i--) {
		dp[i][i] = 1;
		for (int j = i + 1; j < size; j++) {
			if (s[i] == s[j])
				dp[i][j] = dp[i + 1][j - 1] + 2;
			else
				dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
		}
	}
	return dp[0][size - 1];
}

//DP解法，P[i,j]表示i，j区间的最长回文串长度
//string longestPalindromeWithDP(string s) {
//	int size = s.size();
//	int maxLength = 0, start = 0, end = 0;
//	if (size == 0)
//		return"";
//	vector<vector<int>> dp(size, vector<int>(size, 0));
//	for (int i = 0; i < size; i++) {
//		for (int j = 0; j < i; j++) {
//			dp[j][i] = ((s[j] == s[i]) && (i - j < 2 || dp[j + 1][i - 1]));
//			if (dp[j][i] && (i - j + 1) > maxLength) {
//				maxLength = i - j + 1;
//				start = j;
//				end = i;
//			}
//		}
//		dp[i][i] = 1;
//	}
//	return s.substr(start, end - start + 1);
//}

//升序序比较器
bool compareForPair(pair<int, int>& a, pair<int, int> &b) {
	return (a.first + a.second < b.first + b.second);
}

//求和最小的k个pair
vector<pair<int, int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
	vector<pair<int, int>> res;
	if (nums1.empty() && nums2.empty())
		return res;

	for (int i = 0; i < nums1.size(); i++) {
		for (int j = 0; j < nums2.size(); j++) {
			res.push_back(make_pair(nums1[i], nums2[j]));
		}
	}
	sort(res.begin(), res.end(), compareForPair);
	if (res.size() > k)
		res.resize(k);
	return res;
}

//升序比较器
struct cmp {
	bool operator() (pair<int, int>& a, pair<int, int> &b) {
		return (a.first + a.second < b.first + b.second);
	}
};

//求和最小的k个pair,用堆（优先队列来做）
//维护大顶堆，存储各个pair，当大顶堆的数量大于k的时候
vector<pair<int, int>> kSmallestPairsII(vector<int>& nums1, vector<int>& nums2, int k) {
	vector<pair<int, int>> res;
	//注意优先队列的用法，自己定义比较器,这里是大顶堆，用的比较器是<
	priority_queue <pair<int, int>, vector<pair<int, int>>, cmp> q;
	if (nums1.empty() && nums2.empty())
		return res;

	for (int i = 0; i < nums1.size(); i++) {
		for (int j = 0; j < nums2.size(); j++) {
			if (q.size() < k) {
				q.push({ nums1[i], nums2[j] });
			}
			//因为这是大顶堆，堆顶就是最大值，所以一旦发现堆的大小超过了k，就要开始更新堆。
			//新来的值和堆顶做比较，发现堆顶大了的话就吧堆顶更新
			else if (nums1[i] + nums2[j] < q.top().first + q.top().second) {
				//当前的pair值更小，push进去
				q.push({ nums1[i], nums2[j] });
				//把堆顶删除，因为他已经不是最小的k个pair里的一个了
				q.pop();
			}
		}
	}
	while (!q.empty()) {
		res.push_back(q.top());
		q.pop();
	}
	return res;
}

int maxDepth(TreeNode* root) {
	int maxLength1 = 0;
	int maxLength2 = 0;
	if (root == NULL)
		return 0;

	if (root->left != NULL)
		maxLength1 = maxDepth(root->left) + 1;

	if(root->right != NULL)
		maxLength2 = maxDepth(root->right) + 1;

	return max(maxLength1, maxLength2);
}

//找两个数组合并后的第k小的数字
double finKth(vector<int>& A,vector<int>& B,int A_st,int B_st,int k) {

	if (A_st >= A.size()) {
		return B[B_st + k - 1];
	}
	if (B_st >= B.size()) {
		return A[A_st + k - 1];
	}

	//k=1表示取第一小的数
	if (k == 1)
		return min(A[A_st], B[B_st]);

	int A_cur = A_st + k / 2 - 1 >= A.size() ? INT_MAX : A[A_st + k / 2 - 1];
	int B_cur = B_st + k / 2 - 1 >= B.size() ? INT_MAX : B[B_st + k / 2 - 1];

	//所求的数肯定不在A_st + k / 2之前的元素里，反证法证明
	if (A_cur < B_cur) {
		//规模缩小后，求剩下的A.size() + B.size() - k/2个元素里的第k - k/2小的元素
		return finKth(A, B, A_st + k / 2, B_st, k - k / 2);
	}
	//同理，所求的数肯定不在B_st + k / 2之前的元素里
	else{
		return finKth(A, B, A_st, B_st + k / 2, k - k / 2);
	}
}

//两个数组的中位数，用O(logmn)的复杂度
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
	int sum = nums1.size() + nums2.size();
	double res;
	if (sum % 2 == 1) {
		//合并后的元素个数是奇数，求第sum / 2 + 1小的元素
		res = finKth(nums1, nums2, 0, 0, sum / 2 + 1);
	}
	else {
		//合并后元素个数是偶数
		res = ((finKth(nums1, nums2, 0, 0, sum / 2)) + (finKth(nums1, nums2, 0, 0, sum / 2 + 1))) / 2.0;
	}
	return res;
}

//实现中位数的数据结构
class MedianFinder {
public:
	/** initialize your data structure here. */
	MedianFinder() {

	}

	void addNum(int num) {
		myVector.push_back(num);
	}

	double findMedian() {

	}
private:
	vector<int> myVector;
};

void dfsForItinerary(unordered_map<string, vector<string>>& graph, string& begin,vector<string>& res) {
	while(graph[begin].size()) {
		string t = *graph[begin].begin();
		graph[begin].erase(graph[begin].begin());
		dfsForItinerary(graph, t, res);
	}
	//while循环最后跳出的时候说明整条路径都走完了，这是我们要回溯回去，所以这里的结点是insert而不是push_back
	res.insert(graph[begin].begin(),begin);
}

static bool cmpForString(string& a, string& b) {
	return a < b;
}
//构建有效路线
vector<string> findItinerary(vector<pair<string, string>> tickets) {
	unordered_map<string, vector<string>> graph;
	vector<string> res;
	//ticket的键值是在字典序上有序的
	for (auto pair : tickets) {
		graph[pair.first].push_back(pair.second);
	}

	for (auto pair : tickets) {
		sort(graph[pair.first].begin(), graph[pair.first].end(), cmpForString);
	}

	string begin = "JFK";
	int i = 0;
	dfsForItinerary(graph, begin, res);

	return res;
}

int binarySearch(vector<int> m, int low, int high, int target) {
	int mid;
	while (low <= high) {
		mid =  low + (high - low)/ 2;
		if (target < m[mid]) {
			high = mid - 1;
		}
		else if (m[mid] < target) {
			low = mid + 1;
		}
		else
			return mid;
	}
	return -1;
}

//在一个矩阵里搜索某一个数
bool searchMatrix(vector<vector<int>>& matrix, int target) {
	vector<int> res;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			res.push_back(matrix[i][j]);
		}
	}
	if (res.empty())
		return false;
	int s = binarySearch(res, 0, res.size() - 1, target);
	if (s == -1)
		return false;
	else
		return true;
}

//在一个矩阵里搜索一个数
bool searchMatrixII(vector<vector<int>>& matrix, int target) {
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return false;

	int i = 0;
	int j = matrix[0].size() - 1;

	while (i < matrix.size() && j >= 0) {
		int t = matrix[i][j];
		if (t > target)
			j--;
		else if (t < target)
			i++;
		else
			return true;
	}
	return false;
}

struct cmpDesc {
	bool operator() (int& a, int& b) {
		return a > b;
	}
};

//寻找数组中第k个大的数，注意最大的数是第一大
//维护一个小顶堆，然后把数组里的元素一个一个push到堆里，
//发现堆的大小比k大的时候，把对顶元素弹出，确保小顶堆的元素个数是k，所有元素遍历完成后把堆顶弹出即可
//注意小顶堆的比较函数是a>b,C++里默认是大顶堆，比较函数是a<b
int findKthLargest(vector<int>& nums, int k) {
	priority_queue<int, vector<int>, cmpDesc> p;
	for (int i = 0; i < nums.size(); i++) {
		p.push(nums[i]);
		if (p.size() > k)
			p.pop();
	}
	return p.top();
}

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
	return;
}

static bool cmpForArray(int& a, int &b) {
	return a > b;
}

//重新排序数组，变成nums[0] < nums[1] > nums[2] < nums[3]....
//i++返回原来的值，++i返回加一后的值
void wiggleSort(vector<int>& nums) {
	vector<int> temp = nums;
	int n = nums.size();
	int k = (n + 1) / 2;
	int j = n;
	sort(temp.begin(), temp.end());
	for (int i = 0; i < n; i++) {
		nums[i] = i & 1 ? temp[--j] : temp[--k];
	}
}

//这种方法交换相邻的两个元素，只适合没有重复元素的数组
void wiggleSortII(vector<int>& nums) {
	int n = nums.size();
	sort(nums.begin(), nums.end(), cmpForArray);
	for (int i = 0; i < n - 1;) {
		swap(nums[i], nums[i + 1]);
		i += 2;
	}
}

//按规格输出，三的倍数输出Fizz，五的倍数输出Buzz，既是三又是五的倍数输出FizzBuzz
vector<string> fizzBuzz(int n) {
	vector<string> res;
	for (int i = 1; i <= n; i++) {
		if (i % 3 == 0 && i % 5 != 0)
			res.push_back("Fizz");
		else if (i % 3 != 0 && i % 5 == 0)
			res.push_back("Buzz");
		else if (i % 3 == 0 && i % 5 == 0)
			res.push_back("FizzBuzz");
		else
			res.push_back(intToString(n));
	}
	return res;
}

//存储每个站点和其所在线路的unordered_map
//在从这个map里再初始化出每条线路与和他相邻线路的map
//把start和end所在的线路找出来，然后用上面准备好的map，从start线路一直找到end线路

void minTransfer() {

}

//设置一个哈希表，存储每一次的余数，以及该余数在返回结果result中的下标。
//每一次得到新的余数，就查询该余数是否已经在哈希表中，是的话说明开始循环了，
//那么直接在result中该余数对应的位置后面插入‘（’，result末尾加上‘）’，
//结束运算。如果在哈希表中没找到，则继续正常运运算
string fractionToDecimal(int numerator, int denominator) {
	if (numerator == 0)
		return "0";
	string str = "";
	if (numerator<0 ^ denominator<0)
		str += "-";
	//开始计算，转换成long long int
	long long int numeratorNew = numerator;
	numeratorNew = abs(numeratorNew);
	long long int  denominatorNew = denominator;
	denominatorNew = abs(denominatorNew);
	str += intToString(numeratorNew / denominatorNew);
	long long int r = (numeratorNew % denominatorNew);
	if (r == 0)
		return str;
	else
		str += ".";
	unordered_map<int, int> myMap;
	while (r) {
		//已经开始循环了
		if (myMap.find(r) != myMap.end()) {
			str.insert(myMap[r], 1, '(');
			str += ")";
			break;
		}

		myMap[r] = str.size();
		//继续计算
		r *= 10;
		str += intToString(r / denominatorNew);
		r = r % denominatorNew;
	}
	return str;
}

//维护一个栈，从根节点开始，每次迭代地将根节点的左孩子压入栈，直到左孩子为空为止。
//调用next()方法时，弹出栈顶，如果被弹出的元素拥有右孩子，则以右孩子为根，将其左孩子迭代压栈。
class BSTIterator {
public:
	BSTIterator(TreeNode *root) {
		TreeNode* node = root;
		while (node) {
			s.push(node);
			node = node->left;
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode * node = s.top();
		int res = node->val;
		s.pop();
		node = node->right;
		while (node) {
			s.push(node);
			node = node->left;
		}
		return res;
	}
private:
	stack<TreeNode *> s;
};


void combineParenthesis(vector<string>& res, string& str, int depth, int n, int left, int right) {
	if (depth == n * 2) {
		res.push_back(str);
		return;
	}

	if (left < n) {
		str.push_back('(');
		combineParenthesis(res, str, depth + 1, n,left + 1, right);
		str.resize(str.size() - 1);
	}

	if (right < left) {
		str.push_back(')');
		combineParenthesis(res, str, depth + 1, n, left, right + 1);
		str.resize(str.size() - 1);
	}

}

//求n对括号的所有有效组合，类似于全排列，但是要加入有效括号的限制
//一步步构造字符串。当左括号出现次数<n时，就可以放置新的左括号。当右括号出现次数小于左括号出现次数时，就可以放置新的右括号
vector<string> generateParenthesis(int n) {
	vector<string> res;
	string str;
	if (n != 0)
		combineParenthesis(res, str, 0, n, 0, 0);
	return res;
}


int main() {
	//int T;
	//string empty, line;
	//int ROW, COL;

	////测试用
	////freopen("C:/Users/Miwa/Downloads/codejam/test.in", "r", stdin);
	//freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice.in", "r", stdin);
	//freopen("C:/Users/Miwa/Downloads/codejam/A-large-practice-out.out", "w", stdout);
	//cin >> T;
	////getline(cin, empty);
	//for (int caseID = 1; caseID <= T; caseID++) {
	//	cin >> line;
	//	string res;
	//	res.append(1,line[0]);
	//	for (int i = 1; line[i] != '\0'; i++) {
	//		if (line[i] >= res[0])
	//			res.insert(res.begin(), line[i]);
	//		else
	//			res.append(1, line[i]);
	//	}
	//	cout << "Case #" << caseID << ": " << res << endl;
	//}
	//gettingDigits();
	//closeMatch();
	//vector<int> temp = { 1,1,2};
	//permute(temp);
	//reverseStr("awtsrm");
	//cout << removeKdigits("1231219", 3);
	//vector<int> temp1 = { };
	//vector<int> temp2 = { }; 
	//maxNumber(temp1,temp2, 0);
	//letterCombinations("23");
	//vector<vector<int>> matrix = { {2, 3, 4,14,15} };
	//spiralOrder(matrix);
	//generateMatrix(1);
	//numberOfOne(27);
	//letterCombinations("123");
	//vector<int> matrix = { 1,2};
	//rotateArray(matrix, 1);
	//myPowII(3,5);
	//vector<int> vec = { 0,1,2,4,6,7 };
	//maxProfitII(vec);
	//summaryRanges(vec);
	//isValid("{[}(((]){}");
	//reverse(1534236469);
	//vector<string> vec = { "leet","code" };
	//wordBreak("leetcode", vec);
	/*vector<pair<string, string>> tickets;
	tickets.push_back(make_pair("JFK", "SFO"));
	tickets.push_back(make_pair("JFK", "ATL"));
	tickets.push_back(make_pair("SFO", "ATL"));
	tickets.push_back(make_pair("ATL", "JFK"));*/
	//tickets.push_back(make_pair("ATL", "SFO"));
	//findItinerary(tickets);
	//vector<vector<int>> matrix;
	//matrix.push_back({1,3,5,7});
	//matrix.push_back({10,11,16,20});
	//matrix.push_back({23,30,34,50});
	//searchMatrix(matrix, 3);
	//vector<int> nums = { 3,2,1,5,6,4 };
	//int a = findKthLargest(nums, 2);
	/*int a = 1;
	int i = 0;
	i = a++;
	cout << i << endl; 1
	i = ++a;
	cout << i << endl; 3*/
	/*vector<int> nums = { 3,2,1,5,6,4 };
	wiggleSortII(nums);*/
	cout << fractionToDecimal(2147483648, 1) << endl;
	return 0;
}