#include<iostream>
using namespace std;

#define MAXQSIZE 5	

template <typename T>
class bqueue
{
	public:
		bqueue():qfront(0), qback(0), count(0){};
		void push(const T& item);
		void maxpop();			
		void minpop();
		void maxfront();
		void minfront();
		
		int size() const;		// return the size of the queue
		bool empty() const;
		bool full() const;		
		// display function only use for experiment.
		void display();

    private:
		T queueArray[MAXQSIZE];
		// qfront and qback are two subscribe of the original array.
		// qfront points to the first active element.
		// qback points to the next position of the last element.
		int qfront, qback;
		// Calculate the number of elements in the queue.		
		int count;		
};					

// Push the element into the queue.
template <typename T>
void bqueue<T>::push(const T& item)
{	
	queueArray[qback] = item;
	// For sometimes qback+1 may be lager than the maxsize of the queue,
	// so use mode operation to ensure the number of qback is safe.
	qback = (qback+1) % MAXQSIZE;
	count++;
}

// Pop out the largest element in the queue.
template <typename T>
void bqueue<T>::maxpop()
{
	// When there is no element in the queue, go into the judgement.
	if (empty()) {
		cout<<"Error! There is no element in the queue!"<<endl;
		return;
	}		
	// Initially let the head element be the largest element.
	T max = queueArray[qfront];
	int maxNum = qfront, cycle = count;
	// serch the whole queue.
	while(cycle--){
		int i = qfront+(count-cycle)-1;
		// If find an element larger than the max stored, change max.
		// maxNum is a subscript to show the position of the max element.
		if (max<queueArray[i%MAXQSIZE]){
			max = queueArray[i];		
			maxNum = i % MAXQSIZE;
		}		
	}
	
	// Move one step backward.
	// Let the elements before the max element move one step backward
	// to squeeze the max element out.
	// Use mode operation to ensure all the elements are still in the queue.
	for (int i=maxNum+(qfront>maxNum? MAXQSIZE:0); i>qfront; i--){
		queueArray[i%MAXQSIZE] = queueArray[(i-1)%MAXQSIZE];	
	} 
	
	// move the qfront one step backward, point to the new head.
	qfront = (qfront+1) % MAXQSIZE;
	count--;
	cout<<"pop the largest successfully!"<<endl;	// suggest message
}

// Pop out the smallest element in the queue.
template <typename T>
void bqueue<T>::minpop()
{
	// When there is no element in the queue, go into the judgement.
	if (empty()){
		cout<<"Error! There is no element in the queue!"<<endl;
		return;
	}
	// Initially let the head element be the smallest element.
	T min = queueArray[qfront];
	int minNum = qfront, cycle = count;
	// serch the whole queue.
	while(cycle--){
		int i = qfront+(count-cycle)-1;
		// If find an element smaller than the min stored, change min.
		// minNum is a subscript to show the position of the min element.
		if (min>queueArray[i%MAXQSIZE]){
			min = queueArray[i];			
			minNum = i % MAXQSIZE;
		}		
	}
	
	// Move one step backward.
	// Let the elements before the min element move one step backward
	// to squeeze the min element out.
	// Use mode operation to ensure all the elements are still in the queue.
	for (int i=minNum+(qfront>minNum? MAXQSIZE:0); i>qfront; i--){
		queueArray[i%MAXQSIZE] = queueArray[(i-1)%MAXQSIZE];	
	} 
	
	// move the qfront one step backward, point to the new head.
	qfront = (qfront+1) % MAXQSIZE;
	count--;
	cout<<"pop the smallest successfully!"<<endl;	// suggest message
}

// Show the largest element in the queue.
template <typename T>
void bqueue<T>::maxfront()
{
	// Initially let the head element be the largest element.
	T max = queueArray[qfront];
	int cycle = count-1;
	while(cycle--){							// serch the whole queue.
		int i = qfront+(count-cycle)-1;
		// If find an element larger than the max stored, change max.
		if (max < queueArray[i%MAXQSIZE]){
			max = queueArray[i];
		}		
	}
	cout<<max;
}

// Show the smallest element in the queue.
template <typename T>
void bqueue<T>::minfront()
{
	// Initially let the head element be the smallest element.
	T min = queueArray[qfront];
	int cycle = count-1;
	while(cycle--){							// serch the whole queue.
		int i = qfront+(count-cycle)-1;
		// If find an element smaller than the min stored, change min.
		if (min > queueArray[i%MAXQSIZE]){
			min = queueArray[i];
		}		
	}
	cout<<min;
}

// Return the number of elements in the queue.
template <typename T>
int bqueue<T>::size() const
{
	return count;
}

// Judge wether the queue is empty.
template <typename T>
bool bqueue<T>::empty() const
{
	return count == 0;
}

// Judge wether the queue is full.
template <typename T>
bool bqueue<T>::full() const
{
	return count == MAXQSIZE;
}

// Display all the elements in the queue.
template <typename T>
void bqueue<T>::display()
{
	for (int i=qfront; i<(qback+(qfront>=qback? MAXQSIZE:0)); i++){
		cout<<queueArray[i%MAXQSIZE]<<' ';
	} 
	cout<<endl;
}
	

int main ()
{
	bqueue<int> Q;
	char option;
	cout<<"Option: 1-push into the queue,  2-show the size of the queue,\n"
	 	<<"        3-show the min front,   4-pop the smallest from the queue,\n"
	  	<<"        5-show the max front,   6-pop the largest from the queue,\n"
 		<<"        #-quit.\n";
	while(cin>>option && option!='#'){
		int temp;
		switch(option)
		{
			// Judge wether the queue is full; if not, push in the element.
			case'1':if (!Q.full()){
						cout<<"insert:";
						cin>>temp;
						Q.push(temp);
					}
					else
						cout<<"the queue is full!"<<endl;
					break;
			// Show the size of the queue.
			case'2':cout<<"The size: "<<Q.size()<<endl;
					break; 
			// Show the smallest element in the queue.
			case'3':if (Q.empty())			// Firstly, judge wether the queue is empty.
						cout<<"error! There is no element in the queue!"<<endl;
					else{
						cout << "The smallest element: ";
						Q.minfront();
						cout << endl;
					}
					break;
			// Pop out the smallest element in the queue.
			case'4':Q.minpop();
					break;
			// Show the largest element in the queue.
			case'5':if (Q.empty())			// Firstly, judge wether the queue is empty.
						cout<<"error! There is no element in the queue!"<<endl;
					else{
						cout << "The largest element: ";
						Q.maxfront();
						cout << endl;
					}
					break;
			// Pop out the largest element in the queue.
			case'6':Q.maxpop();
					break;
			default:cout<<"Error input! Please try again."<<endl;
		}
	}	
	return 0;	
} 

