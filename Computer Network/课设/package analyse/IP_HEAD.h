#include <winsock2.h>
class IP_HEAD       //IP�ײ�
{
public:
	BYTE ver_hlen;      //IPЭ��汾��IP�ײ����ȡ���4λΪ�汾����4λΪ�ײ��ĳ���(��λΪ4bytes)
	BYTE byTOS;         //��������
	WORD wPacketLen;    //IP���ܳ��ȡ������ײ�����λΪbyte��
	WORD wSequence;     //��ʶ��һ��ÿ��IP������ŵ�����
	union
	{
		WORD Flags;     //��־
		WORD FragOf;    //�ֶ�ƫ��
	};
	BYTE byTTL;         //����ʱ�� 
	BYTE byProtocolType; //Э�����ͣ���PROTOCOL_TYPE����
	WORD wHeadCheckSum;   //IP�ײ�У��
	DWORD dwIPSrc;        //Դ��ַ
	DWORD dwIPDes;        //Ŀ�ĵ�ַ
	BYTE Options;         //ѡ��
};
