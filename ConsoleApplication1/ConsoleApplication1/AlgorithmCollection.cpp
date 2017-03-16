#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <list>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include "AlgorithmCollection.h"

using namespace std;

AlgorithmCollection::AlgorithmCollection() {

}

int AlgorithmCollection::binSearch(int m[], int low, int high, int target) {

	//sizeof(m) / sizeof(m[0]) - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (target < m[mid]) {
			high = mid - 1;
		}
		else if (m[mid] < target) {
			low = mid + 1;
		}
		else
			return mid;
	}
	//return  -1;
	return mid;
}

//一般的插入排序，每次内层循环从i开始递减，前一个大于后一个就交换，外层循环为遍历整个数组。
void AlgorithmCollection::insertSorting(int m[], int length) {
	int temp;
	for (int i = 1; i < length; i++) {
		for (int j = i; j >0; j--) {
			if (m[j - 1] > m[j]) {
				temp = m[j - 1];
				m[j - 1] = m[j];
				m[j] = temp;
			}
			else
				break;
		}
	}
}

//利用二分查找的插入排序
void AlgorithmCollection::insertSortingByBinSearch(int m[], int length) {
	int temp;
	int k;
	for (int i = 1; i < length; i++) {
		temp = m[i];  //先把m[i]记下来
		if (m[i - 1] <= temp) {  //如果m[i]大于m[i-1]
			k = i; //m[i]的位置不变，也就是从0-i都是有序的
		}
		else {
			k = binSearch(m, 0, i - 1, temp);  //找到m[i]的位置就是k
			for (int j = i; j > k; j--) {
				m[j] = m[j - 1];  //从k到i一个一个向后移,把k的位置腾出来
			}
		}
		m[k] = temp;//把保存起来的m[i]的值赋给m[k].
	}
}

//内层循环比较相邻的两个元素，前面的大于后面的就交换，每次都把最大的数放到数组尾部，外层循环遍历整个数组
void AlgorithmCollection::bubbleSort(int m[], int length)
{
	int temp;
	for (int i = length - 1; i > 0; i--) {
		for (int j = 0; j < i; j++) {
			if (m[j] > m[j + 1]) {
				temp = m[j];
				m[j] = m[j + 1];
				m[j + 1] = temp;
			}
		}
	}
}

int AlgorithmCollection::partion(int m[], int left, int right) {
	int storeIndexLeft = left;  //left指针
	int storeIndexRight = right; //right指针
	int flag = 0;
	int pivot = m[right]; //记录最右边的元素为枢纽
	while (storeIndexLeft != storeIndexRight) {
		if (flag == 0) {
			if (m[storeIndexLeft] > pivot) {
				m[storeIndexRight] = m[storeIndexLeft];//比枢纽大的通通移动到右边
				storeIndexRight--;//右指针往回退一步
				flag = 1;//开始判断右指针与pivot的关系
			}
			else
				storeIndexLeft++; //left往前移一步
		}
		else {
			if (m[storeIndexRight] < pivot) {
				m[storeIndexLeft] = m[storeIndexRight]; //比枢纽小的通通移动到右边
				storeIndexLeft++;//左指针往前进一步
				flag = 0;//开始判断左指针与pivot的关系
			}
			else
				storeIndexRight--; //left往前移一步
		}
	}
	m[storeIndexLeft] = pivot;
	return storeIndexLeft;  //返回枢纽位置
}

void AlgorithmCollection::quickSort(int m[], int left, int right) {
	if (left > right)
		return;
	int storeIndex;
	storeIndex = partion(m, left, right);  //第一次划分
	quickSort(m, left, storeIndex - 1);
	quickSort(m, storeIndex + 1, right);
}


//快速排序高级解法来自王小明
void quicksortAdvanced(int a[], int low, int high)
{
	if (low < high)
	{
		int i = low;
		int j = high;
		int x = a[high];
		while (i < j)
		{
			while (i < j && x > a[i])
				i++;

			if (i < j)
				a[j--] = a[i];

			while (i < j && x < a[j])
				j--;

			if (i < j)
				a[i++] = a[j];
		}
		a[i] = x;
		quicksortAdvanced(a, low, i - 1);
		quicksortAdvanced(a, i + 1, high);
	}
}

