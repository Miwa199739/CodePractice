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
#include "AlgorithmCollection.h"

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

//merge两个有序list
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

//判断两个链表的交点开始处
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (!headA)
		return NULL;
	if (!headB)
		return NULL;
	int sizeA = 0, sizeB = 0;
	ListNode * A = headA;
	ListNode * B = headB;
	while (A->next && B->next) {
		sizeA++;
		sizeB++;
		A = A->next;
		B = B->next;
	}
	while (A->next) {
		sizeA++;
		A = A->next;
	}
	while (B->next) {
		sizeB++;
		B = B->next;
	}
	A = headA;
	B = headB;
	int diff = 0;
	if (sizeB > sizeA) {
		diff = sizeB - sizeA;
		while (diff > 0) {
			diff--;
			B = B->next;
		}
		A = headA;
	}
	else {
		diff = sizeA - sizeB;
		while (diff > 0) {
			diff--;
			A = A->next;
		}
		B = headB;
	}
	while (A && B) {
		if (A == B)
			break;
		A = A->next;
		B = B->next;
	}
	return A;
}

//判断链表里是否有环
bool hasCycle(ListNode *head) {
	if (!head)
		return NULL;
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) 
			return true;
	}
	return NULL;
}

//返回环开始的位置
ListNode *detectCycle(ListNode *head) {
	if (!head)
		return NULL;
	ListNode* slow = head;
	ListNode* fast = head;
	while (fast->next && fast->next->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			slow = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}
	return NULL;
}

//奇数位在一起，偶数位在一起
ListNode* oddEvenList(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode* oddAC = head;
	ListNode* evenAC = head->next;
	ListNode* odd = head;
	ListNode* even = head->next;
	while (oddAC->next && oddAC->next->next) {
		oddAC->next = oddAC->next->next;
		oddAC = oddAC->next;
		if (evenAC->next && evenAC->next->next) {
			evenAC->next = evenAC->next->next;
			evenAC = evenAC->next;
		}
	}
	oddAC->next = even;
	evenAC->next = NULL;
	return head;
}

//删除重复元素
ListNode* deleteDuplicates(ListNode* head) {
	if (!head)
		return head;
	ListNode* active = head;
	while (active) {
		if (active->next){
			if (active->val == active->next->val) {
				active->next = active->next->next;
			}else
				active = active->next;
		}
		else
			break;
	}
	return head;
}

//删除所有重复元素
ListNode* deleteDuplicatesII(ListNode* head) {
	if (!head)
		return head;
	if (!head->next)
		return head;
	ListNode* dummy = new ListNode(-1);
	dummy->next = head;
	ListNode* fast = dummy;
	while (fast->next) {
		ListNode* cur = fast->next;
		while (cur && cur->next && cur->val == cur->next->val)
			cur = cur->next;
		if (cur != fast->next)
			fast->next = cur->next;
		else
			fast = fast->next;
	}
	return dummy->next;
}

//n个抽屉放n+1个数，找出那个重复的元素
int findDuplicate(vector<int>& nums) {
	int n = nums.size() - 1;
	if (n <= 0)
		return 0;
	int min = 0;
	int max = n;
	int mid = 0;
	while (min <= max) {
		mid = min + (max - min) / 2;
		int cnt = 0;
		for (int i = 0; i <= n; i++) {
			if (nums[i] <= mid)
				cnt++;
		}
		//小于等于mid的数的个数比mid大，说明重复的数肯定小于等于mid
		if (cnt > mid)
			max = mid - 1;
		else
			min = mid + 1;
	}
	return min;
}

//移除链表中等于val的元素
ListNode* removeElements(ListNode* head, int val) {
	ListNode* dummy = new ListNode(-1);
	dummy->next = head;
	ListNode* res = dummy;
	while (res) {
		if (res->next && res->next->val == val) {
			res->next = res->next->next;
		}
		else
			res = res->next;
	}
	return dummy->next;
}


