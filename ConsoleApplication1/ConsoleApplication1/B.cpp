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

//排好序的数组，找两个数等于target
vector<int> twoSumII(vector<int>& numbers, int target) {
	vector<int> res = {};
	if (numbers.size() == 0 || target < numbers[0])
		return res;
	int size = numbers.size() - 1;
	int start = 0, end = size;
	while (start < end) {
		if (start > 0 && numbers[start] == numbers[start - 1]) {
			start++;
			continue;
		}
		if (end < size && numbers[end] == numbers[end + 1]) {
			end--;
			continue;
		}
		if (numbers[start] + numbers[end] < target)
			start++;
		else if (numbers[start] + numbers[end] > target)
			end--;
		else {
			//找到了
			res.push_back(numbers[start]);
			res.push_back(numbers[end]);
			start++;
			end--;
		}
	}
	return res;
}

//找三个数，加起来等于0
//不需额外的空间
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
		ListNode* left = helper(lists, l, m);
		ListNode* right = helper(lists, m + 1, r);
		return mergeTwoLists(left, right);
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

//找到两个链表的交界处
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
	if (!headA || !headB)
		return NULL;
	ListNode* cur1 = headA;
	ListNode* cur2 = headB;
	while (cur1 != cur2) {
		cur1 = cur1 ? cur1->next : headB;
		cur2 = cur2 ? cur2->next : headA;
	}
	return cur1;
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


//删除重复元素解法一
ListNode* deleteDuplicatesM1(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode* cur = head;
	while (cur) {
		if (cur->next) {
			if (cur->val == cur->next->val) {
				cur->next = cur->next->next;
			}
			else
				cur = cur->next;
		}
		else
			break;
	}
	return head;
}

//删除重复元素解法二
ListNode* deleteDuplicates(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode* pre = new ListNode(-1);
	pre->next = head;
	ListNode* res = pre;
	while (pre->next) {
		ListNode* cur = pre->next;
		//开始从这一点走，只要和下一个值相同就往前走
		while (cur->next && cur->val == cur->next->val)
			cur = cur->next;
		//判断cur有没有往前走，如果有，说明有重复元素，现在cur所指向的是最后一个重复元素，保留它，下一次从它开始算
		if (cur != pre->next)
			pre->next = cur;
		else
			pre = pre->next;
	}
	return res->next;
}

