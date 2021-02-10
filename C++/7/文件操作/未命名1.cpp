#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

//职工
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
        cout << "号码:\t" << this -> m_Id << endl;
        cout << "名字:\t" << this -> m_Name << endl;
        cout << "年龄:\t" << this -> m_Age << endl;
        cout << "工资:\t" << this -> m_Wage << endl;
        cout << "===================" << endl;
    }
};

Person *p[3] =
{
    new Person(101, "小黄", 23, 3100),
    new Person(102, "中黄", 41, 6600),
    new Person(105, "大黄", 55, 7000),

};

int main()
{
    //对5组数据按ID进行排序
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

    //将排好序的数据存入到文件f.dat
    ofstream outfile1("f.dat", ios :: out);
    if(!outfile1)
    {
        cerr << "f.dat 打开错误" << endl;
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

    //再写入两个职工信息
    //示例输入 108 Titus 40 4000 109 Tulius 35 5000
    cout << "请输入2个职工信息：";
    ofstream outfile2("f.dat", ios :: out | ios :: app);
    if(!outfile2)
    {
        cerr << "f.dat 打开错误" << endl;
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

    //输出文件中的全部职工数据
    ifstream infile1("f.dat", ios :: in);
    if(!infile1)
    {
        cerr << "f.dat 打开错误" << endl;
        exit(1);
    }
    for(i = 0; i < 5; i++)
    {
        infile1 >> temp -> m_Id >> temp -> m_Name >> temp -> m_Age >> temp -> m_Wage;
        temp -> PrintInfo();
    }
    infile1.close();

    //输入一个ID检测是否存在
    int id;
    cout << "请输入一个号码：";
    cin >> id;
    bool isFound = false;
    ifstream infile2("f.dat", ios :: in);
    if(!infile2)
    {
        cerr << "f.dat 打开错误" << endl;
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
        cerr << "没有找到这个人" << endl;
    }
    infile2.close();

    return 0;
}