//获得第k个排列
string getPermutation(int n, int k) {
	string res = "";
	vector<int> fac(n, 1);
	vector<char> num(n, 1);

	for (int i = 1; i < n; i++) {
		fac[i] = fac[i - 1] * i;
	}

	for (int i = 0; i < n; i++) {
		num[i] = (i + 1) + '0';
	}
	k--;
	for (int i = n; i >= 1; i--) {
		int j = k / fac[i - 1];
		k %= fac[i - 1];
		res.push_back(num[j]);
		num.erase(num.begin() + j);
	}
	return res;
}

int binSearchForPermu(vector<char> &m, int low, int high, int target) {
	int mid = 0;
	while (low <= high) {
		mid = low + (high - low)/ 2;
		if (target < m[mid]) {
			high = mid - 1;
		}
		else if (m[mid] < target) {
			low = mid + 1;
		}
		else
			return mid;
	}
	return mid;
}

//给定permutation，确定是第几个
int getPermutation(int n, string permuation) {
	int k = 1;
	vector<int> fac(n, 1);
	vector<char> num(n, 1);

	for (int i = 1; i < n; i++) {
		fac[i] = fac[i - 1] * i;
	}

	for (int i = 0; i < n; i++) {
		num[i] = (i + 1) + '0';
	}

	for (int i = 0; i < n; i++) {
		int cur = binSearchForPermu(num, 0, num.size()-1, permuation[i]);
		k += fac[n - i - 1] * cur;
		num.erase(num.begin() + cur);
	}
	return k;
}

//反转链表
ListNode* reverseListHelper(ListNode* before, ListNode* after) {
	if (!before)
		return before;
	if (after) {
		ListNode* afterNew = after->next;
		after->next = before;
		return reverseListHelper(after, afterNew);
	}
	else {
		return before;
	}
}

ListNode* reverseList(ListNode* head) {
	if (!head)
		return head;
	ListNode *newHead = reverseListHelper(head, head->next);
	//把头结点的next赋值成空
	head->next = NULL;
	return newHead;
}

//迭代做法
ListNode* reverseListIterative(ListNode* head) {
	if (!head)
		return head;
	ListNode *before = head;
	ListNode *after = head->next;
	while (before) {
		if (after) {
			ListNode *afterNew = after->next;
			after->next = before;
			before = after;
			after = afterNew;
		}
		else {
			break;
		}
	}
	head->next = NULL;
	return before;
}

//反转从m n之间的节点
ListNode* reverseBetween(ListNode* head, int m, int n) {
	if (!head)
		return head;
	if (m == n)
		return head;
	ListNode *res = head;
	ListNode *before = head;
	ListNode *beforeStart = head;
	ListNode *pre = new ListNode(-1);
	pre->next = head;
	int i = 1;
	while (i < m && before) {
		before = before->next;
		pre = pre->next;
		i++;
	}
	i = 1;
	beforeStart = before;
	ListNode *after = before->next;
	while (before && i < n - m + 1) {
		if (after) {
			ListNode *afterNew = after->next;
			after->next = before;
			before = after;
			after = afterNew;
		}
		else
			break;
		i++;
	}
	pre->next = before;
	beforeStart->next = after;
	if (m == 1)//如果从head开始反转，那么head指针最后会被移动，所以我们要返回pre->next，问不是head
		res = pre->next;
	else
		res = head;
	delete pre;
	return res;
}

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* sortedArrayToBST(vector<int>& nums, int begin, int end) {
	if (begin > end)
		return NULL;
	int mid = begin + (end - begin) / 2;
	TreeNode* root = new TreeNode(nums[mid]);
	root->left = sortedArrayToBST(nums, begin, mid - 1);
	root->right = sortedArrayToBST(nums, mid+1, end);
	return root;
}
//把排好序的数组转换成平衡二叉查找树
TreeNode* sortedArrayToBST(vector<int>& nums) {
	if (nums.size() == 0)
		return NULL;
	int size = nums.size();
	return sortedArrayToBST(nums, 0, size - 1);
}


