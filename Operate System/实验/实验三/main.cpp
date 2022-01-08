#include<iostream>
#include<vector>
#define n 4//��������
#define m 3//��Դ����
using namespace std;

class state{
    private:
	    vector<int> resource;//����Դ��
	    vector<int> available;//ʣ�������Դ��
	    vector<vector<int> > claim;//����������Ҫ������Դ��
	    vector<vector<int> > alloc;//�������������ѻ�õĸ�����Դ��
		vector<vector<int> > need;//�������̻���Ҫ����Դ��
		string stateMessage="";//�洢��ǰ״̬��Ϣ��������Ϣ��

    public:

		//���캯�����ڴ���״̬ʱ��ʼ��������
		state(vector<int> _resource,vector<vector<int> > _claim, vector<vector<int> > _alloc) {
			this->resource = _resource;
			this->claim = _claim;
			this->alloc = _alloc;	



			//����ʣ�������Դ
			this->available.resize(m);
			for (int i = 0; i < m; i++) {
				int sum = 0;
				for (int j = 0; j < n; j++) {
					sum += this->alloc[j][i];
				}
				this->available[i] = this->resource[i] - sum;
			}

			//���㻹�������Դ
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

		//��ӡ��Ϣ
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

		//Ѱ�����������Ľ��̣��ɹ��ҵ��򷵻ؽ��̱�ţ���Ȼ����-1
		int findSafeProc(vector<bool> rest,vector<int> currentavail) {
			for (int i = 0; i < n; i++) {
				if (rest[i] == false) {
					int flag = 1;
					//Ҫ�������Դ������Ҫ��
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

		//�жϷ���
		bool safe(){
			vector<int> currentavail = this->available;
			vector<bool> rest(n, false);
			vector<int> safeSequence;


			for (int i = 0; i < n; i++) {
				int ret = findSafeProc(rest, currentavail);
				if (ret == -1) {
					cout << "\n��״̬����ȫ\n";
					return false;
				}
				//����ҵ�����Ҫ�����Դ�����
				else {
					rest[ret] = true;
					safeSequence.push_back(ret);
					for (int j = 0; j < m; j++) {
						currentavail[j] += this->alloc[ret][j];
					}
				}
			}
			//�ж��Ƿ�ȫ�����̶��ѳɹ�����
			for (int i = 0; i < n; i++) {
				if (rest[i] == false) {
					cout << "��״̬����ȫ\n";
					return false;
				}
			}
			cout << "��״̬��ȫ\n";
			cout << "��ǰ�������Ϊ:";
			for (int i = 0; i < safeSequence.size(); i++) {
				cout << safeSequence[i]<<" ";
			}
			cout << "\n\n";
			return true;
		}

		//��̬������Դ
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

	cout << "����ǰ:\n";
	S.printAllData();
	S.resourceAlloc(requestProcessIndex, requestNum);
	cout << "�����:\n";
	S.printAllData();

	return 0;
}