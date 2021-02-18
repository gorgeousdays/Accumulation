#include <winsock2.h>
class IP_HEAD       //IP首部
{
public:
	BYTE ver_hlen;      //IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度(单位为4bytes)
	BYTE byTOS;         //服务类型
	WORD wPacketLen;    //IP包总长度。包括首部，单位为byte。
	WORD wSequence;     //标识，一般每个IP包的序号递增。
	union
	{
		WORD Flags;     //标志
		WORD FragOf;    //分段偏移
	};
	BYTE byTTL;         //生存时间 
	BYTE byProtocolType; //协议类型，见PROTOCOL_TYPE定义
	WORD wHeadCheckSum;   //IP首部校验
	DWORD dwIPSrc;        //源地址
	DWORD dwIPDes;        //目的地址
	BYTE Options;         //选项
};