TreeNode* sortedListToBSTHelper(ListNode* head, ListNode* tail) {
	if (head == tail)
		return NULL;
	if (head->next == tail) {
		TreeNode* root = new TreeNode(head->val);
		return root;
	}

	ListNode* mid = head, *temp = head;
	//找中间节点。用两个快慢指针，快指针每次走两步，慢指针每次走一步，当快指针走到最后一个时，慢指针走到中间
	while (temp != tail && temp->next != tail) {
		mid = mid->next;
		temp = temp->next;
	}
	TreeNode* root = new TreeNode(mid->val);
	root->left = sortedListToBSTHelper(head, mid);
	root->right = sortedListToBSTHelper(mid->next, tail);
	return root;
}

TreeNode* sortedListToBST(ListNode* head) {
	return sortedListToBSTHelper(head, NULL);
}

//1.对于节点x:
//定义PS1(x)为从x出发向leaf方向的第一类path中最大的path sum。
//定义PS2(x)为以x为LCA的第二类path中的最大path sum。
//显然如果我们求得所有节点x的PS1 & PS2，其中的最大值必然就是要求的max path sum。

//2. 如何求PS1(x)、PS2(x) ?
//(1) PS1(x) 、PS2(x)至少应该不小于x->val，因为x自己就可以作为一个单节点path。
//(2) PS1(x) 、 PS2(x)可以从PS1(x->left)和PS1(x->right)来求得：
//PS1(x) = max[max(PS1(x->left), 0), max(PS1(x->right), 0)] + x->val
//PS2(x) = max(PS1(x->left), 0) + max(PS1(x->right), 0) + x->val
//注意这里并不需要PS2(x->left) 以及 PS2(x->right) 因为子节点的2型path无法和父节点构成新的path。

//3、需要返回PS1(x)以供上层的节点计算其PS1 & PS2.

//4、对于leaf节点：PS1(x) = PS2(x) = x->val.

int maxPathSumHelper(TreeNode* root, int &maxSum) {
	if (!root)
		return 0;

	int maxPS1Left = 0, maxPS1Right = 0;

	if (root->left)
		maxPS1Left = max(maxPathSumHelper(root->left, maxSum), 0);
	if (root->right)
		maxPS1Right = max(maxPathSumHelper(root->right, maxSum), 0);
	//第一种路径
	int maxPS1 = max(maxPS1Left, maxPS1Right) + root->val;
	//第二种路径
	int maxPS2 = maxPS1Left + maxPS1Right + root->val;
	//求最大值
	maxSum = max(maxSum, max(maxPS1, maxPS2));

	//返回第一种路径，不能返回第二种路径，因为
	return maxPS1;
}

int maxPathSum(TreeNode* root) {
	if (!root)
		return 0;
	int maxSum = INT_MIN;
	maxPathSumHelper(root, maxSum);
	return maxSum;
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
	ListNode * l11 = new ListNode(1);
	ListNode * l12 = new ListNode(2);
	ListNode * l13 = new ListNode(3);
	ListNode * l14 = new ListNode(4);
	ListNode * l15 = new ListNode(5);
	ListNode * l16 = new ListNode(6);
	ListNode * l17 = new ListNode(7);
	ListNode * l18 = new ListNode(8);
	l11->next = l12;
	l12->next = l13;
	l12->next = NULL;
	l13->next = l14;
	l14->next = l15;
	l15->next = l16;
	l16->next = l17;
	l17->next = l18;
	l18->next = NULL;
	//ListNode * l21 = new ListNode(5);
	//ListNode * l22 = new ListNode(6);
	//ListNode * l23 = new ListNode(4);
	//l21->next = NULL;
	//l22->next = l23;
	//l23->next = NULL;
	//addTwoNumbers(l11, l21);
	//ListNode * l1 = new ListNode(5);
	//ListNode * l2 = new ListNode(5);
	//mergeTwoLists(l1, l2);

	//vector<int> vec = prime(20);
	//for (auto a : vec)
		//cout << a << endl;
	//getIntersectionNode(l11, l21);
	//oddEvenList(l11);
	//cout << getPermutation(4, "4132") << endl;
	reverseBetween(l11,1,2);
}