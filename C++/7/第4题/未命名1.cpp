#include<iostream>
#include<fstream>
#include<algorithm> 
using namespace std;
void f1()
{
    int a[10];
    ofstream outfile1("f1.dat"),outfile2("f2.dat"); 
    if(!outfile1)
    {
        cerr << "open f1.dat error!" << endl;
        exit(1);
    }
    if(!outfile2)
    {
        cerr << "open f2.dat error!" << endl;
        exit(1);
    }
    cout << "输入10个数据到f1" << endl;
    for (int i=0;i<10;i++)             
    {
        cin >> a[i];
        outfile1 << a[i] << " ";
    }
    cout << "输入10个数据到f2" << endl;
    for (int i=0;i<10;i++)              
    {
        cin >> a[i];
        outfile2 << a[i] << " ";
    }
    outfile1.close();
    outfile2.close();
}
void f2()
{
    ifstream infile("f1.dat");      
    if(!infile)
    {
        cerr << "open f1.dat error!" << endl;
        exit(1);
    }
    ofstream outfile("f2.dat",ios::app);        
    if (!outfile)
    {
        cerr << "open f2.dat error!" << endl;
        exit(1);
    }
    int t;
    for (int i=0;i<10;i++)
    {
        infile >> t;       
        outfile << t << " ";  
    }
    infile.close();
    outfile.close();
}
void f3()
{
    ifstream infile("f2.dat");
    if(!infile)
    {
        cerr << "open f2.dat error!" << endl;
        exit(1);
    }
    int a[20];
    int i,j,t;
    for (i=0;i<20;i++)
        infile >> a[i];
    sort(a,a+20);
    infile.close();
    ofstream outfile("f2.dat",ios::out);
    if(!outfile)
    {
        cerr << "open f2.dat error!" << endl;
        exit(1);
    }
    for (i=0;i<20;i++)
    {
        outfile << a[i] << " ";
        cout << a[i] << " ";
    }
    cout << endl;
    outfile.close();
}
int main()
{
    f1();
    f2();
    f3();
} 
