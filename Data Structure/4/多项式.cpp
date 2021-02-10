#include <stdc++.h>
using namespace std;

class expression {//���ʽ��
public:
	double coefficient;//x��ϵ��
	double power_index;//x��ָ��
public:
	expression(double _x = 0.0, double _y = 0.0) {
		coefficient = _x;
		power_index = _y;
	}//��Ĺ��캯�� Ĭ��ֵΪ0
	friend ostream& operator << (ostream&, expression&); //��������� ���ڱ��ʽ�����
};

ostream& operator << (ostream& out, expression& l) {
	double a = l.coefficient;
	double b = l.power_index;
	if (!b) return out << a;//���ϵ��Ϊ1 ָ��Ϊ0  ֱ�����1
	if (a != 1 && a != -1) out << a;//���ϵ����Ϊ1 ��ô���ϵ�� ����Ͳ����
	else if (a == -1) out << "-";//���ϵ��Ϊ-1 ���һ��-�ż���
	if (b != 0 && b != 1) out << "x^"; // ���ָ����Ϊ0 ����ָ����Ϊ1 ���x^
	else if (b == 1) out << "x";//��ָ��Ϊ1��ʱ�� ���ʽ�е�ָ��ʡ��
	if (b != 1 && b > 0) out << b;//��ָ����Ϊ1��ʱ�� ָ��������ʡ��
	else if (b < 0) out << "(" << b << ")";//��ָ��Ϊ����
	return out;
}


class node { //�ڵ��� 
public:
	expression value; //ֵ�Ǳ��ʽ���͵�
	node* next;//��һ���ڵ�
	node* pre;//ǰһ���ڵ�
	node(expression _value, node* _pre = NULL, node* _next = NULL) {
		value = _value;
		pre = _pre;
		next = _next;
	}//�ڵ���Ĺ��캯��
	node() {//�ڵ����Ĭ�Ϲ��캯��
		next = NULL;
		pre = NULL;
	}
};

class List {//˫��������
private:
	node* head;//ͷ�ڵ�
	int size = 0;//����˫������Ĵ�С
public:
	List() { //����һ��������
		head = new node();
		head->next = head;
		head->pre = head;
	}

	int length() {// ����һ������ĳ���
		return size;
	}

	bool isEmpty() {//�ж������Ƿ�Ϊ��
		return size == 0;
	}

	expression back() {//����˫�������е����һ��ֵ
		if (isEmpty()) {//�������Ϊ�յĻ� ������ʾ
			cout << "empty list!" << endl;
			throw 0;
		}
		return head->pre->value;
	}

	expression front() {//����˫�������е�һ��ֵ
		if (isEmpty()) {
			cout << "empty list!" << endl;
			throw 0;
		}
		return head->next->value;
	}

	void push_back(expression _value) {//������ڵ�
		size++;
		if (isEmpty()) {
			head->next = new node(_value, head, head);
			head->pre = head;
		}
		else {
			head->pre->next = new node(_value, head->pre, head);
			head->pre = head->pre->next;
		}
	}

	void push_front(expression _value) {//��ǰ����ڵ�
		size++;
		if (isEmpty()) {
			head->next = new node(_value, head, head);
			head->pre = head;
		}
		else {
			head->next->pre = new node(_value, head, head->next);
			head->next = head->next->pre;
		}
	}

	void display() {//��ӡ��ǰ�����е�ֵ ����ӡ���ʽ
		node* p = head->next;
		int index = 1;
		cout << p->value;
		p = p->next;
		while (p != head) {
			
			if (p->value.coefficient > 0) cout << "+";
			else if (p->value.coefficient == 0) {
				p = p->next;
				continue;
			}
			cout << p->value;
			p = p->next;
		}
		cout << endl;
	}

	List add(List b) {//��������ʽ��ӵĺ��� ����������������������ĺϲ�
		List  res;
		node* p1 = head->next;
		node* p2 = b.head->next;
		while (p1 != head || p2 != b.head) { //����һ�����ʽû�б�����ɵ�ʱ�� ִ��
			if (p1 != head && p2 != b.head) { //������û�б������
				if (p1->value.power_index > p2->value.power_index) {//�����ǰ���ʵĵ�һ�����ʽ��ָ���ȵڶ�����Ļ� ����һ�����ʽѹ��������
					res.push_back(p1->value);
					p1 = p1->next;
				}
				else if (p1->value.power_index == p2->value.power_index) { //�����ȵĻ� ϵ��ֱ�����
					expression temp = expression(p1->value.coefficient + p2->value.coefficient, p1->value.power_index);
					res.push_back(temp);
					p1 = p1->next;
					p2 = p2->next;
				}
				else if (p1->value.power_index < p2->value.power_index) { //���һ��������෴�����
					res.push_back(p2->value);
					p2 = p2->next;
				}
			}
			else if (p1 != head) {//�����һ�����ʽ��û�б������
				res.push_back(p1->value);
				p1 = p1->next;
			}
			else {//����ڶ������ʽ��û�б������
				res.push_back(p2->value);
				p2 = p2->next;
			}
		}
		return res;
	}
};

List phaser(string _in) {//��������ı��ʽ ����һ��������ʽ
	List res;
	for (int i = 0; i < _in.length();) {
		string temp1 = "";
		string temp2 = "";
		if (_in[i] == '-') temp1 = '-', i++;//�����ǰ�������ַ�Ϊ��-����˵���Ǹ�ϵ��
		while (i < _in.length() && _in[i] != 'x' && _in[i] != '+' && _in[i] != '-') {
			temp1 += _in[i];
			i++;
		}
		//cout << temp1 << endl;
		if (_in[i] == '+' || _in[i] == '-') { //��������
			temp2 = "0";
			res.push_back(expression(stod(temp1), stod(temp2)));
			//i += 1;
			continue;
		}
		if (temp1 == "") temp1 = "1";//���ϵ��Ϊ�� ˵����ǰ���ʵ��ַ�����һ��ϵ��Ϊ1�ı��ʽ
		else if (temp1 == "-") temp1 = "-1"; //���ϵ��Ϊ-1
		if (i >= _in.length()) { //����������Ϊ���һ�� ָ��Ϊ0
			temp2 = "0"; 
			res.push_back(expression(stod(temp1), stod(temp2)));
			break;
		} //���û���ҵ�x ˵����ǰ���ʵ��ַ�������һ������
		if (_in[i + 1] == '^') i += 2;//һ������ 
		else if (_in[i + 1] == '+') {//ָ��Ϊ1�����
			i += 2;
			temp2 = "1";
			res.push_back(expression(stod(temp1), stod(temp2)));
			//cout << temp2 << endl;
			expression a = res.back();
			//cout << a << endl;
			continue;
		}
		//cout << temp1 << endl;
		if (_in[i] == '-') temp2 = "-", i++;//ָ��Ϊ���������
		while (i < _in.length() && isdigit(_in[i])) {
			temp2 += _in[i];
			i++;
		}
		if (temp2 == "") temp2 = "1";//˵��ָ��Ϊ1
		//cout << temp2 << endl;
		res.push_back(expression(stod(temp1), stod(temp2)));
		expression a = res.back();
		//cout << a << endl;
		if (_in[i] != '-') i++;
	}
	//res.display();
	return res;
}

int main() {
	string s;
	cout << "��������ʽ1:\n";
	cin >> s;
	List l = phaser(s);
	//l.display();
	cout << "��������ʽ2:\n";
	cin >> s;
	List l2 = phaser(s);
	//l2.display();
	l = l.add(l2);
	cout << "����ʽ��ӵĽ��:\n";
	l.display();
	return 0;
}
