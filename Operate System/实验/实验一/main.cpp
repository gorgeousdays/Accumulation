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
        cout << "��������ʧ��";
    }
    Sleep(1000);
    int x;
    while (true) {
        cout << "������Ҫѡ��Ĳ�����\n0:���ٽ���\n1:�˳�\n";
        cin >> x;
        switch (x) {
        case 0:
            if (TerminateProcess(pi.hProcess, 0))
                cout << "���ٽ��̳ɹ�" << endl;
            else {
                cout << "����ʧ��" << endl;
            }
            break;
        case 1:
            exit(0);
        default:
            cout << "�޸�ѡ��������ѡ��" << endl;
        }

    }
}