//删除所有重复元素
ListNode* deleteDuplicatesII(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode* pre = new ListNode(-1);
	pre->next = head;
	ListNode* res = pre;
	while (pre->next) {
		ListNode* cur = pre->next;
		//开始从这一点走，只要和下一个值相同就往前走
		while (cur->next && cur->val == cur->next->val)
			cur = cur->next;
		//判断cur有没有往前走，如果有，说明有重复元素，现在cur所指向的是最后一个重复元素，删除它
		if (cur != pre->next)
			pre->next = cur->next;
		else
			pre = pre->next;
	}
	return res->next;
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

ListNode* merge(ListNode* l1, ListNode* l2) {
	if (!l1)
		return l2;
	if (!l2)
		return l1;
	if (l1->val < l2->val) {
		l1->next = merge(l1->next, l2);
		return l1;
	}
	else
	{
		l2->next = merge(l1, l2->next);
		return l2;
	}
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

//反转链表递归
ListNode* reverseList(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode *newHead = reverseList(head->next);
	//把头结点的next赋值成空
	head->next->next = head;
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
	while (i < n - m + 1) {
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
		temp = temp->next->next;
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

////买卖股票系列，只能进行两次交易
////解法一，以i天为分割点，profit[0,i]为在第i天之前进行一次交易所获得的最大利润，
////profit[i,n-1]表示在第i天之后进行一次交易所获得的最大利润
////那么最大利润profit[0,n-1]=max(profit[0,i],profit[i,n-1])，而这两段的最大利润可以分别求出来
//int maxProfit(vector<int>& prices) {
//	if (prices.size() == 0)
//		return 0;
//	int size = prices.size();
//	int res = 0;
//	vector<int> leftProfit(size, 0);
//	int minPrice = prices[0];
//	int maxLeftProfit = 0;
//	for (int i = 1; i < size; i++) {
//		if (prices[i] < minPrice)
//			minPrice = prices[i];
//		else
//			maxLeftProfit = max(maxLeftProfit, prices[i] - minPrice);
//		leftProfit[i] = maxLeftProfit;
//	}
//
//	int maxPrice = prices[size - 1];
//	int rightProfit = 0;
//	for (int i = size - 2; i >= 0; i--) {
//		if (prices[i] > maxPrice)
//			maxPrice = prices[i];
//		else
//			rightProfit = max(rightProfit, maxPrice - prices[i]);
//		res = max(res, rightProfit + leftProfit[i]);
//	}
//	return res;
//}
//
////解法二
////我们定义local[i][j]为在到达第i天时最多可进行j次交易并且最后一次交易在最后一天卖出的最大利润，此为局部最优。
////然后我们定义global[i][j]为在到达第i天时最多可进行j次交易的最大利润，此为全局最优。它们的递推式为：
////local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)(前一天卖出了又后悔了，改为这一天卖出)
////global[i][j] = max(local[i][j], global[i - 1][j])
////其中局部最优值是比较前一天并少交易一次的全局最优加上大于0的差值，和前一天的局部最优加上差值中取较大值，
////而全局最优比较局部最优和前一天的全局最优
//int maxProfitII(vector<int>& prices) {
//	if (prices.size() == 0)
//		return 0;
//	int size = prices.size();
//	int local[100000][3] = { 0 };
//	int global[100000][3] = { 0 };
//	for (int i = 1; i < size; i++) {
//		int diff = prices[i] - prices[i - 1];
//		for (int j = 1; j <= 2; j++) {
//			local[i][j] = max(global[i - 1][j - 1] + max(diff,0), local[i - 1][j] + diff);
//			global[i][j] = max(global[i - 1][j], local[i][j]);
//		}
//	}
//	return global[size-1][2];
//}

//最多可以进行k次交易
//使用“局部最优和全局最优解法”。我们维护两种量，
//一个是当前到达第i天可以最多进行j次交易，最好的利润是多少（global[i][j]），
//另一个是当前到达第i天，最多可进行j次交易，并且最后一次交易在当天卖出的最好的利润是多少（local[i][j]）。
//下面我们来看递推式，
//global[i][j] = max(local[i][j], global[i - 1][j])，
//也就是去当前局部最好的，和过往全局最好的中大的那个（因为最后一次交易如果包含当前天一定在局部最好的里面，否则一定在过往全局最优的里面）。
//local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)，
//也就是看两个量，第一个是全局到i - 1天进行j - 1次交易，然后加上今天的交易，如果今天是赚钱的话（也就是前面只要j - 1次交易，最后一次交易取当前天），
//第二个量则是取local第i - 1天j次交易，然后加上今天的差值（这里因为local[i - 1][j]比如包含第i - 1天卖出的交易，所以现在变成第i天卖出，并不会增加交易次数，而且这里无论diff是不是大于0都一定要加上，否则就不满足local[i][j]必须在最后一天卖出的条件了）。
int solveMaxProfit(vector<int> &prices) {
	int res = 0;
	for (int i = 1; i < prices.size(); ++i) {
		if (prices[i] - prices[i - 1] > 0) {
			res += prices[i] - prices[i - 1];
		}
	}
	return res;
}
int maxProfitIII(int k, vector<int> &prices) {
	if (prices.empty()) return 0;
	if (k >= prices.size()) return solveMaxProfit(prices);
	int size = prices.size();
	int local[100][100] = { { 0 } };
	int global[100][100] = { { 0 } };
	for (int i = 1; i < size; i++) {
		int diff = prices[i] - prices[i - 1];
		for (int j = 1; j <= k; j++) {
			local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff);
			global[i][j] = max(global[i - 1][j], local[i][j]);
		}
	}
	return global[size - 1][k];
}

//卖出后，休息一天再买入，设置两个数组buy和sell:
//buy[i] 买进操作的最大利润。它需要考虑的是，第i天是否买进。（手上没有stock在第i天所能获得的最大利润）maximize profits we decide buy or not buy a stock at day i.
//sell[i] 卖出操作的最大利润。它需要考虑的是，第i天是否卖出。（手上有stock在第i天所能获得的最大利润） maximize profits we sell or not sell a stock at day i.
//buy[i] = max(buy[i-1],sell[i-2] - prices[i]) because we cooldown one day.
//sell[i] = max(sell[i-1],buy[i-1] + prices[i]);
int maxProfitWithCooldown(vector<int>& prices) {
	int size = prices.size();
	if (size < 2) return 0;
	int buy[10000] = { 0 };
	int sell[10000] = { 0 };
	buy[0] = -prices[0];
	buy[1] = max(-prices[0], -prices[1]);
	sell[1] = max(0, prices[1] - prices[0]);
	for (int i = 2; i < size; i++) {
		buy[i] = max(sell[i - 2] - prices[i], buy[i - 1]); //在第i天买进和不买进的最大值
		sell[i] = max(buy[i - 1] + prices[i], sell[i - 1]); //在第i天卖出和不卖出的最大值
	}
	return sell[size - 1];
}

//求乘积最大的连续子集
//注意，既要维护上一步的最大值又要维护最小值，因为最小值乘以一个负数有可能变为最大值。
int maxProduct(vector<int>& nums) {
	int size = nums.size();
	if (size == 0)
		return 0;
	if (size == 1)
		return nums[0];
	int maxProduct;
	int minProduct;
	int res = nums[0];
	maxProduct = nums[0], minProduct = nums[0];
	for (int i = 1; i < size; i++) {
		int maxCur = maxProduct, minCur = minProduct;
		maxProduct = max(max(nums[i], nums[i] * maxCur), nums[i] * minCur);
		minProduct = min(min(nums[i], nums[i] * minCur), nums[i] * maxCur);
		res = max(res, maxProduct);
	}
	return res;
}

int updateMatrixHelper(vector<vector<int>>& matrix, int startRow, int startCol, vector<vector<bool>>& visited, vector<vector<int>>& dp, int res) {
	int row = matrix.size();
	int col = matrix[0].size();
	if (!(startRow >= 0 && startRow < row && startCol >= 0 && startCol < col && !visited[startRow][startCol]))
		return INT_MAX;
	if(visited[startRow][startCol])
		return INT_MAX;
	if (matrix[startRow][startCol] == 0)
		return res;
	if (dp[startRow][startCol] != -1)
		return dp[startRow][startCol];
	//上下左右
	vector<vector<int>> dirs = { { -1,0 },{ 0,-1 } ,{ 1,0 },{ 0,1 } };
	visited[startRow][startCol] = true;
	/*for (vector<int> dir : dirs) {
		int x = startRow + dir[0];
		int y = startCol + dir[1];
		if (x >= 0 && x < row && y >= 0 && y < col && !visited[x][y]) {
			curRes = min(curRes, updateMatrixHelper(matrix, x, y, visited, dp, res + 1));
		}
	}*/
	int x = startRow;
	int y = startCol;
	int resTop = updateMatrixHelper(matrix, x - 1, y, visited, dp, res + 1);
	int resdown = updateMatrixHelper(matrix, x + 1, y, visited, dp, res + 1);
	int resLeft = updateMatrixHelper(matrix, x, y - 1, visited, dp, res + 1);
	int resRight = updateMatrixHelper(matrix, x, y + 1, visited, dp, res + 1);
	int curRes = min(min(resTop, resdown), min(resLeft, resRight));
	visited[startRow][startCol] = false;
	dp[startRow][startCol] = curRes;
	return curRes;
}
//给一个矩阵，里面有零和1，找到离每个1到0的最短路径，上下左右分别算一步
vector<vector<int>> updateMatrix(vector<vector<int>>& matrix) {
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return matrix;
	int row = matrix.size();
	int col = matrix[0].size();
	vector<vector<bool>> visited(row, vector<bool>(col, false));
	vector<vector<int>> dp(row, vector<int>(col, -1));
	vector<vector<int>> res(row, vector<int>(col));
	res = matrix;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (matrix[i][j] == 0)
				continue;
			else {
				int curRes = updateMatrixHelper(matrix, i, j, visited, dp, 0);
				res[i][j] = (curRes != INT_MAX) ? curRes : res[i][j];
			}
		}
	}
	return res;
}

bool check(int x, int y, int n, int m) {
	if (x >= 0 && x < n && y >= 0 && y < m) 
		return 1;
	return 0;
}

//给一个矩阵，里面有零和1，找到离每个1到0的最短路径，上下左右分别算一步
vector<vector<int>> updateMatrixIterative(vector<vector<int>>& matrix) {
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return matrix;
	int row = matrix.size();
	int col = matrix[0].size();
	vector<vector<int>> res(row, vector<int>(col,0));
	queue<pair<int, int>> matrixQ;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (matrix[i][j] == 0) {
				matrixQ.push(make_pair(i, j));
			}
			else {
				res[i][j] = INT_MAX;
			}
		}
	}
	
	while (!matrixQ.empty()) {
		int x = matrixQ.front().first;
		int y = matrixQ.front().second;
		matrixQ.pop();
		//上下左右
		vector<vector<int>> dirs = { { -1,0 },{ 0,-1 } ,{ 1,0 },{ 0,1 } };
		for (vector<int> dir : dirs) {
			int cx = x + dir[0];
			int cy = y + dir[1];
			if (check(cx, cy, row, col)) {
				//需要更新cx,cy所对应的距离值，并把这个点入队列
				if (res[cx][cy] > res[x][y] + 1) {
					res[cx][cy] = res[x][y] + 1;
					matrixQ.push(make_pair(cx, cy));
				}
			}
		}
	}
	return res;
}

