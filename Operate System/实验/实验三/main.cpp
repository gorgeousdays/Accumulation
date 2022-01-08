#include<iostream>
#include<vector>
#define n 4//进程总数
#define m 3//资源类数
using namespace std;

class state{
    private:
	    vector<int> resource;//总资源数
	    vector<int> available;//剩余可用资源数
	    vector<vector<int> > claim;//各个进程需要的总资源数
	    vector<vector<int> > alloc;//各个进程现在已获得的各类资源数
		vector<vector<int> > need;//各个进程还需要的资源数
		string stateMessage="";//存储当前状态信息，错误信息等

    public:

		//构造函数，在创建状态时初始化各常量
		state(vector<int> _resource,vector<vector<int> > _claim, vector<vector<int> > _alloc) {
			this->resource = _resource;
			this->claim = _claim;
			this->alloc = _alloc;	



			//计算剩余可用资源
			this->available.resize(m);
			for (int i = 0; i < m; i++) {
				int sum = 0;
				for (int j = 0; j < n; j++) {
					sum += this->alloc[j][i];
				}
				this->available[i] = this->resource[i] - sum;
			}

			//计算还需多少资源
			this->need.resize(n);
			for (int i = 0; i < n; ++i) {
				this->need[i].resize(m);
			}
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					this->need[i][j] = this->claim[i][j] - this->alloc[i][j];
				}
			}
			
		}

		//打印信息
		void printAllData() {
			cout << "---------------------\n";
			cout << "resource:";
			for (int i = 0; i < m; i++) {
				cout << this->resource[i] << " ";
			}
			cout << "\navailable:";
			for (int i = 0; i < m; i++) {
				cout << this->available[i] << " ";
			}
			cout << "\nclaim:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << this->claim[i][j]<<" ";
				}
				cout << "\n";
			}
			cout << "alloc:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << this->alloc[i][j] << " ";
				}
				cout << "\n";
			}
			cout << "need:\n";
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m; j++) {
					cout << this->need[i][j] << " ";
				}
				cout << "\n";
			}
			cout << "stateMessgae:" << this->stateMessage;
			cout << "\n---------------------\n";
		}

		//寻找满足条件的进程，成功找到则返回进程编号，不然返回-1
		int findSafeProc(vector<bool> rest,vector<int> currentavail) {
			for (int i = 0; i < n; i++) {
				if (rest[i] == false) {
					int flag = 1;
					//要求各类资源都满足要求
					for (int j = 0; j < m; j++) {
						if (this->need[i][j] > currentavail[j]) {
							flag = 0;
						}
					}
					if (flag == 1) {
						return i;
					}
				}
			}
			return -1;
		}

		//判断分配
		bool safe(){
			vector<int> currentavail = this->available;
			vector<bool> rest(n, false);
			vector<int> safeSequence;


			for (int i = 0; i < n; i++) {
				int ret = findSafeProc(rest, currentavail);
				if (ret == -1) {
					cout << "\n此状态不安全\n";
					return false;
				}
				//如果找到满足要求的资源则回收
				else {
					rest[ret] = true;
					safeSequence.push_back(ret);
					for (int j = 0; j < m; j++) {
						currentavail[j] += this->alloc[ret][j];
					}
				}
			}
			//判断是否全部进程都已成功分配
			for (int i = 0; i < n; i++) {
				if (rest[i] == false) {
					cout << "此状态不安全\n";
					return false;
				}
			}
			cout << "此状态安全\n";
			cout << "当前分配队列为:";
			for (int i = 0; i < safeSequence.size(); i++) {
				cout << safeSequence[i]<<" ";
			}
			cout << "\n\n";
			return true;
		}

		//动态申请资源
		void  resourceAlloc(int requestProcessIndex, int requestNum[m]) {
			int pid = requestProcessIndex;
			for (int i = 0; i < m; i++) {
				if (this->alloc[pid][i] + requestNum[i] > this->claim[pid][i]) {
					this->stateMessage = "Error!Total request is more than claim";
					return;
				}
				if (requestNum[i] > this->available[i]) {
					this->stateMessage = "Suspend process";
					return;
				}
			}
			//define newstate

			for (int i = 0; i < m; i++) {
				this->alloc[pid][i] += requestNum[i];
				this->available[i] -= requestNum[i];
				this->need[pid][i] -= requestNum[i];
			}

			if (safe()) {
				this->stateMessage = "Carry out allocation";
				return;
			}
			else {
				//restore
				for (int i = 0; i < m; i++) {
					this->alloc[pid][i] -= requestNum[i];
					this->available[i] += requestNum[i];
					this->need[pid][i] += requestNum[i];
				}
				this->stateMessage = "Restore;Suspend process";
				return;
			}
	    }
};

state initState() {
	vector<int> _resource = { 9,3,6};
	vector<vector<int> > _claim = { {3,2,2},{ 6,1,3},{3,1,4},{4,2,2} };
	vector<vector<int> > _alloc = { {1,0,0},{ 6,1,2},{2,1,1},{0,0,2} };
	state S(_resource,_claim,_alloc);
	return S;
}

int main() {
	state S = initState();
	int requestProcessIndex = 1;
	int requestNum[m] = { 0,0,1};

	cout << "分配前:\n";
	S.printAllData();
	S.resourceAlloc(requestProcessIndex, requestNum);
	cout << "分配后:\n";
	S.printAllData();

	return 0;
}