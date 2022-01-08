#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
//进程类
class Process {
    private:
		int pid;//进程id
	    string processname;//进程名
		int size;//进程所占内存
		int startAddress=-1;//该进程在内存中的起址
	public:
		Process(int t_pid, string t_processname, int t_size) :pid(t_pid), processname(t_processname), size(t_size){};
		void displayProcess() {
			cout <<"进程起址"<<startAddress<<"进程id"<<pid<< "进程名:" << processname << " 所占内存"<<size<<endl;
		}
		int getpid() {
			return pid;
		}
		string getprocessname() {
			return processname;
		}
		int getsize() {
			return size;
		}
		int getstartAddress() {
			return startAddress;
		}
		void changeStartAddress(int t_startAddress) {
			startAddress = t_startAddress;
		}
		~Process() {
			cout <<"进程名"<<processname<<"删除成功"<<endl;		
			cout << "------------------------------" << endl;
		}
};

//空闲区表项类
class freeArea {
private:
	int startAddress;//起址
	int length;//长度
	int state;//状态 0表示未分配，1表示分配 由于采用vector结构，其实没用
public:
	freeArea(int t_startAddress, int t_length, int t_state) :startAddress(t_startAddress), length(t_length), state(t_state) {}
	int getStartAddress() {
		return startAddress;
	}
	int getLength() {
		return length;
	}
	int getState() {
		return state;
	}
	void changeStartAddress(int t_startAddress) {
		startAddress = t_startAddress;
	}
	void changeLength(int t_length) {
		length = t_length;
	}
	void displayFreeArea() {
		cout << startAddress << "\t" << length << "\t" << state<<endl;
	}
	bool operator <(const freeArea& other) const
	{
		return startAddress > other.startAddress;
	}
};

//空闲区表类
class freeAreaTable {
private:
	vector<freeArea*> table;
	freeArea* temp_fa=NULL;//存储上次分配的位置 用于循环首次适应算法
public:
	freeAreaTable() {
		freeArea* area = new freeArea(0, 128, 0);
		table.push_back(area);
	}

	void displayTable() {
		cout << "------------------------------" << endl;
		cout << "起址\t长度\t状态" << endl;
		for (auto temp_t : table) {
			temp_t->displayFreeArea();
		}
	}
	//增加进程时，根据传入的进程更新空闲分区表 首次适应算法
	void updateByFF(Process* p) {
		for (auto temp_t : table) {
			if (temp_t->getLength() > p->getsize()) {
				//更改当前分配位置 用于循环首次适应算法
				temp_fa= temp_t;
				//更改进程信息
				p->changeStartAddress(temp_t->getStartAddress());
				//更改表
				temp_t->changeLength(temp_t->getLength() - p->getsize());
				temp_t->changeStartAddress(temp_t->getStartAddress() + p->getsize());
				break;
			}
		}
	}
	//最佳适应算法
	void updateByBF(Process* p) {
		int t_length = 1e7;
		freeArea* t=NULL;
		for (auto temp_t : table) {
			if (temp_t->getLength() > p->getsize() && temp_t->getLength()<t_length) {
				t = temp_t;
				t_length = temp_t->getLength();
			}
		}
		if (t != NULL) {
			//更改进程信息
			p->changeStartAddress(t->getStartAddress());
			//更改表
			t->changeLength(t->getLength() - p->getsize());
			t->changeStartAddress(t->getStartAddress() + p->getsize());
		}
	}
	//最坏适应算法
	void updateByWF(Process* p) {
		int t_length = 0;
		freeArea* t = NULL;
		for (auto temp_t : table){
			if (temp_t->getLength() > p->getsize() && temp_t->getLength() > t_length) {
				t = temp_t;
				t_length = temp_t->getLength();
			}
		}
		if (t != NULL) {
			//更改进程信息
			p->changeStartAddress(t->getStartAddress());
			//更改表
			t->changeLength(t->getLength() - p->getsize());
			t->changeStartAddress(t->getStartAddress() + p->getsize());
		}
	}
	//循环首次适应算法
	void updateByNF(Process* p) {
		//第一次分配 temp_fa为空
		if (temp_fa == NULL) {
			updateByFF(p);
			return;
		}
		else {
			//先找上次分配点后面的
			for (auto temp_t : table) {
				if (temp_t->getLength() > p->getsize() && temp_t->getStartAddress()>=temp_fa->getStartAddress()){
					temp_fa = temp_t;
					//更改进程信息
					p->changeStartAddress(temp_t->getStartAddress());
					//更改表
					temp_t->changeLength(temp_t->getLength() - p->getsize());
					temp_t->changeStartAddress(temp_t->getStartAddress() + p->getsize());
					return;
				}
			}
			//找不到再从头开始找
			updateByFF(p);
		}
	}
	