//这道题类似一种迷宫问题，规定了-1表示墙，0表示门，让求每个点到门的最近的曼哈顿距离，
void wallsAndGates(vector<vector<int>>& rooms) {
	if (rooms.size() == 0 || rooms[0].size() == 0)
		return;
	int row = rooms.size();
	int col = rooms[0].size();

	queue<pair<int, int>> matrixQ;
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if (rooms[i][j] == 0) {
				matrixQ.push(make_pair(i, j));
			}
		}
	}
	while (!matrixQ.empty()) {
		int x = matrixQ.front().first;
		int y = matrixQ.front().second;
		matrixQ.pop();
		//上下左右
		vector<vector<int>> dirs = { { -1,0 },{ 0,-1 } ,{ 1,0 },{ 0,1 } };
		for (vector<int> dir : dirs) {
			int cx = x + dir[0];
			int cy = y + dir[1];
			if (check(cx, cy, row, col)) {
				if (rooms[cx][cy] > rooms[x][y] + 1) {
					rooms[cx][cy] = rooms[x][y] + 1;
					matrixQ.push(make_pair(cx, cy));
				}
			}
		}
	}
}

ListNode* sortListhelper(ListNode* head) {
	if (!head || !head->next)
		return head;
	ListNode* mid = head, *temp = head, *pre = head;
	//找中间节点。用两个快慢指针，快指针每次走两步，慢指针每次走一步，当快指针走到最后一个时，慢指针走到中间
	while (temp != NULL && temp->next != NULL) {
		pre = mid;
		mid = mid->next;
		temp = temp->next;
	}
	//把两个list断开
	pre->next = NULL;
	ListNode* left = sortListhelper(head);//head->pre
	ListNode* right = sortListhelper(mid);//mid->temp

	return merge(left, right);
}
//排序链表
ListNode* sortList(ListNode* head) {
	if (!head || !head->next)
		return head;
	return sortListhelper(head);
}

