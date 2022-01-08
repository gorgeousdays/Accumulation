#include<windows.h>
#include<iostream>
#include<string>
#include<queue>
#define N 32
#define WaitTime 100
using namespace std;


HANDLE Mutex;//互斥信号量
HANDLE isFull;//同步信号量
HANDLE isEmpty;//空闲缓冲区数量

string  buffer[N];//定义共享缓冲区
queue<int> productionQueue;

//生产产品
string  produce() {
	string production = to_string(rand());
	cout << "当前生产产品为：" << production<<endl;
	return production;
}


//选择一个空缓冲区并放入产品
void putProductionToBuffer(string production) {
	for (int i = 0; i < N; i++) {
		if (buffer[i] == "") {
			buffer[i] = production;
			productionQueue.push(i);
			break;
		}
	}
	cout << "以下产品已放入缓冲区：" << production << endl;

	cout << "当前缓冲区有：";
	for (int i = 0; i < N; i++) {
		cout << buffer[i]<<" ";
	}
	cout << endl;
}

//从缓冲区中取出产品 采用队列先入先出
string getProductionFromBuffer() {
	string production;
	production=buffer[productionQueue.front()];
	buffer[productionQueue.front()] = "";
	productionQueue.pop();
	
	cout << "已从缓存区中取出产品：" << production<<endl;
	return production;
}

//消费产品
void consume(string production) {
	cout << "当前消费产品为：" << production<<endl;
}


void producer() {
	while(TRUE) {
		string production=produce();//生产
		if (WaitForSingleObject(isEmpty, WaitTime) == WAIT_OBJECT_0) {//缓冲区存在空余空间
			if (WaitForSingleObject(Mutex, WaitTime) == WAIT_OBJECT_0) { //没有其它对象在访问临界区
				putProductionToBuffer(production);//将产品放入缓冲区
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
				string production=getProductionFromBuffer();//从缓冲区取出产品
				ReleaseMutex(Mutex);
				ReleaseSemaphore(isEmpty, 1, NULL);
				consume(production);//消费
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