void AlgorithmCollection::permutationOfString(char pStr[], int begin, int end) {
	if (begin == end - 1) {
		for (int i = 0; i < end; i++)
			cout << pStr[i];
		cout << endl;
	}
	else {
		for (int k = begin; k < end; k++) {
			swapForChar(pStr[k], pStr[begin]);
			permutationOfString(pStr, begin + 1, end);
			swapForChar(pStr[k], pStr[begin]);
		}
	}
}

int AlgorithmCollection::digitToValue(char c) {
	if (c >= '0' && c <= '9') return c - '0';
	else if (c >= 'A' && c <= 'F') return 10 + c - 'A';
	else if (c >= 'a' && c <= 'f') return 10 + c - 'a';
	return 0;
}

int AlgorithmCollection::ConvertToBase(string number, int base) {
	if (base < 2 || (base > 10 & base != 16))
		return -1;
	int value = 0;
	//开始求值
	for (int i = number.length(); i >= 0; i--) {
		int digit = digitToValue(number[i]);
		if (digit < 0 || digit >= base) {
			return -1;
		}
		int exp = number.length() - 1 - i;
		value += digit * pow(base, exp);
	}
	return value;
}

void AlgorithmCollection::swapForInt(int &m, int &n) {
	int temp = m;
	m = n;
	n = temp;
}

void AlgorithmCollection::swapForChar(char &m, char &n) {
	char temp = m;
	m = n;
	n = temp;
}

void AlgorithmCollection::reverse(int m[], int length) {
	for (int i = 0; i < length / 2; i++) {
		swapForInt(m[i], m[length - 1 - i]);
	}
}

list<char> AlgorithmCollection::LetterCount(list<char> listSource) {
	list<char> listTemp;
	list<char>::iterator itor;
	itor = listSource.begin();
	while (itor != listSource.end()) {
		char temp = *itor;
		int count = 0;
		while (itor != listSource.end() && temp == *itor) {
			count++;
			itor++;
		}
		listTemp.push_back(temp);
		listTemp.push_back(count);
	}
	if (listTemp.size() != listSource.size())
		return listTemp;
	else
		return listSource;
}

int AlgorithmCollection::removeDuplicates(int A[], int n) {
	if (n == 0) {
		return 0;
	}
	int j = 0;
	for (int i = 1; i < n; i++) {
		if (A[j] != A[i]) {  
			//j代表新的数组的当前下标，放到新数组里的元素都是不重复的，所以每次判断当前的a[j]和a[i]就可以了，注意不可以判断a[i]和a[i+1]
			A[++j] = A[i];
		}
	}
	return j + 1;
}

int removeDuplicatesII(vector<int>& nums) {
	if (nums.size() == 0)
		return 0;
	int j = 0;
	int count = 0;
	for (int i = 1; i < nums.size(); i++) {
		if (nums[i] == nums[j]){
			count++;
			if (count <= 1) {
				nums[++j] = nums[i];
			}
			else
				continue;
		}
		else {
			nums[++j] = nums[i];
			count = 0;
		}
	}
	return j + 1;
}

vector<int> AlgorithmCollection::plusOne(vector<int> &digits) {
	vector<int> res(digits.size(), 0);
	int sum = 0;
	int one = 1;
	for (int i = digits.size() - 1; i >= 0; i--) {
		sum = one + digits[i];
		one = sum / 10;
		res[i] = sum % 10;
	} if (one > 0) {  //最高位需要进位，在向量头部插入一个元素
		res.insert(res.begin(), one);
	}
	for (int j = 0; j <= res.size() - 1; j--) {
		cout << res[j] << endl;
	}
	return res;
}

