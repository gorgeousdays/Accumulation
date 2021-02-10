#include <stdc++.h>
using namespace std;

class expression {//表达式类
public:
	double coefficient;//x的系数
	double power_index;//x的指数
public:
	expression(double _x = 0.0, double _y = 0.0) {
		coefficient = _x;
		power_index = _y;
	}//类的构造函数 默认值为0
	friend ostream& operator << (ostream&, expression&); //重载输出流 用于表达式的输出
};

ostream& operator << (ostream& out, expression& l) {
	double a = l.coefficient;
	double b = l.power_index;
	if (!b) return out << a;//如果系数为1 指数为0  直接输出1
	if (a != 1 && a != -1) out << a;//如果系数不为1 那么输出系数 否则就不输出
	else if (a == -1) out << "-";//如果系数为-1 输出一个-号即可
	if (b != 0 && b != 1) out << "x^"; // 如果指数不为0 并且指数不为1 输出x^
	else if (b == 1) out << "x";//当指数为1的时候 表达式中的指数省略
	if (b != 1 && b > 0) out << b;//当指数不为1的时候 指数不可以省略
	else if (b < 0) out << "(" << b << ")";//当指数为负数
	return out;
}


class node { //节点类 
public:
	expression value; //值是表达式类型的
	node* next;//下一个节点
	node* pre;//前一个节点
	node(expression _value, node* _pre = NULL, node* _next = NULL) {
		value = _value;
		pre = _pre;
		next = _next;
	}//节点类的构造函数
	node() {//节点类的默认构造函数
		next = NULL;
		pre = NULL;
	}
};

class List {//双向链表类
private:
	node* head;//头节点
	int size = 0;//保存双向链表的大小
public:
	List() { //创建一个空链表
		head = new node();
		head->next = head;
		head->pre = head;
	}

	int length() {// 返回一个链表的长度
		return size;
	}

	bool isEmpty() {//判断链表是否为空
		return size == 0;
	}

	expression back() {//访问双向链表中的最后一个值
		if (isEmpty()) {//如果链表为空的话 给出提示
			cout << "empty list!" << endl;
			throw 0;
		}
		return head->pre->value;
	}

	expression front() {//访问双向链表中的一个值
		if (isEmpty()) {
			cout << "empty list!" << endl;
			throw 0;
		}
		return head->next->value;
	}

	void push_back(expression _value) {//向后插入节点
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

	void push_front(expression _value) {//向前插入节点
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

	void display() {//打印当前链表中的值 即打印表达式
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

	List add(List b) {//两个多项式相加的函数 操作类似于两个有序链表的合并
		List  res;
		node* p1 = head->next;
		node* p2 = b.head->next;
		while (p1 != head || p2 != b.head) { //当有一个表达式没有遍历完成的时候 执行
			if (p1 != head && p2 != b.head) { //两个都没有遍历完成
				if (p1->value.power_index > p2->value.power_index) {//如果当前访问的第一个表达式的指数比第二个大的话 讲第一个表达式压入结果链表
					res.push_back(p1->value);
					p1 = p1->next;
				}
				else if (p1->value.power_index == p2->value.power_index) { //如果相等的话 系数直接相加
					expression temp = expression(p1->value.coefficient + p2->value.coefficient, p1->value.power_index);
					res.push_back(temp);
					p1 = p1->next;
					p2 = p2->next;
				}
				else if (p1->value.power_index < p2->value.power_index) { //与第一种情况的相反的情况
					res.push_back(p2->value);
					p2 = p2->next;
				}
			}
			else if (p1 != head) {//如果第一个表达式还没有遍历完成
				res.push_back(p1->value);
				p1 = p1->next;
			}
			else {//如果第二个表达式还没有遍历完成
				res.push_back(p2->value);
				p2 = p2->next;
			}
		}
		return res;
	}
};

List phaser(string _in) {//解析输入的表达式 返回一个结果表达式
	List res;
	for (int i = 0; i < _in.length();) {
		string temp1 = "";
		string temp2 = "";
		if (_in[i] == '-') temp1 = '-', i++;//如果当前读到的字符为“-”，说明是负系数
		while (i < _in.length() && _in[i] != 'x' && _in[i] != '+' && _in[i] != '-') {
			temp1 += _in[i];
			i++;
		}
		//cout << temp1 << endl;
		if (_in[i] == '+' || _in[i] == '-') { //处理常数项
			temp2 = "0";
			res.push_back(expression(stod(temp1), stod(temp2)));
			//i += 1;
			continue;
		}
		if (temp1 == "") temp1 = "1";//如果系数为空 说明当前访问的字符串是一个系数为1的表达式
		else if (temp1 == "-") temp1 = "-1"; //如果系数为-1
		if (i >= _in.length()) { //表明常数项为最后一项 指数为0
			temp2 = "0"; 
			res.push_back(expression(stod(temp1), stod(temp2)));
			break;
		} //如果没有找到x 说明当前访问的字符串中是一个常数
		if (_in[i + 1] == '^') i += 2;//一般的情况 
		else if (_in[i + 1] == '+') {//指数为1的情况
			i += 2;
			temp2 = "1";
			res.push_back(expression(stod(temp1), stod(temp2)));
			//cout << temp2 << endl;
			expression a = res.back();
			//cout << a << endl;
			continue;
		}
		//cout << temp1 << endl;
		if (_in[i] == '-') temp2 = "-", i++;//指数为负数的情况
		while (i < _in.length() && isdigit(_in[i])) {
			temp2 += _in[i];
			i++;
		}
		if (temp2 == "") temp2 = "1";//说明指数为1
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
	cout << "请输入表达式1:\n";
	cin >> s;
	List l = phaser(s);
	//l.display();
	cout << "请输入表达式2:\n";
	cin >> s;
	List l2 = phaser(s);
	//l2.display();
	l = l.add(l2);
	cout << "多项式相加的结果:\n";
	l.display();
	return 0;
}
