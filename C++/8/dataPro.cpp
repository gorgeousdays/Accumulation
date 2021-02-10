#include"datePro.h"
#include"date.h"
#include<iostream>
#include<map>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;
void pr302A(istream& cin, ostream& out) {
	map<string, int>sd;
	string n,fs;
	for (Date d; cin >> n >> d >> fs;) 
		sd[n] = d.getAbsDay() + (fs == "Out" ? 0 : 1 - sd[n]);
	cout << "统计天数：\n";
	for (map<string, int>::const_iterator it = sd.begin(); it != sd.end(); ++it)
		cout << left << setw(10) << it->first << right << setw(5) << it->second << "\n";
}

struct NameNum {
	NameNum(const string& s, const Date& d) :name(s), num(d.getAbsDay()){}
	NameNum(const string&s,int n):name(s),num(n){}
	string name;
	int num;
};
bool operator<(const NameNum& n1, const NameNum& n2) {
	return n1.num == n2.num ? (n1.name < n2.name) : (n1.num < n2.num);
}
void pr302B(istream& cin, ostream& out) {
	vector<NameNum> nd;
	Date curDay;
	cin >> curDay;
	int n;
	for (string s; cin >> s >> n;)
		nd.push_back(NameNum(s, curDay + n));
	sort(nd.begin(), nd.end());
	cout << "推排日期：\n";
	for (int i = 0; i < nd.size(); ++i)
		cout << left << setw(11) << nd[i].name << Date(nd[i].num) << "\n";
}
void pr302C(istream& cin, ostream& out) {
	vector<NameNum> nd;
	Date curDay, d;
	cin >> curDay;
	for (string s; cin >> s >> d;)
		nd.push_back(NameNum(s, d - curDay));
	sort(nd.begin(), nd.end());
	cout << "确定天数：\n";
	for (int i = 0; i < nd.size(); ++i)
		cout << nd[i].name << " " << nd[i].num << "\n";
}
void pr302D(istream& cin, ostream& out) {
	cout << "星期几：\n";
	for (Date d; cin >> d;)
		cout << d.getWeekDay() << "\n";
}
void pr302E(istream& cin, ostream& out) {
	Date a, b, d, mD;
	int n, maxd = 0;
	cin >> a >> b >> n;
	cin.ignore();
	for (string s, t; getline(cin, s); a = d + 1) {
		istringstream sin(s);
		sin >> d;
		if (d - a > maxd)maxd = d - a, mD = a;
		sin >> d;
	}
	if (b - a + 1 > maxd) maxd = b - a + 1, mD = a;
	d = mD + (maxd - n) / 2;
	cout << "安排会议：\n";
	d.print(cout, d.MDYY);
	cout << "\n";
}