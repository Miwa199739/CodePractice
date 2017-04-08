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

void SplitStringToIntII(const string& s, vector<string>& v, const string& c)
{
	std::string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1).c_str());

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1).c_str());
}

int getNumOfRes(int k) {
	int temp = 1;
	int n = k * 2;
	if (k > n - k) {
		k = n - k;
	}
	for (int i = 0; i < k; i++) {
		temp *= (n - i);
		temp /= (i + 1);
	}
	return temp / (k+1);
}

int count(string line) {
	if (line == "")
		return 0;
	stack<char> stack;
	int i = 1;
	int size= line.size();
	stack.push(line[0]);
	while (!stack.empty() && i < line.size()) {
		char c = stack.top();
		if (line[i] == ')' && c == '(')
			stack.pop();
		else
			stack.push(line[i]);
		i++;
	}
	return stack.size();
}

//找两个数，加起来等于target
vector<int> twoSum(vector<int>& nums, int target) {
	vector<int> res;
	unordered_map<int,int> numsMap;
	for (int i = 0; i < nums.size();i++){
		numsMap[nums[i]] = i;
	}

	for (int i = 0; i < nums.size(); i++) {
		int remainder = target - nums[i];
		if (numsMap.find(remainder) != numsMap.end()) {
			if (numsMap[remainder] < i) {
				res.push_back(numsMap[remainder]);
				res.push_back(i);
				break;
			}
			else if (numsMap[remainder] > i) {
				res.push_back(i);
				res.push_back(numsMap[remainder]);
				break;
			}
		}
	}
	return res;
}

//找三个数，加起来等于0
vector<vector<int>> threeSum(vector<int>& nums) {
	vector<vector<int>> res;
	//加起来是零，我们先排序
	sort(nums.begin(), nums.end());

	int size = nums.size();
	for (int i = 0; i < nums.size(); i++) {
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		//twosum
		int start = i + 1;
		int end = size - 1;
		int remainder = nums[i] * -1;
		vector<int> temp;
		while (start < end) {
			if (start > i + 1 && nums[start] == nums[start - 1]) {
				start++;
				continue;
			}
			if (end < size - 1 && nums[end] == nums[end + 1]) {
				end--;
				continue;
			}
			if (nums[start] + nums[end] < remainder)
				start++;
			else if (nums[start] + nums[end] > remainder)
				end--;
			else {
				temp.push_back(nums[i]);
				temp.push_back(nums[start]);
				temp.push_back(nums[end]);
				res.push_back(temp);
				start++;
				end--;
			}
		}
	}
	return res;
}

//找三个数，加起来的和与target差值最小
int threeSumClosest(vector<int>& nums, int target) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	int size = nums.size();

	int closet = INT_MIN;
	int diff = INT_MAX;
	for (int i = 0; i < nums.size(); i++) {
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		//twosum
		int start = i + 1;
		int end = size - 1;
		int remainder = target - nums[i];
		vector<int> temp;
		while (start < end) {
			if (start > i + 1 && nums[start] == nums[start - 1]) {
				start++;
				continue;
			}
			if (end < size - 1 && nums[end] == nums[end + 1]) {
				end--;
				continue;
			}
			int temp = nums[i] + nums[start] + nums[end];
			if (nums[start] + nums[end] < remainder)
				start++;
			else if (nums[start] + nums[end] > remainder)
				end--;
			else {
				return target;
			}
			if (abs(target - temp) < diff) {
				diff = abs(target - temp);
				closet = temp;
			}
		}
	}
	return closet;
}


