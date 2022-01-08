#include<iostream>
#include<windows.h>
using namespace std;
void  main(VOID) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si,0,sizeof(si));
    si.cb = sizeof(si);
    char path[1000] = "D:\\games\\steam\\Steam.exe";
    if (!CreateProcess(NULL,path, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)){
        cout << "创建进程失败";
    }
    Sleep(1000);
    int x;
    while (true) {
        cout << "请输入要选择的操作：\n0:销毁进程\n1:退出\n";
        cin >> x;
        switch (x) {
        case 0:
            if (TerminateProcess(pi.hProcess, 0))
                cout << "销毁进程成功" << endl;
            else {
                cout << "销毁失败" << endl;
            }
            break;
        case 1:
            exit(0);
        default:
            cout << "无该选择，请重新选择" << endl;
        }

    }
}