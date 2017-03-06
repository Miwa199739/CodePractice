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
#include <iomanip>
#include "Algorithm2.h"

using namespace std;

void gettingDigits() {
	int T;
	string line;

	//²âÊÔÓÃ
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
int main() {
	//int T;
	//string empty, line;
	//int ROW, COL;

	////²âÊÔÓÃ
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
	gettingDigits();
	return 0;
}