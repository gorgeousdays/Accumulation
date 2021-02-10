#include"date.h";
#include"myExcept.h"
#include<iostream>
#include<iomanip>
using namespace std;
const int Date::tians[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
const char* Date::week[] = { "Sun.","Mon.","Tue.","Wed.","Thu.","Fri.","Sat." };
Date::Date(const string& s) {
	int y = 1000 * (s[0] - '0') + 100 * (s[1] - '0') + 10 * (s[2] - '0') + s[3] - '0';
	int m = 10 * (s[5] - '0') + s[6] - '0';
	int d = 10 * (s[8] - '0') + s[9] - '0';
	_ymd2i(y, m, d);
}
void Date::_ymd2i(int y, int m, int d) {
	if (y <= 0 || y > 9999)
		throw MyIllegal();
	if (m <= 0 || m > 12)
		throw MyIllegal();
	if (d <= 0 || d > tians[m] - tians[m - 1] + m == 2 && isLeapYear())
		throw MyIllegal();
	int ny = (y - 1) * 365 + (y - 1) / 4 - (y - 1) / 100 + (y - 1) / 400;
	_absDay = ny + tians[m - 1] + d + (m > 2 && _isLeapYear(y));
}
void Date::_i2ymd(int& y, int& m, int& d)const {
	int n400 = _absDay / 146097;
	int y400 = _absDay % 146097;
	int n100 = y400 / 36524;
	int y100 = y400 % 36524;
	int n4 = y100 / 1461;
	int y4 = y100 % 1461;
	int n1 = y4 / 365;
	int y1 = y4 % 365;
	y = n400 * 400 + n100 * 100 + n4 * 4 + n1 + (y1 != 0);
	m = 12;
	if (y1 == 0)
		d = 30 + (n1 != 4);
	else {
		while (y1 <= (n1 == 3 && m > 2) + tians[m]) m--;
		d = y1 - tians[m] - (n1 == 3 && m >= 2);
		m++;
	}
}
void Date::print(ostream& o, int type)const {
	int y, m, d;
	_i2ymd(y, m, d);
	o <<right<<setfill('0');
	switch (type) {
	    case YMD:o << setw(2) << y % 100 << "-" << setw(2) << m << "-" << setw(2) << d; break;
	    case MDY:o << setw(2) <<m << "-" << setw(2) << d<< "-" << setw(2) << y%100; break;
	    case YYMD:o << setw(4) << y  << "-" << setw(2) << m << "-" << setw(2) << d; break;
	    case MDYY:o << setw(2) << m << "-" << setw(2) << d << "-" << setw(4) << y; break;
		default:throw MyFormatError();
	}
	o << setfill(' ');
}
bool Date::isLeapYear() const {
	int y, m, d;
	_i2ymd(y, m, d);
	return _isLeapYear(y);
}
istream& operator>>(istream& i, Date& d) {
	string s;
	if (i >> s)
		d = Date(s);
	return i;
}
ostream& operator<<(ostream& o, const Date& d) {
	d.print(o, d.YYMD);
	return o;
}