queue<AlgorithmCollection::Node*> AlgorithmCollection::depthFirstSearch() {
	const int TREE_SIZE = 9;
	stack<Node*> unvisited;
	queue<Node*> visited;//保存顺序的队列
	Node nodes[TREE_SIZE];
	Node* current;

	//初始化树
	for (int i = 0; i < TREE_SIZE; i++) {
		nodes[i].self = i;
		int child = i * 2 + 1;
		if (child < TREE_SIZE)
			nodes[i].left = &nodes[child];
		else
			nodes[i].left = NULL;
		child++;
		if (child < TREE_SIZE)
			nodes[i].right = &nodes[child];
		else
			nodes[i].right = NULL;
	}

	//初始情况，根节点先入栈
	unvisited.push(&nodes[0]);

	//总体思想，依照栈先进后出的规则，从根结点开始，本节点弹出后,对于每一个栈顶结点，右节点入栈再左结点入栈，然后继续循环。
	while (!unvisited.empty()) {
		current = (unvisited.top());  //拿到栈顶元素
		unvisited.pop();  //栈顶出栈
		if (current->right != NULL)
			unvisited.push(current->right); //先入栈的访问次序在后
		if (current->left != NULL)
			unvisited.push(current->left); //后入栈的先访问
		cout << current->self << endl;
		visited.push(current);
	}
	return visited;
}

queue<AlgorithmCollection::Node*> AlgorithmCollection::widthFirstSearch() {
	queue<Node*> visited, unvisited;
	const int TREE_SIZE = 9;
	static Node nodes[TREE_SIZE];
	Node* current;

	//初始化树
	for (int i = 0; i < TREE_SIZE; i++) {
		nodes[i].self = i;
		int child = i * 2 + 1;
		if (child < TREE_SIZE)
			nodes[i].left = &nodes[child];
		else
			nodes[i].left = NULL;
		child++;
		if (child < TREE_SIZE)
			nodes[i].right = &nodes[child];
		else
			nodes[i].right = NULL;
	}

	//初始根节点先入队列
	unvisited.push(&nodes[0]);

	//总体思想，利用队列的先进先出原则，从根节点开始，对于每一个队列首结点，本节点弹出后,左节点先入队列，右节点后入队列，继续循环。
	while (!unvisited.empty()) {
		current = unvisited.front(); //队列首元素
									 //把current出队列，开始访问下一个元素
		unvisited.pop();
		if (current->left != NULL)
			unvisited.push(current->left);
		if (current->right != NULL)
			unvisited.push(current->right);

		//最终保持访问顺序的队列
		visited.push(current);
		cout << current->self << endl;
	}
	return visited;
}

void printQueue(queue<AlgorithmCollection::Node*> myQueue) {
	while (!myQueue.empty()) {
		cout << myQueue.front()->self << endl;
		myQueue.pop();
	}
}

UndirectedGraphNode* UndirectedGraphNode::cloneGraph(UndirectedGraphNode *node) {
	if (node == NULL)
		return NULL;

	//开辟新空间
	UndirectedGraphNode *copy = new UndirectedGraphNode(node->label);
	//源节点和克隆节点的map，避免重复创建复制节点
	unordered_map<UndirectedGraphNode*, UndirectedGraphNode*> cmap;
	//用于广度优先搜索的queue
	queue<UndirectedGraphNode*> graphQ;
	//根节点入队列
	graphQ.push(node);
	//再map里记录根节点与其克隆节点的对应关系
	cmap.insert({ node,copy });

	//开始广度优先遍历结点
	while (!graphQ.empty()) {
		//当前处理元素
		UndirectedGraphNode* cur = graphQ.front();
		graphQ.pop();
		//开始一个一个复制当前结点的邻居信息
		for (int i = 0; i < cur->neighbors.size(); i++) {
			UndirectedGraphNode *neighbor = cur->neighbors[i];
			//如果之前没有拷贝过
			if (cmap.find(neighbor) == cmap.end()) {
				UndirectedGraphNode* neighborClone = new UndirectedGraphNode(neighbor->label);
				cmap[cur]->neighbors.push_back(neighborClone);
				cmap.insert({ neighbor , neighborClone }); //对应一开始的UndirectedGraphNode* curClone = cmap[cur]
				graphQ.push(neighbor);
			}
			else {
				cmap[cur]->neighbors.push_back(cmap[neighbor]);
			}
		}
	}
	return copy;
}

