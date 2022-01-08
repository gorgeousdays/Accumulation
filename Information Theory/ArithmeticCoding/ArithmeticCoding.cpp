#include "ArithmeticCoding.h"


void ArithmeticCoding::init(vector<char>sList, vector<double>pList) {

	t_low = 0;
	t_high = 1;
	t_range = 1;
	probabilitySum = 100;

	probabilityList.clear();


	originalList = pList;
	for (auto p : pList) {
		probabilityList.push_back(p /probabilitySum);
	}
	
	symbolList = sList;
	if (checkProbability()) {
		cout << "OK,the sum of probability=1!\n";
	}
	else {
		cout << "Error!The sum of probability!=1";
	}

	//calculate the rangeList
	double low=0;
	for (int i = 0; i < probabilityList.size(); i++) {
		vector<double> temp;
		temp.push_back(low);
		low += probabilityList[i];
		temp.push_back(low);
		rangeList.push_back(temp);
	}

}

void ArithmeticCoding::initByInput() {
	int number;
	double probability;
	char symbol;
	cout << "Please enter the number of coding elements\n";
	cin >> number;
	for (int i = 1; i <= number; i++) {
		cout << i << " Please enter the symbol:";
		cin >> symbol;
		cout << i << " Please enter the probability:";
		cin >> probability;
		symbolList.push_back(symbol);
		probabilityList.push_back(probability);
	}
	if (checkProbability()) {
		cout << "OK!\n";
	}
	else {
		cout << "Error!The sum of probability!=1";
	}
}

bool ArithmeticCoding::checkProbability(){
	double sum = 0;
	for (auto p : probabilityList) {
		sum += p;
	}
	if (sum == 1) {
		return true;
	}
	else {
		return false;
	}
}

double ArithmeticCoding::getLow(char symbol){
	int i;
	for (i = 0; i <symbolList.size(); i++){
		if (symbolList[i] == symbol) {
			break;
		}
	}
	return rangeList[i][0];
}

double ArithmeticCoding::getHigh(char symbol) {
	int i;
	for (i = 0; i < symbolList.size(); i++) {
		if (symbolList[i] == symbol) {
			break;
		}
	}
	return rangeList[i][1];
}
double ArithmeticCoding::toDec(vector<int> data) {
	double ans = 0;
	for (int i = 0; i < data.size(); i++) {
		ans += data[i] * pow(2, -(i + 1));
	}
	return ans;
}

string ArithmeticCoding::readmessage(string file) {
	ifstream infile;
	infile.open(file.data());   
	assert(infile.is_open());  

	string s;
	getline(infile, s);
	/*
	while (getline(infile, s)) {
		cout << s << endl;
	}*/
	infile.close();
	return s;
}

void  ArithmeticCoding::writeanswer(string file, string message) {
	ofstream outfile;
	outfile.open(file.data());
	assert(outfile.is_open());

	outfile << message;

	outfile.close();
}

void ArithmeticCoding::updatePriority(char sym){
	probabilitySum += 1;

	for (int i = 0; i < symbolList.size(); i++) {
		if (symbolList[i] == sym) {
			originalList[i] += 1;
		}
	}

	for (int i = 0; i < originalList.size(); i++) {
		probabilityList[i]=originalList[i] / probabilitySum;
	}

	double low = 0;
	for (int i = 0; i < probabilityList.size(); i++) {
		vector<double> temp;
		temp.push_back(low);
		low += probabilityList[i];
		temp.push_back(low);
		rangeList[i]=temp;
	}
}

void ArithmeticCoding::backUpdatePriority(char sym) {
	probabilitySum -= 1;

	for (int i = 0; i < symbolList.size(); i++) {
		if (symbolList[i] == sym) {
			originalList[i] -= 1;
		}
	}

	for (int i = 0; i < originalList.size(); i++) {
		probabilityList[i] = originalList[i] / probabilitySum;
	}

	double low = 0;
	for (int i = 0; i < probabilityList.size(); i++) {
		vector<double> temp;
		temp.push_back(low);
		low += probabilityList[i];
		temp.push_back(low);
		rangeList[i] = temp;
	}
}

string ArithmeticCoding::encoding(string s) {
	cout << "encoding...\n";
	for (int i = 0; i < s.length(); i++) {
		char sym = s[i];
		updatePriority(sym);
		float low = t_low;

		t_low = low + t_range * getLow(sym);
		t_high = low + t_range * getHigh(sym);
		t_range = t_high - t_low;
	}
	//change to binary
	int k = 0;
	while (toDec(resList) < t_low) {
		
		resList.push_back(1);
		
		if (toDec(resList) > t_high) {
			resList[k] = 0;
		}
		k++;
	}
	string res = "";
	for (int i = 0; i < resList.size(); i++) {
		res+=char(resList[i]+48);//int to char ascii
	}

	return res;
}

string ArithmeticCoding::decoding(string s,int lengthOfMessage) {
	cout << "decoding...\n";
	/*
	for (int i = 0; i < s.length(); i++) {
		resList[i] = s[i];
	}*/

	double number = toDec(resList);

	string res = "";
	char symbol;
	while (lengthOfMessage > 0){
		for (int i = 0; i < rangeList.size(); i++) {
			symbol = symbolList[i];
			updatePriority(symbol);
			if (getLow(symbol) <= number &&number < getHigh(symbol)) {
				break;
			}
			backUpdatePriority(symbol);
		}
		res += symbol;
		double low = getLow(symbol);
		double high = getHigh(symbol);
		float range = high - low;
		number = (number - low) / range;
		lengthOfMessage--;
	};
	return res;
}