	static bool cmp(freeArea *fa1,freeArea* fa2) {
		return fa1->getStartAddress() < fa2->getStartAddress();
	}
	//对空闲分区表进行排序，使得空闲分区的各项起始地址为从低到高
	void sortTable() {
		sort(begin(table), end(table),cmp);
	}
	//在结束进程后，更新空闲分区表
	void freetable(Process* p){
		sortTable();
		freeArea* start_fa=NULL;//该分区用于应对结束进程分区在空闲分区后的情况
	    freeArea* end_fa=NULL;//该分区用于应对结束进程分区在空闲分区前的情况
		for (auto temp_fa : table) {
			//当前任务的终止恰好等于某个空闲分区的起址
			if (temp_fa->getStartAddress() == p->getstartAddress() + p->getsize()) {
				end_fa = temp_fa;
			}
			//当前任务的起址恰好等于某个空闲分区的终址
			if (temp_fa->getStartAddress() + temp_fa->getLength() == p->getstartAddress()) {
				start_fa = temp_fa;
			}
		}
		//重新开辟一个空闲区
		if (start_fa == NULL && end_fa == NULL) {
			freeArea* area = new freeArea(p->getstartAddress(),p->getsize(), 0);
			table.push_back(area);
			sortTable();

			temp_fa = area;
		}//增加上一个分区的长度
		else if(start_fa != NULL && end_fa == NULL) {
			start_fa->changeLength(start_fa->getLength()+p->getsize());

			temp_fa = start_fa;
		}//改变下一个分区的起址和长度
		else if (start_fa == NULL && end_fa != NULL) {
			end_fa->changeStartAddress(p->getstartAddress());
			end_fa->changeLength(end_fa->getLength() + p->getsize());

			temp_fa = end_fa;
		}//增加上一个分区的长度，去掉下一个分区
		else {
			start_fa->changeLength(start_fa->getLength() + p->getsize() + end_fa->getLength());
			
			temp_fa = start_fa;
			//删除下一个分区
			for (vector<freeArea*>::iterator it = table.begin(); it != table.end(); it++) {
				if ((*it)==end_fa) {
					delete* it;
					table.erase(it);
					return;
				}
			}
		}
	}
};

//进程管理类
class ProcessContainer {
    private:
		freeAreaTable freeareatable;
		vector<Process*> processList;
	public:

		//创建进程 startAddress为-1表示由系统分配，不为-1表示初始化
		Process*  createProcess(int pid,string processname,int size) {
			Process* p = new Process(pid,processname, size);
			return p;
		}

		//将进程加入进程队列
		void appendProcess(Process* p) {
			processList.push_back(p);
			//采用对应算法进行内存分配
			freeareatable.updateByNF(p);
			freeareatable.displayTable();
			cout << "进程名" << p->getprocessname() << "创建成功" << endl;
			cout << "------------------------------" << endl;
		}

		//给定进程id删除进程
		void popProcess(int pid) {
			for (vector<Process*>::iterator it = processList.begin(); it != processList.end(); it++) {
				if ((*it)->getpid() == pid) {
					freeareatable.freetable(*it);
					freeareatable.displayTable();
					delete* it;
					processList.erase(it);
					return;
				}
			}
			cout << "删除失败";
		}

		void displayAll() {
			for (auto temp_p : processList) {
				temp_p->displayProcess();
			}
		}
};


int main() {
	ProcessContainer pcontainer;
	Process* p0 = pcontainer.createProcess(0, "操作系统", 5);
	Process* p1 = pcontainer.createProcess(1, "作业1", 5);
	Process* p3 = pcontainer.createProcess(3, "作业3", 4);
	Process* p_temp = pcontainer.createProcess(-1, "临时进程", 12);//临时进程，用来修改空闲分区表使得与要求相同
	Process* p2 = pcontainer.createProcess(2, "作业2", 6);

	pcontainer.appendProcess(p0);
	pcontainer.appendProcess(p1);
	pcontainer.appendProcess(p3);
	pcontainer.appendProcess(p_temp);
	pcontainer.appendProcess(p2);
	pcontainer.popProcess(-1);
	cout << "空闲分区初始化成功"<<endl;

	Process* p4 = pcontainer.createProcess(4, "作业4", 6);
	pcontainer.appendProcess(p4);
	pcontainer.popProcess(3);
	pcontainer.popProcess(2);
}