int AlgorithmCollection::ladderLength(string start, string end, unordered_set<string> &dict) {
	if (start == end)
		return 1;
	int n = start.size();
	if (n < 1 || n != end.size())
		return 0;

	queue<string> Q;
	Q.push(start);
	dict.erase(start);
	int length = 2;

	//基于广度优先搜索图
	while (!Q.empty()) {
		int size = Q.size();
		//注意，在循环外面递增length
		//因为考虑到word变换某一字母后会出现多种情况，所有的情况下length只加一，而不是每种情况都要加一，就相当于这些情况在图中处于同一层，高度一样。
		for (int i = 0; i < size; i++) {
			string word = Q.front();
			Q.pop();
			//开始逐个字母的变换start
			for (int i = 0; i < n; i++) {
				char oldChar = word[i];
				for (char c = 'a'; c <= 'z'; c++) {
					if (c == oldChar) continue;
					word[i] = c;
					if (word == end) {
						return length;
					}
					if (dict.find(word) != dict.end()) {
						//如果dict里有这个单词，说明这是我们需要的台阶，把这个单词入队列，下次循环处理他，从他开始再找台阶
						Q.push(word);
						//把检查过的单词从dict里排除
						dict.erase(word);
					}
				}
				//恢复成原来的word
				word[i] = oldChar;
			}
		}
		length++;
	}
	return 0;
}

bool AlgorithmCollection::exist(vector<vector<char>> &board, string word) {
	if (board.empty() || board[0].empty())
		return false;
	//记录搜索状态
	vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), false));
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			//注意这里word首元素开始，从每个元素开始，向它的上下左右四个方向开始搜索。
			if (wordSearch(board, visited, i, j, word, 0))
				return true;
		}
	}
	return false;
}

bool AlgorithmCollection::wordSearch(vector<vector<char>> &board, vector<vector<bool>> &visited, int row, int col, string word, int index) {
	if (index == word.size())
		return true;
	if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size() || visited[row][col] || board[row][col] != word[index]) {
		return false;
	}

	//注意，当从这个（row,col）开始上下左右搜索的时候，本节点是访问过了的，所以要写成true
	visited[row][col] = true;
	bool res = wordSearch(board, visited, row - 1, col, word, index + 1) ||
		wordSearch(board, visited, row + 1, col, word, index + 1) ||
		wordSearch(board, visited, row, col - 1, word, index + 1) ||
		wordSearch(board, visited, row, col + 1, word, index + 1);
	//以下一个结点作为起始搜索结点时，本节点是可被访问的，理解。
	visited[row][col] = false;

	return res;
}

const int MAX_LENGTH = 65535;
int min(int a[], int length) {
	if (length <= 0)
		return MAX_LENGTH;
	int minal = a[0];
	for (int i = 0; i < length; i++) {
		if (a[i] < minal)
			minal = a[i];
	}
	return minal;
}

