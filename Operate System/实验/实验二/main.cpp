#include<windows.h>
#include<iostream>
#include<string>
#include<queue>
#define N 32
#define WaitTime 100
using namespace std;


HANDLE Mutex;//�����ź���
HANDLE isFull;//ͬ���ź���
HANDLE isEmpty;//���л���������

string  buffer[N];//���干������
queue<int> productionQueue;

//������Ʒ
string  produce() {
	string production = to_string(rand());
	cout << "��ǰ������ƷΪ��" << production<<endl;
	return production;
}


//ѡ��һ���ջ������������Ʒ
void putProductionToBuffer(string production) {
	for (int i = 0; i < N; i++) {
		if (buffer[i] == "") {
			buffer[i] = production;
			productionQueue.push(i);
			break;
		}
	}
	cout << "���²�Ʒ�ѷ��뻺������" << production << endl;

	cout << "��ǰ�������У�";
	for (int i = 0; i < N; i++) {
		cout << buffer[i]<<" ";
	}
	cout << endl;
}

//�ӻ�������ȡ����Ʒ ���ö��������ȳ�
string getProductionFromBuffer() {
	string production;
	production=buffer[productionQueue.front()];
	buffer[productionQueue.front()] = "";
	productionQueue.pop();
	
	cout << "�Ѵӻ�������ȡ����Ʒ��" << production<<endl;
	return production;
}

//���Ѳ�Ʒ
void consume(string production) {
	cout << "��ǰ���Ѳ�ƷΪ��" << production<<endl;
}


void producer() {
	while(TRUE) {
		string production=produce();//����
		if (WaitForSingleObject(isEmpty, WaitTime) == WAIT_OBJECT_0) {//���������ڿ���ռ�
			if (WaitForSingleObject(Mutex, WaitTime) == WAIT_OBJECT_0) { //û�����������ڷ����ٽ���
				putProductionToBuffer(production);//����Ʒ���뻺����
				ReleaseMutex(Mutex);
				ReleaseSemaphore(isFull, 1, NULL);
			}
		}
	}
}

void consumer(){
	while (TRUE) {
		if (WaitForSingleObject(isFull, WaitTime) == WAIT_OBJECT_0) {
			if (WaitForSingleObject(Mutex, WaitTime) == WAIT_OBJECT_0) {
				string production=getProductionFromBuffer();//�ӻ�����ȡ����Ʒ
				ReleaseMutex(Mutex);
				ReleaseSemaphore(isEmpty, 1, NULL);
				consume(production);//����
			}
		}
	}
}

int main() {
	srand((unsigned)time(NULL));
	HANDLE producer1=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(producer), 0, 0, 0);
	HANDLE consumer1=CreateThread(NULL, 0, LPTHREAD_START_ROUTINE(consumer), 0, 0, 0);
	isFull = CreateSemaphore(NULL, 0, N, NULL);
	isEmpty = CreateSemaphore(NULL, N, N, NULL);
	Mutex = CreateMutex(NULL, FALSE, LPCWSTR("mutex"));

	system("pause");
	return 0;

}