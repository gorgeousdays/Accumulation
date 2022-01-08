#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
//������
class Process {
    private:
		int pid;//����id
	    string processname;//������
		int size;//������ռ�ڴ�
		int startAddress=-1;//�ý������ڴ��е���ַ
	public:
		Process(int t_pid, string t_processname, int t_size) :pid(t_pid), processname(t_processname), size(t_size){};
		void displayProcess() {
			cout <<"������ַ"<<startAddress<<"����id"<<pid<< "������:" << processname << " ��ռ�ڴ�"<<size<<endl;
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
			cout <<"������"<<processname<<"ɾ���ɹ�"<<endl;		
			cout << "------------------------------" << endl;
		}
};

//������������
class freeArea {
private:
	int startAddress;//��ַ
	int length;//����
	int state;//״̬ 0��ʾδ���䣬1��ʾ���� ���ڲ���vector�ṹ����ʵû��
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

//����������
class freeAreaTable {
private:
	vector<freeArea*> table;
	freeArea* temp_fa=NULL;//�洢�ϴη����λ�� ����ѭ���״���Ӧ�㷨
public:
	freeAreaTable() {
		freeArea* area = new freeArea(0, 128, 0);
		table.push_back(area);
	}

	void displayTable() {
		cout << "------------------------------" << endl;
		cout << "��ַ\t����\t״̬" << endl;
		for (auto temp_t : table) {
			temp_t->displayFreeArea();
		}
	}
	//���ӽ���ʱ�����ݴ���Ľ��̸��¿��з����� �״���Ӧ�㷨
	void updateByFF(Process* p) {
		for (auto temp_t : table) {
			if (temp_t->getLength() > p->getsize()) {
				//���ĵ�ǰ����λ�� ����ѭ���״���Ӧ�㷨
				temp_fa= temp_t;
				//���Ľ�����Ϣ
				p->changeStartAddress(temp_t->getStartAddress());
				//���ı�
				temp_t->changeLength(temp_t->getLength() - p->getsize());
				temp_t->changeStartAddress(temp_t->getStartAddress() + p->getsize());
				break;
			}
		}
	}
	//�����Ӧ�㷨
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
			//���Ľ�����Ϣ
			p->changeStartAddress(t->getStartAddress());
			//���ı�
			t->changeLength(t->getLength() - p->getsize());
			t->changeStartAddress(t->getStartAddress() + p->getsize());
		}
	}
	//���Ӧ�㷨
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
			//���Ľ�����Ϣ
			p->changeStartAddress(t->getStartAddress());
			//���ı�
			t->changeLength(t->getLength() - p->getsize());
			t->changeStartAddress(t->getStartAddress() + p->getsize());
		}
	}
	//ѭ���״���Ӧ�㷨
	void updateByNF(Process* p) {
		//��һ�η��� temp_faΪ��
		if (temp_fa == NULL) {
			updateByFF(p);
			return;
		}
		else {
			//�����ϴη��������
			for (auto temp_t : table) {
				if (temp_t->getLength() > p->getsize() && temp_t->getStartAddress()>=temp_fa->getStartAddress()){
					temp_fa = temp_t;
					//���Ľ�����Ϣ
					p->changeStartAddress(temp_t->getStartAddress());
					//���ı�
					temp_t->changeLength(temp_t->getLength() - p->getsize());
					temp_t->changeStartAddress(temp_t->getStartAddress() + p->getsize());
					return;
				}
			}
			//�Ҳ����ٴ�ͷ��ʼ��
			updateByFF(p);
		}
	}
	
	static bool cmp(freeArea *fa1,freeArea* fa2) {
		return fa1->getStartAddress() < fa2->getStartAddress();
	}
	//�Կ��з������������ʹ�ÿ��з����ĸ�����ʼ��ַΪ�ӵ͵���
	void sortTable() {
		sort(begin(table), end(table),cmp);
	}
	//�ڽ������̺󣬸��¿��з�����
	void freetable(Process* p){
		sortTable();
		freeArea* start_fa=NULL;//�÷�������Ӧ�Խ������̷����ڿ��з���������
	    freeArea* end_fa=NULL;//�÷�������Ӧ�Խ������̷����ڿ��з���ǰ�����
		for (auto temp_fa : table) {
			//��ǰ�������ֹǡ�õ���ĳ�����з�������ַ
			if (temp_fa->getStartAddress() == p->getstartAddress() + p->getsize()) {
				end_fa = temp_fa;
			}
			//��ǰ�������ַǡ�õ���ĳ�����з�������ַ
			if (temp_fa->getStartAddress() + temp_fa->getLength() == p->getstartAddress()) {
				start_fa = temp_fa;
			}
		}
		//���¿���һ��������
		if (start_fa == NULL && end_fa == NULL) {
			freeArea* area = new freeArea(p->getstartAddress(),p->getsize(), 0);
			table.push_back(area);
			sortTable();

			temp_fa = area;
		}//������һ�������ĳ���
		else if(start_fa != NULL && end_fa == NULL) {
			start_fa->changeLength(start_fa->getLength()+p->getsize());

			temp_fa = start_fa;
		}//�ı���һ����������ַ�ͳ���
		else if (start_fa == NULL && end_fa != NULL) {
			end_fa->changeStartAddress(p->getstartAddress());
			end_fa->changeLength(end_fa->getLength() + p->getsize());

			temp_fa = end_fa;
		}//������һ�������ĳ��ȣ�ȥ����һ������
		else {
			start_fa->changeLength(start_fa->getLength() + p->getsize() + end_fa->getLength());
			
			temp_fa = start_fa;
			//ɾ����һ������
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

//���̹�����
class ProcessContainer {
    private:
		freeAreaTable freeareatable;
		vector<Process*> processList;
	public:

		//�������� startAddressΪ-1��ʾ��ϵͳ���䣬��Ϊ-1��ʾ��ʼ��
		Process*  createProcess(int pid,string processname,int size) {
			Process* p = new Process(pid,processname, size);
			return p;
		}

		//�����̼�����̶���
		void appendProcess(Process* p) {
			processList.push_back(p);
			//���ö�Ӧ�㷨�����ڴ����
			freeareatable.updateByNF(p);
			freeareatable.displayTable();
			cout << "������" << p->getprocessname() << "�����ɹ�" << endl;
			cout << "------------------------------" << endl;
		}

		//��������idɾ������
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
			cout << "ɾ��ʧ��";
		}

		void displayAll() {
			for (auto temp_p : processList) {
				temp_p->displayProcess();
			}
		}
};


int main() {
	ProcessContainer pcontainer;
	Process* p0 = pcontainer.createProcess(0, "����ϵͳ", 5);
	Process* p1 = pcontainer.createProcess(1, "��ҵ1", 5);
	Process* p3 = pcontainer.createProcess(3, "��ҵ3", 4);
	Process* p_temp = pcontainer.createProcess(-1, "��ʱ����", 12);//��ʱ���̣������޸Ŀ��з�����ʹ����Ҫ����ͬ
	Process* p2 = pcontainer.createProcess(2, "��ҵ2", 6);

	pcontainer.appendProcess(p0);
	pcontainer.appendProcess(p1);
	pcontainer.appendProcess(p3);
	pcontainer.appendProcess(p_temp);
	pcontainer.appendProcess(p2);
	pcontainer.popProcess(-1);
	cout << "���з�����ʼ���ɹ�"<<endl;

	Process* p4 = pcontainer.createProcess(4, "��ҵ4", 6);
	pcontainer.appendProcess(p4);
	pcontainer.popProcess(3);
	pcontainer.popProcess(2);
}