int searchLine(vector<vector<string>> &myMap, vector<vector<bool>> &visited, int row, int col, string newStart, string end, int length) {
	if (row >= myMap.size() || col >= myMap[0].size() || row < 0 || col < 0)
		return MAX_LENGTH;  //没找到，返回一个很大的数
	if (myMap[row][col] == end)
		return length;
	if (visited[row][col])
		return MAX_LENGTH;
	if (myMap[row][col] == newStart)
		length++;
	//int all[4] = { MAX_LENGTH ,MAX_LENGTH ,MAX_LENGTH ,MAX_LENGTH };
	//在同一线路，换乘数不变
	visited[row][col] = true;
	/*//all[0] = searchLine(myMap, visited, row, col - 1, end, length);
	//all[1] = searchLine(myMap, visited, row, col + 1, end, length);
	//上下看如果存在不同线路上有两个相同的站点的话，换乘数加一
	if (!(row >= myMap.size()-1 || row < 0)) {
	if (myMap[row + 1][col] == myMap[row][col])
	all[2] = searchLine(myMap, visited, row + 1, col, end, length + 1);

	}
	if (!(row >= myMap.size() || row <= 0)) {
	if (myMap[row - 1][col] == myMap[row][col])
	all[3] = searchLine(myMap, visited, row - 1, col, end, length + 1);
	}
	for (int i = 1; i < myMap.size(); i++) {
	for (int j = 1; j < myMap[0].size(); j++) {
	//all.push_back();
	if (!(row + i < 0 || row + i >= myMap.size() || col + j < 0 || col + j >= myMap[0].size())) {
	if (myMap[row + i][col + j] == myMap[row][col])
	length++;
	cout << length;

	}
	}
	}*/
	vector<int> all;  //记录所有找到的换乘数
	for (int i = 0; i < myMap.size(); i++) {
		for (int j = 0; j < myMap[0].size(); j++) {
			if (i == 0 && j == 0)
				continue;
			//开始从start开始向四面八方搜索
			if (!(row + i < 0 || row + i >= myMap.size() || col + j < 0 || col + j >= myMap[0].size())) {
				newStart = myMap[row + i][col + j];
				all.push_back(searchLine(myMap, visited, row + i, col + j, newStart, end, length));
			}
			if (!(row + i < 0 || row + i >= myMap.size() || col - j < 0 || col - j >= myMap[0].size())) {
				newStart = myMap[row + i][col - j];
				all.push_back(searchLine(myMap, visited, row + i, col - j, newStart, end, length));
			}
			if (!(row - i < 0 || row - i >= myMap.size() || col + j < 0 || col + j >= myMap[0].size())) {
				newStart = myMap[row - i][col + j];
				all.push_back(searchLine(myMap, visited, row - i, col + j, newStart, end, length));
			}
			if (!(row - i < 0 || row - i >= myMap.size() || col - j < 0 || col - j >= myMap[0].size())) {
				newStart = myMap[row - i][col - j];
				all.push_back(searchLine(myMap, visited, row - i, col - j, newStart, end, length));
			}
		}
	}
	visited[row][col] = false;
	int minal = MAX_LENGTH;
	for (int i = 1; i < all.size(); i++) {
		if (all[i] < minal)
			minal = all[i];
	}
	return minal;
}


int findMinTransfer(vector<vector<string>> &myMap, string start, string end) {
	//先找到start所在的坐标
	int rowOfStart;
	int colOfStart;
	int length = 0;
	for (int i = 0; i < myMap.size(); i++) {
		for (int j = 0; j < myMap[0].size(); j++) {
			if (myMap[i][j] == start) {
				rowOfStart = i;
				colOfStart = j;
				break;
			}
		}
	}
	vector<vector<bool>> visited(myMap.size(), vector<bool>(myMap[0].size(), false));
	vector<int> all;  //记录所有找到的换乘数
	return searchLine(myMap, visited, rowOfStart, colOfStart, start, end, length);
}

//反转一个字符串，较快的解法
void reverse(string s) {
	int len = s.size();
	string newstr = s;
	for (int i = 0; i < len / 2; i++) {
		newstr[i] = s[len - i];
		newstr[len - i] = s[i];
	}
	cout << newstr << endl;
}

void AlgorithmCollection::fill(vector<vector<char>> &board, int i, int j, char target, char c) {
	if (i < 0 || i> board.size() || j < 0 || j < board[0].size())
		return;

	board[i][j] = c;
	//在上下左右四个方向找联通区域，dfs递归
	if (j - 1 > 0 && j - 1 < board[0].size() && board[i][j - 1] == target)
		fill(board, i, j - 1, target, c);
	if (j + 1 > 0 && j + 1 < board[0].size() && board[i][j + 1] == target)
		fill(board, i, j + 1, target, c);
	if (i - 1 > 0 && i - 1 < board.size() && board[i - 1][j] == target)
		fill(board, i - 1, j, target, c);
	if (i + 1 > 0 && i + 1 < board.size() && board[i + 1][j] == target)
		fill(board, i + 1, j, target, c);

	//迭代版本
	stack<pair<int, int>> kicked;
	kicked.push(make_pair(i, j));

	int m, n;
	while (!kicked.empty()) {
		i = kicked.top().first;
		j = kicked.top().second;
		board[i][j] = c;
		kicked.pop();
		if (j - 1 > 0 && j - 1 < board[0].size() && board[i][j - 1] == target)
			kicked.push(make_pair(i, j - 1));
		if (j + 1 > 0 && j + 1 < board[0].size() && board[i][j + 1] == target)
			kicked.push(make_pair(i, j + 1));
		if (i - 1 > 0 && i - 1 < board.size() && board[i - 1][j] == target)
			kicked.push(make_pair(i - 1, j));
		if (i + 1 > 0 && i + 1 < board.size() && board[i + 1][j] == target)
			kicked.push(make_pair(i + 1, j));
	}
}