//找四个数，加起来等于target
vector<vector<int>> fourSum(vector<int>& nums, int target) {
	vector<vector<int>> res;
	sort(nums.begin(), nums.end());
	int size = nums.size();
	for (int i = 0; i < nums.size() - 3; i++) {
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		for (int j = i+1; j < nums.size() - 2; j++) {
			if (j > i+1 && nums[j] == nums[j - 1])
				continue;
			//twosum
			int start = j + 1;
			int end = size - 1;
			int remainder = target - nums[i] - nums[j];
			while (start < end) {
				if (start > j + 1 && nums[start] == nums[start - 1]) {
					start++;
					continue;
				}
				if (end < size - 1 && nums[end] == nums[end + 1]) {
					end--;
					continue;
				}
				if (nums[start] + nums[end] < remainder)
					start++;
				else if (nums[start] + nums[end] > remainder)
					end--;
				else {
					vector<int> temp;
					temp.push_back(nums[i]);
					temp.push_back(nums[j]);
					temp.push_back(nums[start]);
					temp.push_back(nums[end]);
					res.push_back(temp);
					start++;
					end--;
				}
			}
		}
	}
	return res;
}

//两个矩阵的交集
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
	sort(nums1.begin(), nums1.end());
	sort(nums2.begin(), nums2.end());

	int i = 0, j = 0;
	vector<int> res;
	while (i < nums1.size() && j < nums2.size()) {
		if (i > 0 && nums1[i] == nums1[i - 1]) {
			i++;
			continue;
		}
		if (j > 0 && nums1[j] == nums1[j - 1]) {
			j++;
			continue;
		}
		if (nums1[i] < nums2[j]) {
			i++;
		}
		else if (nums1[i] > nums2[j]) {
			j++;
		}
		else {
			res.push_back(nums1[i]);
			i++;
			j++;
		}
	}
	return res;
}

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

//链表加法，高精度加法
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int sum = 0,inc = 0,cur = 0;
	ListNode* head = new ListNode(0);
	ListNode* res = head;
	while (l1 && l2) {
		sum = l1->val + l2->val + inc;
		inc = sum / 10;
		cur = sum % 10;
		ListNode* temp = new ListNode(cur);
		res->next = temp;
		l1 = l1->next;
		l2 = l2->next;
		res = res->next;
	}
	while (l1) {
		sum = l1->val + inc;
		inc = sum / 10;
		cur = sum % 10;
		ListNode* temp = new ListNode(cur);
		res->next = temp;
		l1 = l1->next;
		res = res->next;
	}
	while (l2) {
		sum = l2->val + inc;
		inc = sum / 10;
		cur = sum % 10;
		ListNode* temp = new ListNode(cur);
		res->next = temp;
		l2 = l2->next;
		res = res->next;
	}

	if (inc != 0) {
		ListNode* temp = new ListNode(inc);
		res->next = temp;
	}
	return head->next;
}


//移除链表中倒数第n个，O(n)复杂度
ListNode* removeNthFromEnd(ListNode* head, int n) {
	//我们要自己设置一个指针来计算快指针，直接用head会出错，可以推一下
	ListNode* myHead = new ListNode(0);
	myHead->next = head;
	//我们要找的target要从head而不是myHead开始
	ListNode* pre = myHead, *target = head, *pivot = myHead;
	int temp = n;
	//设置快指针，与target差n-1个数
	while (n > 0) {
		pivot = pivot->next;
		n--;
	}
	while (pivot->next) {
		pre = target;//记录要移除的元素的前一个
		pivot = pivot->next;//记录走在最前面的元素，控制循环条件的，这个元素会一直走到链表结束
		target = target->next;//记录倒数第n个元素，当pivot走到倒数第一个时，target就是我们要找的倒数第n个
	}
	pre->next = target->next;
	head = myHead->next;
	delete myHead;
	return head;
}

ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
	ListNode* head = new ListNode(0);
	ListNode* res = head;
	while (l1 && l2) {
		if (l1->val < l2->val) {
			res->next = l1;
			l1 = l1->next;
		}
		else{
			res->next = l2;
			l2 = l2->next;
		}
		res = res->next;
	}
	if (l1) {
		res->next = l1;
	}
	if (l2) {
		res->next = l2;
	}
	res = head->next;
	delete head;
	return res;
}