//划分list，大于x的放在前面，小于x的放在后面
ListNode* partition(ListNode* head, int x) {
	if (!head || !head->next)
		return head;
	ListNode* left = new ListNode(-1);
	ListNode* resL = left;
	ListNode* right = new ListNode(-1);
	ListNode* resR = right;
	ListNode* act = head;
	while (act) {
		if (act->val < x) {
			left->next = act;
			left = left->next;
		}else
		{
			right->next = act;
			right = right->next;
		}
		act = act->next;
	}
	left->next = resR->next;
	right->next = NULL;
	act = resL->next;
	return act;
}

//最久最少使用，看时间
class LRUCache {
public:
	struct CacheEntry {
		int key;
		int value;
		CacheEntry(int k,int v):key(k),value(v){}
	};

	LRUCache(int capacity) {
		m_capacity = capacity;
	}

	int get(int key) {
		if (m_map.find(key) != m_map.end()) {
			moveToHead(key);
			return m_map[key]->value;
		}
		//没找到
		else
			return -1;
	}

	void put(int key, int value) {
		//如果没有这个元素，直接插入
		if (m_map.find(key) == m_map.end()) {
			CacheEntry newItem(key, value);
			if (m_LRU_cache.size() >= m_capacity) {
				//删除最后一个，先清除map，再删掉结点
				m_map.erase(m_LRU_cache.back().key);//用key来删除
				m_LRU_cache.pop_back();
			}
			m_LRU_cache.push_front(newItem); //新元素是最近刚访问的，插入头部
			m_map[key] = m_LRU_cache.begin();//更新map关系
		}
		//如果有这个元素，更新值
		m_map[key]->value = value;
		moveToHead(key);
	}
private:
	int m_capacity;
	unordered_map<int, list<CacheEntry>::iterator> m_map;
	list<CacheEntry> m_LRU_cache;

