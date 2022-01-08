#include "ArithmeticCoding.h"
using namespace std;
/*
int main() {
	
	ArithmeticCoding arithmeticCodingController;

	vector<char> symbolList = { 'a','b','c','d' };
	vector<double> probabilityList = { 25,25,25,25 };
	arithmeticCodingController.init(symbolList, probabilityList);

	//Read the message
	string message= arithmeticCodingController.readmessage("message.txt");
	//string message = "abcddcbaddca";

	cout << "The message is :" << message <<"\n";
	//Crypto :Arithmetic Coding  
	string cryptotext=arithmeticCodingController.encoding(message);

	//Print the answer
	cout << "Crypto:" << cryptotext<<"\n";

	arithmeticCodingController.init(symbolList, probabilityList);
	//Decrypto :Arithmetic Coding  
	string decryptotext = arithmeticCodingController.decoding(cryptotext,message.length());


	//Print the answer
	cout << "Decrypto:" << decryptotext<<"\n";
	
	//Save the answer
	arithmeticCodingController.writeanswer("result.txt", decryptotext);
	

}
*/