//把边缘涉及的联通区域染成第三色
void AlgorithmCollection::fillBorders(vector<vector<char>> &board, char target, char c) {
	//染竖边
	for (int i = 0; i < board.size(); i++) {
		//如果边上有o，就顺着这个o继续染，找到这个o的连通区域
		if (board[i][0] == target)
			fill(board, i, 0, target, c);
		if (board[i][board[0].size() - 1] == target)
			fill(board, i, board[0].size() - 1, target, c);
	}
	//染横边
	for (int j = 0; j < board[0].size(); j++) {
		if (board[0][j] == target)
			fill(board, 0, j, target, c);
		if (board[board.size() - 1][j] == target)
			fill(board, board.size() - 1, j, target, c);
	}
}
//把边缘涉及的联通区域再染回去
void AlgorithmCollection::replace(vector<vector<char>> &board, char target, char c) {
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] == target)
				board[i][j] = c;
		}
	}
}
void AlgorithmCollection::solve(vector<vector<char>> &board) {
	fillBorders(board, 'o', 'Y');
	replace(board, 'o', 'x');
	replace(board, 'Y', 'o');
}

//找最长连续子串
int AlgorithmCollection::findLongestSequence(int a[], int size) {
	unordered_set<int> mySet;
	for (int i = 0; i < size; i++) {
		mySet.insert(a[i]);
	}

	int maxLength = 0;

	for (int m = 0; m < mySet.size(); m++) {
		if (mySet.empty()) break; // mySet变空，说明循环结束了，所有的元素都被移除去了。
		int current = a[m];
		int currentLength = 0;  //此次循环里对应的最大长度

		//往前找
		while (mySet.count(current)) {
			mySet.erase(current);
			currentLength++;
			current++;
		}

		//往后找
		current = a[m] - 1;
		while (mySet.count(current)) {
			mySet.erase(current);
			currentLength++;
			current--;
		}

		if (currentLength > maxLength)
			maxLength = currentLength;
	}
	return maxLength;
}

vector<int> findDisapperNum(vector<int> &nums) {
	unordered_set<int> b;
	vector<int> result;
	for (int i = 0; i < nums.size(); i++) {
		b.insert(nums[i]);
	}
	for (int i = 0; i <= nums.size(); i++) {
		if (b.find(i) == b.end()) {
			cout << i;
			if (i != 0)
				result.push_back(i);
		}
	}
	return result;
}