ListNode* helper(vector<ListNode*>& lists, int l, int r) {
	if (l < r) {
		int m = (l + r) / 2;
		return mergeTwoLists(helper(lists,l,m), helper(lists, m+1, r));
	}
	return lists[l];
}

//合并k个链表，利用归并排序的思想
ListNode* mergeKLists(vector<ListNode*>& lists) {
	if (lists.size()==0)
		return NULL;
	return helper(lists, 0, lists.size()-1);
}

//升序比较器
struct cmp {
	bool operator() (ListNode* a, ListNode* b) {
		return a->val > b->val;
	}
};
//合并k个链表，利用堆，维护一个小顶堆，存储所有的元素，
//然后每次取堆顶元素加入结果集，再将堆顶删除，直到堆为空
ListNode* mergeKListsHeap(vector<ListNode*>& lists) {
	if (lists.size() == 0)
		return NULL;
	//小顶堆，用的比较器是>
	priority_queue <ListNode*, vector<ListNode*>, cmp> q;
	for (int i = 0; i < lists.size(); i++) {
		ListNode* temp = lists[i];
		if (temp)
			q.push(temp);
	}
	ListNode* head = new ListNode(-1);
	ListNode* act = head;
	while (!q.empty()) {
		ListNode* cur = q.top();
		q.pop();
		act->next = cur;
		act = act->next;
		if (cur->next)
			q.push(cur->next);
	}
	act = head->next;
	delete head;
	return act;
}


vector<int> prime(int n) {
	vector<int> res;
	res.push_back(1);
	res.push_back(2);
	for (int i = 3; i <= n; i += 2) { //偶数不是质数，步长可以加大  
		float temp = static_cast<float>(i);
		int mid = static_cast<int>(sqrt(temp));
		int j;
		for (j = 3; j <= mid; j += 2)//i是奇数，当然不能被偶数整除，步长也可以加大。  
			if (i % j == 0)
				break;

		if (j > mid)
			res.push_back(i);
	}
	return res;
}


int main() {
	//freopen("C:/Users/Miwa/Desktop/a.txt", "r", stdin);
	//freopen("C:/Users/Miwa/Desktop/a.out", "w", stdout);
	//int i = 0,countLeft = 0,countOfRes = 0;
	//vector<string> res;
	//string line = "";
	//cin >> line;
	//int len = line.length();
	////计算左括号的数量
	//for (i = 0; i < len; i++) {
	//	if (line[i] == '(')
	//		countLeft++;
	//}
	//int numOfPara = countLeft * 2 - len;
	//string flag = ")";
	////计算需要的括号数目
	//if (countLeft <= len - countLeft) {
	//	flag = "(";
	//	numOfPara = len - 2 * countLeft;
	//}

	//numOfPara = count(line);

	//SplitStringToIntII(line, res, flag);
	//int size = res.size();
	//i = 0;
	////计算所有情况数目
	//while (i < size) {
	//	if (res[i] != "")
	//		countOfRes += getNumOfRes(res[i].size());
	//	i++;
	//}
	//int sum = (countOfRes + 1000000007) % 1000000007;
	//cout << numOfPara << " " << sum << endl;
	//vector<int> para = { -1,0,1,2,-1,-4 };
	//threeSum(para);
	//ListNode * l11 = new ListNode(2);
	//ListNode * l12 = new ListNode(4);
	//ListNode * l13 = new ListNode(3);
	//l11->next = l12;
	//l12->next = l13;
	//l13->next = NULL;
	//ListNode * l21 = new ListNode(5);
	//ListNode * l22 = new ListNode(6);
	//ListNode * l23 = new ListNode(4);
	//l21->next = l22;
	//l22->next = l23;
	//l23->next = NULL;
	//addTwoNumbers(l11, l21);
	//ListNode * l1 = new ListNode(5);
	//ListNode * l2 = new ListNode(5);
	//mergeTwoLists(l1, l2);

	vector<int> vec = prime(20);
	for (auto a : vec)
		cout << a << endl;
}