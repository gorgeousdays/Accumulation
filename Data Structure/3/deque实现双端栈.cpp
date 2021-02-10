#include<iostream> 
#include<deque>
using namespace std; 

void display(deque<int> d, int num){
	int i = num;
	cout<<"ͷ��ջ";
	while (i--)
		cout<<d[i]<<' ';
	cout<<endl;
	i=num; 
	cout<<"β��ջ"; 
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
	cout<<"����:0.�˳����� 1.ͷ������ 2.β������ 3.ͷ��ɾ�� 4.β��ɾ�� 5.��ӡջ\n"; 
	while(true){
		cout<<"��������Ĳ���";   
		cin>>c;
		switch(c){    	
			case 1 :cout<<"����Ҫ����Ԫ��!";     
					cin>>temp;    
					d.push_front(temp);
					num++;
					break;
			case 2:cout<<"����Ҫ����Ԫ��!";    
					cin>>temp;
					d.push_back(temp);
					break;
			case 3:if (num > 0){
						num--; 
						d.pop_front();
						cout<<"ɾ���ɹ�!";
					}
					else	
						cout<<"ͷ��ջΪ��!";  	
					break;
			case 4 :if (d.size()-num > 0){
						d.pop_back();
						cout<<"ɾ���ɹ�!";
					}			
				 	else
				 		cout<<"β��ջΪ��!";
					break;
			case 5:display(d, num);
					break;
			case 0 :cout<<"�������н�����"; 
			        return 0;
			default:cout<<"����������������룡"<<endl;
		}    
	}  	
}

int main() {
	deque<int> D;
	choose(D);
	return 0;	
}