int AlgorithmCollection::lengthOfLongestNonRepeatedSubs(string s) {
	unordered_set<char> mySet;
	stack<int> ss;
	int currentLength = 1;
	//mySet.insert(s[0]);

	//int j = 0;

	//for (int i = 1; i < s.size(); i++) {
	//	if (mySet.find(s[i]) == mySet.end()) {  //不重复
	//		mySet.insert(s[i]);
	//		currentLength++;
	//		continue;
	//	}
	//	else {
	//		if (currentLength > maxLength)
	//			maxLength = currentLength;
	//		//移除重复元素以及其之前的元素
	//		//难度：在set里面不记录各个元素的位置，这里根据位置来移除元素很难实现
	//		mySet.clear();  //清除
	//		mySet.insert(s[i]); //插入当前的元素
	//	}
	//}
	//解法二：
	//int maxLength = 1;
	//char visit[256];  //记录某一元素被访问过的下标
	//int dp[256]; //每个元素对应的不重复子串长度
	//memset(visit, -1, 256);
	//memset(dp, 0, 256);
	//dp[0] = 1;
	//visit[s[0]] = 0;
	//for (int i = 1; i < s.size(); i++) {
	//	//注意visited用元素值作为下标，这样我们查找该元素时的时间是常量，类似于hash.
	//	if (visit[s[i]] == -1) { //没出现过该元素
	//		dp[i] = dp[i - 1] + 1;//length+1就好了
	//		visit[s[i]] = i; //记录每个元素的下标
	//	}
	//	else {//如果出现过
	//		dp[i] = i - visit[s[i]];//注意这里的运算，当前元素下标所对应的字串长度是当前下标值减去该元素上次出现时的下标，改下标记录在visit数组里。
	//		visit[s[i]] = i; //记录重复元素的下标
	//	}
	//	if (dp[i] > maxLength) {
	//		maxLength = dp[i];
	//	}
	//}
	//return maxLength;

	//解法三，解法二里visit长度我们只能固定，有可能会数组越界
	//还是用以前的思路，找到一个重复的元素就把它以及它之前的元素删除，但该解法引述新的数据结构unordered_map
	unordered_map<char, int> ht;  //用hash实现的，内存占用多查找时间复杂度低，map用红黑树实现，内存占用少查找时间复杂度高
	int maxlength = 0;
	int curLength = 0;
	int start = 0;
	for (int i = 0; i < s.size(); i++) {
		if (ht.find(s[i]) != ht.end()) {  //该元素出现过
										  //开始删除
			for (int m = start; m < ht[s[i]]; m++) {
				ht.erase(s[m]);
			}
			start = ht[s[i]] + 1;
			curLength = i - ht[s[i]];
			ht.erase(s[i]);  //把重复了的那个元素删除，不删也可以，下面会更新该元素低音的下标值
		}
		else {
			curLength++;
		}

		ht[s[i]] = i;//更新重复元素的下标值

		if (curLength > maxlength)
			maxlength = curLength;
	}
	return maxlength;
}

int singleNumber(vector<int>& nums) {
	int numsLen = nums.size();
	int sum = 0, i = 0;
	vector<int> tmp((numsLen / 2) + 1, 0);

	for (i = 0; i<numsLen; i++)
	{
		int j = 0;
		for (j = 0; j<i; j++)
		{
			if (nums[i] == tmp[j])
			{
				tmp[j] = 0;
			}
		}
		if (j == i)
		{
			tmp[j] = nums[i];
		}
	}

	for (int k = 0; k<tmp.size(); k++)
	{
		sum = sum + tmp[k];
	}

	return sum;
}

//最长公共子串
//以字符串中的每个字符作为子串的端点，判定以此为开始的子串的相同字符最长能达到的长度。
int AlgorithmCollection::findCommonLongestSubstring(string &a, string &b) {
	int size_a = a.size();
	int size_b = b.size();
	int currentLength = 0;
	int maxLength = 0;

	for (int i = 0; i < size_a; i++) {
		for (int j = 0; j < size_b; j++) {
			int m = 0;
			int n = 0;

			//currentLength置为0
			currentLength = 0;

			while (m < size_a && n < size_b) {
				if (a[m] != b[n])
					break;
				m++;
				n++;
				currentLength++;
			}

			if (currentLength > maxLength) {
				maxLength = currentLength;
			}
		}
	}
	return currentLength;
}

//假设两个字符串分别为s和t，s[i]和t[j]分别表示其第i和第j个字符(字符顺序从0开始)，
//再令L[i, j]表示以s[i]和s[j]为结尾的相同子串的最大长度。
//应该不难递推出L[i, j]和L[i+1,j+1]之间的关系，因为两者其实只差s[i+1]和t[j+1]这一对字符。
//若s[i+1]和t[j+1]不同，那么L[i+1, j+1]自然应该是0，因为任何以它们为结尾的子串都不可能完全相同；
//而如果s[i+1]和t[j+1]相同，那么就只要在以s[i]和t[j]结尾的最长相同子串之后分别添上这两个字符即可，这样就可以让长度增加一位。
//合并上述两种情况，也就得到L[i+1,j+1]=(s[i+1]==t[j+1]?L[i,j]+1:0)这样的关系。
int AlgorithmCollection::findCommonLongestSubstringWithDP(string &a, string &b) {
	int size_a = a.size();
	int size_b = b.size();
	int maxLength = 0;

	//保存以a[i]和b[j]结尾的最长的子串长度
	vector<vector<int>> myVector(size_a, vector<int>(size_b));

	//考虑到L[i+1,j+1]=(s[i+1]==t[j+1]?L[i,j]+1:0)，我们应该先把L[i,j]算出来，下面是初始情况
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

	for (int i = 0; i < size_a; i++) {
		for (int j = 0; j < size_b; j++) {
			if (myVector[i][j] > maxLength)
				maxLength = myVector[i][j];
		}
	}

	return maxLength;
}

