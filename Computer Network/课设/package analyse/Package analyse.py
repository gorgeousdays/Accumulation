#通过scapy来获取本机对应网卡的IP报文
from scapy.all import *
import time
a = []
def pack_callback(packet):
    try:
        if (packet[6].name == 'IP'):
            temp = []
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.version)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.ihl)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.tos)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.len)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.id)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.flags)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.frag)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.ttl)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.proto)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.chksum)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.src)
            temp.append(packet[0].payload.payload.payload.payload.payload.payload.dst)
            a.append(temp)
            print(temp)
    except:pass
    
filterstr="" 
#关于sniff的prn参数  指定回调函数，每当一个符合filter的报文被探测到时，就会执行回调函数
#iface参数 用来指定要在哪个网络接口上进行抓包 如若不指定即所有网络接口
# count指定最多嗅探多少个报文（是指符合filter条件的报文，而非所有报文）
sniff(filter=filterstr,prn=pack_callback, iface=' ', count=0)