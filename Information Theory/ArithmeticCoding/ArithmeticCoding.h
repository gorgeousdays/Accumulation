#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<assert.h>
using namespace std;

class ArithmeticCoding {
private:
	vector<double> originalList;
	vector<char> symbolList;
	vector<double> probabilityList;
	vector<vector<double>> rangeList;
	vector<int> resList;//result

	double probabilitySum;

	double t_low;
	double t_high;
	double t_range;
public:
	void init(vector<char>sList, vector<double>pList);
	void initByInput();
	bool checkProbability();//check the sum of probability =1

	double getLow(char symbol);//get the low range of the symbol
	double getHigh(char symbol);//get the high range of the symbol

	double toDec(vector<int> data);//bin to dec

	string readmessage(string file);
	void  writeanswer(string file, string message);

	void updatePriority(char sym);//update the priority
	void backUpdatePriority(char sym);

	string encoding(string s);
	string decoding(string s,int lengthOfMessage);
};