//求公共最长前缀
string AlgorithmCollection::findLongestCommonPrefix(vector<string> &strs) {
	//考虑到各个字符串的长度并不都是相同，所以我们用最短的字符串来做判断；
	string res = "";
	if (strs.empty())
		return res;
	if (strs.size() == 1) {
		res = strs[0];
		return strs[0];
	}

	int i = 0;
	int m = 0;
	char current;
	while (m < strs[0].size()) {
		current = strs[0][m];  //从第一个字符开始
		while (i < strs.size()) {
			if (m < strs[i].size() && strs[i][m] == current) {
				i++;
			}
			else {
				return res;
			}
		}

		res += current;
		m++;
		i = 0;
	}
	return res;
}
/*
int main(){
int m[] = { 1, 3, 5, 7, 9, 10, 15, 28 };
int n[] = { 4, 6, 5, 3, 2, 11, 1, 2, 18, 0, 16 };
AlgorithmCollection *ac = new AlgorithmCollection();
//cout << ac->binSearch(m, 7, 50);
//ac->insertSorting(n, 7);
//ac->insertSortingByBinSearch(n, 7);
//ac->bubbleSort(n, 7);
//ac->quickSort(n, 0, 10);
//ac->quickSort(n, 0, 10);
/*ac->reverse(n, 11);
for (int i = 0; i < 11; i++){
cout << n[i] << endl;
}*/
//cout << ac->digitToValue('B') << endl;
//cout << ac->ConvertToBase("010101", 2);
/*list<char> listTemp;
for (int i = 0; i < 3; i++)
listTemp.push_back('a');
for (int i = 0; i < 2; i++)
listTemp.push_back('b');
for (int i = 0; i < 4; i++)
listTemp.push_back('c');
for (int i = 0; i < 3; i++)
listTemp.push_back('a');
list<char> listDest = ac->LetterCount(listTemp);
list<char>::iterator itor = listDest.begin();
while (itor != listDest.end())
cout << *itor++ << endl;
;
vector<int> a(10, 9);
//ac->plusOne(a);
//printQueue(ac->depthFirstSearch());
queue<AlgorithmCollection::Node*> myqueue = ac->widthFirstSearch();
printQueue(myqueue);
char s[10];
for (int i = 0; i < 10; i++) {
s[i] = '1';
}
for (int i = 0; i < 10; i++) {
cout << s[i];
}
reverse("awt");
vector<vector<string>> myMap(4, vector<string>(3));
myMap[0][0] = "a";
myMap[0][1] = "b";
myMap[0][2] = "c";
myMap[1][0] = "e";
myMap[1][1] = "b";
myMap[1][2] = "d";
myMap[2][0] = "n";
myMap[2][1] = "m";
myMap[2][2] = "d";
myMap[3][0] = "h";
myMap[3][1] = "m";
myMap[3][2] = "z";
string start = "z";
string end = "a";
cout << findMinTransfer(myMap, start, end);
vector<int> vec(9);
vec[0] = 4;
vec[1] = 3;
vec[2] = 2;
vec[3] = 7;
vec[4] = 8;
vec[6] = 2;
vec[7] = 3;
vec[8] = 1;
vector<int> vec2(2);
vec2[0] = 1;
vec2[1] = 1;
//findDisapperNum(vec2);
string s = "abcabcbb";
string s2 = "pwwkew";
cout << lengthOfLongestNonRepeatedSubs(s);

system("pause");
return 0;
}
*/