	void moveToHead(int key) {
		list<CacheEntry>::iterator updateEntry = m_map[key];
		m_LRU_cache.erase(updateEntry);//注意，list的erase函数参数是迭代器，所以m_map里用list<CacheEntry>::iterator
		m_LRU_cache.push_front(*updateEntry); //这个元素是最近刚访问的，插入头部
		m_map[key] = m_LRU_cache.begin();//更新map关系
	}
};

//最近最少使用，看使用频率
class LFUCache {
public:
	struct CacheEntry {
		int key;
		int value;
		int freq;
		CacheEntry(int k, int v) :key(k), value(v) {}
	};

	LFUCache(int capacity) {
		m_capacity = capacity;
	}

	int get(int key) {
		if (m_map.find(key) != m_map.end()) {
			CacheEntry* temp = m_map[key];
			temp->freq++;
			m_map[key] = temp;
			return temp->value;
		}
		return -1;
	}

	void put(int key, int value) {
		if (m_capacity == 0)
			return;
		CacheEntry* temp;
		if (m_map.find(key) != m_map.end()) {
			temp = m_map[key];
			temp->freq++;
			temp->value = value;
		}
		else {
			if (m_map.size() >= m_capacity) {
				m_map.erase(minFreq);
			}
			temp = new CacheEntry(key, value);
			temp->freq = 1;
		}
		m_map[key] = temp;
		minFreq = 1;
	}

private:
	int m_capacity;
	int minFreq;
	map<int, CacheEntry*> m_map;
	int getLFUKey() {
		//获取要删除的元素
		int minFrequency = INT_MAX;
		int keyRes = 0;
		for (auto cur : m_map) {
			if (cur.second->freq <= minFrequency) {
				keyRes = cur.second->key;
				minFrequency = cur.second->freq;
			}
		}
		return keyRes;
	}
};

//找所有加起来等于target的组合
void combinationSumHelper(vector<int> &candidates, int target, vector<vector<int> > &res, vector<int> &combination, int cur, int begin)
{
	if (target == cur) {
		res.push_back(combination);
		return;
	}
	//cur <= target条件很重要，过滤掉一些不可能条件，让循环终止
	for (int i = begin; i < candidates.size() && cur <= target; ++i) {
		combination.push_back(candidates[i]);
		combinationSumHelper(candidates, target, res, combination, cur + candidates[i], i);
		combination.pop_back();
	}
}

vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
	//排序很重要
	sort(candidates.begin(), candidates.end());
	vector<vector<int> > res;
	vector<int> combination;
	combinationSumHelper(candidates, target, res, combination, 0, 0);
	return res;
}

void combinationSum2(vector<int> &candidates, int target, vector<vector<int> > &res, vector<int> &combination, int cur, int begin) {
	if (cur == target) {
		res.push_back(combination);
		return;
	}
	for (int i = begin; i != candidates.size() && cur <= target; ++i) {
		if (i == begin || candidates[i] != candidates[i - 1]) {
			combination.push_back(candidates[i]);
			combinationSum2(candidates, target, res, combination, cur + candidates[i], i + 1);
			combination.pop_back();
		}
	}
}
vector<vector<int> > combinationSum2(vector<int> &candidates, int target) {
	sort(candidates.begin(), candidates.end());
	vector<vector<int> > res;
	vector<int> combination;
	combinationSum2(candidates, target, res, combination, 0,0);
	return res;
}

//按照二叉树的方式rob，下面的方法只适合于左右子树高度一致的情况
int rob(TreeNode* root) {
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return root->val;
	//开始层级遍历
	vector<int> res;
	queue<TreeNode*> myQueue;
	myQueue.push(root);
	while (!myQueue.empty()) {
		int size = myQueue.size();
		int sum = 0;
		for (int i = 0; i < size; i++) {
			TreeNode* cur = myQueue.front();
			sum += cur->val;
			myQueue.pop();
			if(cur->left)
				myQueue.push(cur->left);
			if (cur->right)
				myQueue.push(cur->right);
		}
		res.push_back(sum);
	}

	int dp[100000];
	memset(dp, 0, sizeof(dp));
	int size = sizeof(dp);
	dp[0] = res[0];
	dp[1] = max(res[0], res[1]);
	for (int i = 2; i < size; i++) {
		dp[i] = max(dp[i - 2] + res[i], dp[i - 1]);
	}
	return dp[res.size()-1];
}

int robHelper(TreeNode* root, unordered_map<TreeNode*, int>& myMap) {
	if (!root)
		return 0;
	if (myMap.find(root) != myMap.end())
		return myMap[root];
	int val = 0;
	if (root->left) {
		val += robHelper(root->left->left, myMap) + robHelper(root->left->right, myMap);
	}
	if (root->right) {
		val += robHelper(root->right->left, myMap) + robHelper(root->right->right, myMap);
	}
	val = max(root->val + val, robHelper(root->left, myMap) + robHelper(root->right, myMap));
	myMap[root] = val;
	return val;
}

//更加通用，适合各种高度
//分析，对于一个节点来说，该节点的最大值就是max(该节点的值加上不包括其左右子节点的最大值，左右子节点的最大值之和)
//注意我们记录中间变量，防止重复运算
int robII(TreeNode* root) {
	if (!root)
		return 0;
	if (!root->left && !root->right)
		return root->val;
	unordered_map<TreeNode*, int> myMap;
	robHelper(root, myMap);
	return myMap[root];
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
	ListNode * l11 = new ListNode(2);
	ListNode * l12 = new ListNode(1);
	ListNode * l13 = new ListNode(3);
	ListNode * l14 = new ListNode(2);
	ListNode * l15 = new ListNode(5);
	ListNode * l16 = new ListNode(2);
	ListNode * l17 = new ListNode(7);
	ListNode * l18 = new ListNode(8);
	l11->next = l12;
	l12->next = NULL;
	l13->next = l14;
	l14->next = l15;
	l15->next = l16;
	l16->next = NULL;
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
	//reverseBetween(l11,1,2);
	//vector<int> vec = { 1,2 };
	//vector<vector<int>> vec = { {0,0,0},{0,1,0},{1,1,1} };
	//updateMatrix(vec);
	//cout << maxProfitIII(1, vec);
	//partition(l11, 2);
	//LFUCache *L = new LFUCache(2);
	//L->put(1, 1);
	//L->put(2, 2);
	//L->get(1);
	vector<int> candidates = { 2,3,6,7 };
	combinationSum(candidates, 7);
}