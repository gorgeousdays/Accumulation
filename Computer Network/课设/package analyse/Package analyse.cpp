#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <mstcpip.h>
#include "IP_HEAD.h"
#pragma comment(lib,"Ws2_32.lib")
using namespace std;
int number;
int DecodeIP(char* buf, int len)
{
	int n = len;
	if (n >= sizeof(IP_HEAD))
	{
		IP_HEAD iphead;
		iphead = *(IP_HEAD*)buf;
		cout << "第 " << number++ << " 个IP数据包信息：" << endl;
		cout << "协议版本:" << (iphead.ver_hlen >> 4) << endl;
		cout << "总长度:" << ntohs(iphead.wPacketLen) << endl; //网络字节序转为主机字节序
		cout << "标志位:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;
		cout << "片偏移:" << (iphead.FragOf & 0x1fff) << endl;
		cout << "协议:" << int(iphead.byProtocolType) << endl;
		cout << "源地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;
		cout << "目的地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;
		cout << "---------------------------------------------------" << endl << endl;
	}
	return 0;
}
void AutoWSACleanup()
{
	::WSACleanup();  // 终止Winsock的使用
}
int main()
{
	int n;
	WSADATA wd;  //一种数据结构,这个结构被用来存储被WSAStartup函数调用后返回的Windows Sockets数据,它包含Winsock.dll执行的数据。
	n = WSAStartup(MAKEWORD(2, 2), &wd);  //返回winsock服务初始化是否成功，若返回1则输出错误
	if (n)
	{
		cout << "WSAStartup函数错误！" << endl;
		return -1;
	}
	atexit(AutoWSACleanup);
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);  //创建SOCKET
	if (sock == INVALID_SOCKET)
	{
		cerr << WSAGetLastError();
		return 0;
	}
	//获取本机地址
	char  name[128];
	if (-1 == gethostname(name, sizeof(name)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	struct hostent* pHostent;
	pHostent = gethostbyname(name);
	//绑定本地地址到SOCKET
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP
	addr.sin_port = 8888; //端口，IP层端口可随意填
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&addr, sizeof(addr)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//设置该SOCKET为接收所有流经绑定的IP的网卡的所有数据，包括接收和发送的数据包
	u_long sioarg = 1;
	DWORD wt = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//我们只需要接收数据，因此设置为阻塞IO，使用最简单的IO模型
	u_long bioarg = 0;
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//开始接收数据
	//因为前面已经设置为阻塞IO，recv在接收到数据前不会返回。
	number = 1;
	char buf[65535];
	int len = 0;
	do
	{
		len = recv(sock, buf, sizeof(buf), 0);
		if (len > 0)
		{
			DecodeIP(buf, len);
		}
	} while (len > 0);
	closesocket(sock);
	return 0;
}
