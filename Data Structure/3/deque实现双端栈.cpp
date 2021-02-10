#include<iostream> 
#include<deque>
using namespace std; 

void display(deque<int> d, int num){
	int i = num;
	cout<<"头部栈";
	while (i--)
		cout<<d[i]<<' ';
	cout<<endl;
	i=num; 
	cout<<"尾部栈"; 
	while (i < d.size()){
		cout<<d[i]<<' ';
		i++;
	}
	cout<<endl;
}

int choose(deque<int> d){ 
	int temp;   
	int c; 
	int num = 0;    
	cout<<"输入:0.退出程序 1.头部插入 2.尾部插入 3.头部删除 4.尾部删除 5.打印栈\n"; 
	while(true){
		cout<<"请输入你的操作";   
		cin>>c;
		switch(c){    	
			case 1 :cout<<"输入要插入元素!";     
					cin>>temp;    
					d.push_front(temp);
					num++;
					break;
			case 2:cout<<"输入要插入元素!";    
					cin>>temp;
					d.push_back(temp);
					break;
			case 3:if (num > 0){
						num--; 
						d.pop_front();
						cout<<"删除成功!";
					}
					else	
						cout<<"头部栈为空!";  	
					break;
			case 4 :if (d.size()-num > 0){
						d.pop_back();
						cout<<"删除成功!";
					}			
				 	else
				 		cout<<"尾部栈为空!";
					break;
			case 5:display(d, num);
					break;
			case 0 :cout<<"程序运行结束！"; 
			        return 0;
			default:cout<<"输入错误，请重新输入！"<<endl;
		}    
	}  	
}

int main() {
	deque<int> D;
	choose(D);
	return 0;	
}
