#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

//ְ��
struct Person
{
    int m_Id;
    string m_Name;
    int m_Age;
    int m_Wage;

    Person(int i, string n, int a, int w): m_Id(i), m_Name(n), m_Age(a), m_Wage(w) { }
    void PrintInfo()
    {
        cout << "===================" << endl;
        cout << "����:\t" << this -> m_Id << endl;
        cout << "����:\t" << this -> m_Name << endl;
        cout << "����:\t" << this -> m_Age << endl;
        cout << "����:\t" << this -> m_Wage << endl;
        cout << "===================" << endl;
    }
};

Person *p[3] =
{
    new Person(101, "С��", 23, 3100),
    new Person(102, "�л�", 41, 6600),
    new Person(105, "���", 55, 7000),

};

int main()
{
    //��5�����ݰ�ID��������
    int i, j;
    Person *temp;
    for(i = 0; i < 3; i++)
    {
        for(j = i + 1; j < 3; j++)
        {
            if(p[i] -> m_Id > p[j] -> m_Id)
            {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    //���ź�������ݴ��뵽�ļ�f.dat
    ofstream outfile1("f.dat", ios :: out);
    if(!outfile1)
    {
        cerr << "f.dat �򿪴���" << endl;
        exit(1);
    }
    for(i = 0; i < 3; i++)
    {
        outfile1 << p[i] -> m_Id << " "
                 << p[i] -> m_Name << " "
                 << p[i] -> m_Age << " "
                 << p[i] -> m_Wage << endl;
    }
    outfile1.close();

    //��д������ְ����Ϣ
    //ʾ������ 108 Titus 40 4000 109 Tulius 35 5000
    cout << "������2��ְ����Ϣ��";
    ofstream outfile2("f.dat", ios :: out | ios :: app);
    if(!outfile2)
    {
        cerr << "f.dat �򿪴���" << endl;
        exit(1);
    }
    temp = new Person(0, "", 0, 0);
    cin >> temp -> m_Id >> temp -> m_Name >> temp -> m_Age >> temp -> m_Wage;
    outfile2 << temp -> m_Id << " "
             << temp -> m_Name << " "
             << temp -> m_Age << " "
             << temp -> m_Wage << endl;
    cin >> temp -> m_Id >> temp -> m_Name >> temp -> m_Age >> temp -> m_Wage;
    outfile2 << temp -> m_Id << " "
             << temp -> m_Name << " "
             << temp -> m_Age << " "
             << temp -> m_Wage << endl;
    outfile2.close();

    //����ļ��е�ȫ��ְ������
    ifstream infile1("f.dat", ios :: in);
    if(!infile1)
    {
        cerr << "f.dat �򿪴���" << endl;
        exit(1);
    }
    for(i = 0; i < 5; i++)
    {
        infile1 >> temp -> m_Id >> temp -> m_Name >> temp -> m_Age >> temp -> m_Wage;
        temp -> PrintInfo();
    }
    infile1.close();

    //����һ��ID����Ƿ����
    int id;
    cout << "������һ�����룺";
    cin >> id;
    bool isFound = false;
    ifstream infile2("f.dat", ios :: in);
    if(!infile2)
    {
        cerr << "f.dat �򿪴���" << endl;
        exit(1);
    }
    for(i = 0; i < 5; i++)
    {
        infile2 >> temp -> m_Id >> temp -> m_Name >> temp -> m_Age >> temp -> m_Wage;
        if(temp -> m_Id == id)
        {
            temp -> PrintInfo();
            isFound = true;
            break;
        }
    }
    if(!isFound)
    {
        cerr << "û���ҵ������" << endl;
    }
    infile2.close();

    return 0;
}

