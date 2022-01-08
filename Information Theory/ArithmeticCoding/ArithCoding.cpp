#include<iostream>
#include<algorithm>
#include<string.h>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include <assert.h>
#include<fstream>
using namespace std;
typedef long long ll;

long long head = pow(10, 9);
long long second = pow(10, 8);

ll string2ll(string a) {
	ll ans = 0;
	ll wei = 1;
	for (int i = a.length() - 1; i >= 0; i--) {
		ans += (a[i] - '0') * wei;
		wei *= 10;
	}
	return ans;
}

//编码
void encode() {
	string original = "";//原文
	string code = "";//编码
	vector<int> fre;
	int total = 256;//总共可能出现的字符
	ll underflow = -1;
	ll undernum = 0;//下溢位数
	//初始化Low High
	ll l = 0;
	ll h = 9999999999;
	//读进原文
	ifstream in("input.txt");
	string tmp;
	while (getline(in, tmp)) {
		if (original == "") original = tmp;
		else {
			original += '\n' + tmp;
		}
	}
	original += "#";
	//初始化概率表
	for (int i = 0; i <= 255; i++) {
		fre.push_back(1);
	}
	//开始处理原文
	for (int i = 0; i < original.length(); i++) {
		int pos = int(original[i]);
		ll range = (h - l) + 1;
		ll num = 0;
		for (int j = 0; j < pos; j++) {
			num += fre[j];
		}
		h = l + range * (num + fre[pos]) / (total + 1) - 1;
		l = l + range * num / (total + 1);
		total++;
		fre[pos]++;
		//接下来开始移位
		//开始移位
		while ((l / head) == (h / head)) {
			ll d = l / head;
			code = code + char(l / head + '0');
			l = (l % head) * 10;
			h = (h % head) * 10 + 9;
			char add = '0';
			if (d == underflow) {///要用长整型！！！！！！
				add = '9';
			}
			while (undernum) {
				undernum--;
				code = code + add;
			}
			underflow = -1;
		}
		//处理下溢
		while (h - l < second) {
			if (underflow == -1)underflow = l / head;
			undernum++;
			int tmp = l / head;
			l = tmp * head + (l % second) * 10;
			tmp = h / head;
			h = tmp * head + (h % second) * 10 + 9;
		}
	}
	//全部遍历完成
	ll m = (l + h) / 2;
	string magic = to_string(m);
	while (magic.length() < 10) {
		magic = magic + "0";
	}
	code = code + magic;
	ofstream out("output.txt");
	out << code;
}

//解码
void decode() {
	string original = "";//原文
	string code = "";//编码
	vector<int> fre;
	int total = 256;//总共可能出现的字符
	ll underflow = -1;
	ll undernum = 0;
	//初始化Low High
	ll l = 0;
	ll h = 9999999999;
	//读进编码
	ifstream in("output.txt");
	in >> code;
	//初始化概率表
	for (int i = 0; i <= 255; i++) {
		fre.push_back(1);
	}
	ll curcode = string2ll(code.substr(0, 10));
	int pos = 10;//当前运行到第几个code了
	int cur = 257;
	//开始解码
	while (cur != int('#')) {
		ll tmp = l;
		ll range = (h - l) + 1;
		ll num = 0;
		for (int j = 0; j < fre.size(); j++) {
			ll th = tmp + range * (num + fre[j]) / (total + 1) - 1;
			ll tl = tmp + range * (num) / (total + 1);
			num += fre[j];
			if (curcode >= tl && curcode < th) {
				cur = j;
				l = tl;
				h = th;
				total++;
				fre[cur]++;
				break;
			}
		}
		if (cur != int('#')) {
			original = original + char(cur);
		}
		//开始移位
		while ((l / head) == (h / head)) {
			code = code + char(l / head + '0');
			l = (l % head) * 10;
			h = (h % head) * 10 + 9;
			curcode = (curcode % head) * 10 + code[pos] - '0';
			pos++;
		}
		//处理下溢
		while (h - l < second) {
			ll tmp = curcode / head;
			curcode = tmp * head + (curcode % second) * 10 + code[pos] - '0';
			pos++;
			tmp = l / head;
			l = tmp * head + (l % second) * 10;
			tmp = h / head;
			h = tmp * head + (h % second) * 10 + 9;
		}

	}
	ofstream out("ans.txt");
	out << original;
}


int main() {
	encode();
	decode();
	system("pause");
	return 0;
}
