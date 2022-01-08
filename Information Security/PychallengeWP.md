# PychallengeWP

## 0

```
http://www.pythonchallenge.com/pc/def/1.html
```

提示`2**38 is much much larger.`

尝试`2**38`返回`give the answer, not the question.`

尝试`238`返回`No... the 38 is a little bit above the 2...`

2**38即2的38次方...

```
http://www.pythonchallenge.com/pc/def/274877906944.html
```

## 1

凯撒移两位

```python
# 有y要循环
str="g fmnc wms bgblr rpylqjyrc gr zw fylb. rfyrq ufyr amknsrcpq ypc dmp. bmgle gr gl zw fylb gq glcddgagclr ylb rfyr'q ufw rfgq rcvr gq qm jmle. sqgle qrpgle.kyicrpylq() gq pcamkkclbcb. lmu ynnjw ml rfc spj."
res=""
change=2
for s in str:
    if s=='y' or s=='z':
        res+=chr(ord(s)-26+2)
    elif  'x'>=s>='a':
        res+=chr(ord(s)+2)
    else:
        res+=s
print(res)
# i hope you didnt translate it by hand. thats what computers are for. doing it in by hand is inefficient and that's why this text is so long. using string.maketrans() is recommended. now apply on the url.
# map->ocr
```

```
http://www.pythonchallenge.com/pc/def/ocr.html
```

## 2

查看源码`find rare characters in the mess below:`找乱码里的有效字符

```python
with open("test.txt", "r") as f:  # 打开文件
    data = f.read()  # 读取文件
res=""
for s in data:
    if 'a'<=s<='z' or 'A'<=s<='Z':
        res+=s
print(res)
# equality
```

## 3

`One small letter, surrounded by **EXACTLY** three big bodyguards on  each of its sides.` 找左右都是三个大写字母的小写字母，发现找到很多 则有左右边第四个都是小写字母

```python
import requests
import re
res = requests.get('http://www.pythonchallenge.com/pc/def/equality.html')
print("".join(re.findall('[a-z]{1}[A-Z]{3}([a-z]{1})[A-Z]{3}[a-z]{1}', res.text)))
# linkedlist
```

```
http://www.pythonchallenge.com/pc/def/linkedlist.php
```

## 4

查看源码发现`http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=12345`进入则有`and the next nothing is 44827`尝试几个后写脚本继续

```
import requests
url="http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing="
res = requests.get('http://www.pythonchallenge.com/pc/def/linkedlist.php?nothing=12345')
time=0
while(True):
    time+=1
    nothing=res.text.split(" ")[-1]
    print(nothing)
    res=requests.get(url+nothing)
print(time)
print(res)
```

在输出的nothing中间找到一个`peak.html`

```
http://www.pythonchallenge.com/pc/def/peak.html
```

## 5

查看源代码存在`banner.p`对其做反序列化

```python
import requests
import pickle
import os
res=requests.get("http://www.pythonchallenge.com/pc/def/banner.p")
f = open("1.txt", 'wb')
f.write(res.content)
f.close()

with open("1.txt", 'rb') as f:
    data=pickle.load(f)
    print(data)
    
os.remove("1.txt")
```

得到list，list元素总和为95长度为23且只有几个元素，画出矩阵

```python
for col in data:
    for i in col:
        for j in range(i[1]):
            print(i[0],end="")
    print('\n')
```

近似`channel`

```
http://www.pythonchallenge.com/pc/def/channel.html
```

## 6

查看源码提示`<html> <!-- <-- zip -->`改`zip`得到压缩包，解压得到一堆`txt`文件查看`readme`，先找到最后一个文件

```python
data="90052"
while True:
    f=open(data+".txt")
    t=f.read()
    print(t)
    data=t.split(" ")[-1]
# Collect the comments.
```

结合提示2`answer is inside the zip`，得知zipfile存在comment

```python
import zipfile
 
file = zipfile.ZipFile('channel.zip')
data="90052"
res=""
while True:
    f=open(data+".txt")
    res+=str(file.getinfo(data+".txt").comment,encoding='utf-8')
    t=f.read()
    #print(t)
    print(res)
    data=t.split(" ")[-1]
```

得到`HOCKEY`进入`hockey.html`得到提示`it's in the air. look at the letters. `发现`HOCKEY`由小写字母组成`OXYGEN`

```
http://www.pythonchallenge.com/pc/def/oxygen.html
```

## 7

查看源码，信息只有一张img，该img存在灰度区，计算得到43开始后为灰色，提取rgb值，7个一组重复，转asc

```python
import cv2
img=cv2.imread("index.png")
#print(img.shape)
#for i in range(img.shape[0]):
#    print(img[i][0])
res=chr(115)
index=0
for j in range(5,img.shape[1]):
    if(img[43][j][0]==img[43][j][1] and img[43][j][1]==img[43][j][2]):
        print(img[43][j])
        index+=1
        if(index==7):
            index=0
            res+=chr(img[43][j][0])       
print(res)
# smart guy, you made it. the next level is [105, 110, 116, 101, 103, 114, 105, 116, 121]
print("".join(chr(s) for s in [105, 110, 116, 101, 103, 114, 105, 116, 121]))
```

```
http://www.pythonchallenge.com/pc/def/integrity.html
```

## 8

查看源码存在登录窗口，存在提示

```
<!--
un: 'BZh91AY&SYA\xaf\x82\r\x00\x00\x01\x01\x80\x02\xc0\x02\x00 \x00!\x9ah3M\x07<]\xc9\x14\xe1BA\x06\xbe\x084'
pw: 'BZh91AY&SY\x94$|\x0e\x00\x00\x00\x81\x00\x03$ \x00!\x9ah3M\x13<]\xc9\x14\xe1BBP\x91\xf08'
-->

```

查阅资料可知`BZh91AY&SY`为`bz2`加密头，进行解密

```python
import bz2
un = b'BZh91AY&SYA\xaf\x82\r\x00\x00\x01\x01\x80\x02\xc0\x02\x00 \x00!\x9ah3M\x07<]\xc9\x14\xe1BA\x06\xbe\x084'
pw = b'BZh91AY&SY\x94$|\x0e\x00\x00\x00\x81\x00\x03$ \x00!\x9ah3M\x13<]\xc9\x14\xe1BBP\x91\xf08'
print(bz2.decompress(un),bz2.decompress(pw))
# b'huge' b'file'
```

成功登录

```
http://www.pythonchallenge.com/pc/return/good.html
```

## 9

查看图片存在黑点，查看源码存在提示`first+second=?`，`first`、`second`长度不等不为倍数无法相加，猜测`fIrst`与`second`为点，画点

```python
import cv2
import matplotlib.pyplot as plt
img=cv2.imread("good.jpg")
first="temp,146,399,163,403,170,393,169,391,166,386,170,381,170,371,170,355,169,346,167,335,170,329,170,320,170,310,171,301,173,290,178,289,182,287,188,286,190,286,192,291,194,296,195,305,194,307,191,312,190,316,190,321,192,331,193,338,196,341,197,346,199,352,198,360,197,366,197,373,196,380,197,383,196,387,192,389,191,392,190,396,189,400,194,401,201,402,208,403,213,402,216,401,219,397,219,393,216,390,215,385,215,379,213,373,213,365,212,360,210,353,210,347,212,338,213,329,214,319,215,311,215,306,216,296,218,290,221,283,225,282,233,284,238,287,243,290,250,291,255,294,261,293,265,291,271,291,273,289,278,287,279,285,281,280,284,278,284,276,287,277,289,283,291,286,294,291,296,295,299,300,301,304,304,320,305,327,306,332,307,341,306,349,303,354,301,364,301,371,297,375,292,384,291,386,302,393,324,391,333,387,328,375,329,367,329,353,330,341,331,328,336,319,338,310,341,304,341,285,341,278,343,269,344,262,346,259,346,251,349,259,349,264,349,273,349,280,349,288,349,295,349,298,354,293,356,286,354,279,352,268,352,257,351,249,350,234,351,211,352,197,354,185,353,171,351,154,348,147,342,137,339,132,330,122,327,120,314,116,304,117,293,118,284,118,281,122,275,128,265,129,257,131,244,133,239,134,228,136,221,137,214,138,209,135,201,132,192,130,184,131,175,129,170,131,159,134,157,134,160,130,170,125,176,114,176,102,173,103,172,108,171,111,163,115,156,116,149,117,142,116,136,115,129,115,124,115,120,115,115,117,113,120,109,122,102,122,100,121,95,121,89,115,87,110,82,109,84,118,89,123,93,129,100,130,108,132,110,133,110,136,107,138,105,140,95,138,86,141,79,149,77,155,81,162,90,165,97,167,99,171,109,171,107,161,111,156,113,170,115,185,118,208,117,223,121,239,128,251,133,259,136,266,139,276,143,290,148,310,151,332,155,348,156,353,153,366,149,379,147,394,146,399"
#print(len(first.split(',')))
t=first.split(',')
#print(t)
index=0
for point in t:
    #print(point)
    index+=1
    if point=="temp":continue
    if(index%2==0):
        #print(t[index-1],t[index])
        cv2.circle(img,(int(t[index-1]),int(t[index])),3,(0,0,0))
second="temp,156,141,165,135,169,131,176,130,187,134,191,140,191,146,186,150,179,155,175,157,168,157,163,157,159,157,158,164,159,175,159,181,157,191,154,197,153,205,153,210,152,212,147,215,146,218,143,220,132,220,125,217,119,209,116,196,115,185,114,172,114,167,112,161,109,165,107,170,99,171,97,167,89,164,81,162,77,155,81,148,87,140,96,138,105,141,110,136,111,126,113,129,118,117,128,114,137,115,146,114,155,115,158,121,157,128,156,134,157,136,156,136"
t=second.split(',')
index=0
for point in t:
    #print(point)
    index+=1
    if point=="temp":continue
    if(index%2==0):
        #print(t[index-1],t[index])
        cv2.circle(img,(int(t[index-1]),int(t[index])),3,(0,0,0))
plt.imshow(img)
```

得到一头貌似牛的图像`cow.html`得到`hmm. it's a male.`

```
http://www.pythonchallenge.com/pc/return/bull.html
```

## 10

查看源码发现存在`sequence.txt` 内容为`a = [1, 11, 21, 1211, 111221, `问题为`len(a[30]) = ?`，需要找规律`a`序列后面的长度，5个元素比较困难，首先猜测斐波那契因为后几个元素长度为`2,2,4,6`，果然错了。找不到规律，猜测答案为整数，则开始爆破

```python
import requests
s = requests.Session()
def geturl(number):
    return "http://www.pythonchallenge.com/pc/return/"+str(number)+".html"

header={
  "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:94.0) Gecko/20100101 Firefox/94.0",
  "Cookie":"_ga=GA1.2.2060571321.1636538336; info=you%20should%20have%20followed%20busynothing...",
  "Authorization":"Basic aHVnZTpmaWxl",
}
for i in range(100000):
    if(i%500==0):
        print("已遍历",i)
    res=s.get(geturl(i),headers=header)
    
    if "not exist" not in res.text:
        print("the answer is",i)
        break
# the answer is 5808
```

答案为5808

```
http://www.pythonchallenge.com/pc/return/5808.html
```

查看教程发现规律，下一个数为上一个数的总结，11表示1个1即上一个数为1,1211表示1个2，1个1，即上一个数为21

## 11

查看源码未看到有效信息，只有一张图片，而且图片中有异常像素点。图片`shape`为`(480, 640, 3)`，接下来需要分离有效像素点。`cave`是当心，网页`title`为`odd even`表示奇偶。选择按奇偶分离像素点，尝试横向分隔与纵向分隔失败，最后横向纵向同时分隔成功。

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
img=cv2.imread("cave.jpg")
#print(img.shape)
'''
new_img=np.empty((int(img.shape[0]),int(img.shape[1]/2),3))
for i in range(480):
    for j in range(320):
        for k in range(3):
            new_img[i][j][k]=img[i][j*2][k]
'''
new_img=np.empty((int(img.shape[0]/2),int(img.shape[1]/2),3))
for i in range(240):
    for j in range(320):
        for k in range(3):
            new_img[i][j][k]=img[i*2][j*2][k]
#new_img.shape
cv2.imwrite("new_img.png",new_img)
```

在得到的`img`中发现`evil`字样

```
http://www.pythonchallenge.com/pc/return/evil.html
```

## 12

查看源码，也只有`img`这一信息，网页`title`无法提供有效信息。查看`img`的`link`发现其为`evil1.jpg`，尝试`evil2.jpg,evil3.jpg......`发现存在2,3,4三张图，`evil4`提示因错误而无法显示。`2`图中字样`not jpg,gfx`,`3`中`mo more evils`。尝试改后缀`jpg`为`gfx`，访问`evil2.gfx`下载`gfx文件`。由于`evil4`中内容无法显示，则再次尝试

```python
import requests
s = requests.Session()
url="http://www.pythonchallenge.com/pc/return/evil4.jpg"

header={
  "User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64; rv:94.0) Gecko/20100101 Firefox/94.0",
  "Cookie":"_ga=GA1.2.2060571321.1636538336; info=you%20should%20have%20followed%20busynothing...",
  "Authorization":"Basic aHVnZTpmaWxl",
}
res=s.get(url,headers=header)
print(res.text)
# 'Bert is evil! go back!\n'
```

为无效信息，则当前可用的为`	gfx`文件。`010`打开，也不存在有效文件头。查看网上WP，图片中的分牌对应将数据分为5份，包含5张`img`，写脚本实现。

```python
import os
import cv2
import matplotlib.pyplot as plt

with open ("evil2.gfx","rb") as f:
    data=f.read()
    
for i in range(5):
    img_data=data[i::5]
    #img=cv2.imdecode(np.array(bytearray(img_data), dtype='uint8'), cv2.IMREAD_UNCHANGED) # bytes2img
    #plt.imshow(img)
    with open("%d.jpg" % (i),"wb") as f:
        f.write(img_data)
```

`4.jpg`中内容被划掉，拼接`0-3`中内容得到`disproportional`

```
http://www.pythonchallenge.com/pc/return/disproportional.html
```

## 13

有个`phonebook.php`内容有`<string>XML error 5: empty document</string>`毫无思路，直接看WP。

`XML-RPC`是工作在`Internet`上的远程过程调用协议。一个`XML-RPC`消息就是一个请求体为`xml`的`http-post`请求，被调用的方法在服务器端执行并将执行结果以`xml`格式编码后返回。存在`python `的 `xmlrpc `库，并有`phone`方法。

```python
import xmlrpc.client

p= xmlrpc.client.ServerProxy('http://www.pythonchallenge.com/pc/phonebook.php')

#print(p.system.listMethods()) # ['phone', 'system.listMethods', 'system.methodHelp','system.methodSignature', 'system.multicall', 'system.getCapabilities']
#print(p.system.methodHelp('phone')) # Returns the phone of a person
#print(p.system.methodSignature('phone'))# [['string', 'string']]
print(p.phone('evil')) # He is not the evil
print(p.phone('Bert')) # 555-ITALY
```

`phone(evil)`但是提示`He is not the evil`。那么谁是`evil`，在访问12关的`evil4.jpg`中说`'Bert is evil! go back!\n'`，则`phone(Bert)`

```
http://www.pythonchallenge.com/pc/return/italy.html
```

## 14

查看源码，存在提示`<!-- remember: 100*100 = (100+99+99+98) + (...  -->`以及一张`wire.png`，查看图像维度发现其为`10000*1`刚好是`100*100`，尝试将其转为`100*100`

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
img=cv2.imread("index.png")
#print(img.shape) #(1, 10000, 3)
img_res=np.zeros([100,100,3],np.uint8)
for i in range(100):
    for j in range(100):
        for k in range(3):
            img_res[i][j][k]=img[0][i*100+j][k]
plt.imshow(img_res)
```

得到一张图片，上面有`bit`字样，尝试`bit.html`返回`you took the wrong curve.`也就是说不能一行一行，这样的顺序有错。结合主页中给的面包圈图，猜测也是一个环形的

```python
import cv2
import numpy as np
import matplotlib.pyplot as plt
img=cv2.imread("index.png")
#print(img.shape) #(1, 10000, 3)
img_res=np.zeros([100,100,3],np.uint8)
p=0
n=100
for i in range(int(n/2+1)):
    for j in range(i,n-i):#从行遍历
        for k in range(3):
            img_res[i][j][k]=img[0][p][k]
        p+=1
    for j in range(i+1,n-i):#遍历一竖
        for k in range(3):
            img_res[j][n-i-1][k]=img[0][p][k]
        p+=1
    for j in range(n-i-2,i-1,-1):#遍历底层
        for k in range(3):
            img_res[n-i-1][j][k]=img[0][p][k]
        p+=1
    for j in range(n-i-2,i,-1):
        for k in range(3):
            img_res[j][i][k]=img[0][p][k]
        p+=1
plt.imshow(img_res)
```

代码实现，得到一张猫的图片，进入`cat.html`提示`and its name is **uzi**. you'll hear from him later.`则换成`uzi`

```
http://www.pythonchallenge.com/pc/return/uzi.html
```

## 15

查看源码发现提示`<!-- he ain't the youngest, he is the second -->`以及`<!-- todo: buy flowers for tomorrow -->`结合网页`title`为`whom`猜测为找一个人。`buy flowers for tomorrow`表示他明天生日。`tomorrow`的日期为`1月27日`。图片有效信息，2月有29天且1月27号为周二，且年份的中间两位被遮挡，第一位为1，最后一位为6

```python
import calendar
for i in range(1000,2000):
    if calendar.weekday(i,1,27)==1 and calendar.isleap(i) and i%10==6:#weekday函数星期二为1,星期一为0
        print(i)
'''
1176
1356
1576
1756
1976
'''
```

结合提示`he ain't the youngest, he is the second`即推断得到他的生日为1756年1月27号，发现为莫扎特的生日。

```
http://www.pythonchallenge.com/pc/return/mozart.html
```

## 16

打开网页，查看源码有效信息只有一张`img`，用`cv2`读一直报错，猜测是编码问题，转而采用`plt`读取，发现图像存在4个维度，无法观察到有效信息，题目`title`为`let me get this straight`，尝试一段时间放弃，查看题解图中每行都有红线区域，需要将该区域对齐，即`get straight`

```python
import matplotlib.pyplot as plt
import numpy as np
def cmplist(a,b):
    return a[0]==b[0] and a[1]==b[1] and a[2]==b[2]
def isred(a):
    return cmplist(a,[255,0,255])
img = plt.imread('index.gif')


'''
确定红色的值 为[255 0 255 255]
for p in range(len(img[0])):
    if(cmplist(img[0][p],img[0][p+1]) and cmplist(img[0][p],img[0][p+2])):
        print(img[0][p])
        print(p)
'''
img_new=np.zeros((480,640,4),np.uint8)
#img.shape #(480, 640, 4)
for i in range(img.shape[0]):
    for j in range(img.shape[1]):
        if isred(img[i][j]):
            #print(j)
            img_new[i][0:img.shape[1]-j-1]=img[i][j:-1]
            img_new[i][img.shape[1]-j:-1]=img[i][0:j-1]
            break
plt.imshow(img_new)
```

最后得到的图片中包含`romance`

```
http://www.pythonchallenge.com/pc/return/romance.html
```

## 17

查看源码只有一张图片，图名为`cookies.jpg`，查看网页`cookies`,发现`info=you%20should%20have%20followed%20busynothing...`，图中还有第四关的图，也查看第四关的`cookies`发现一样，即思路与第四关相似，为`busynothing`赋值。尝试改17关`.html`为`.php`，并赋值`busynothing`，但无效，发现需要在第四关上构造。`http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing=12345`。运行以下脚本。

```python
import requests
url="http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing="
res = requests.get('http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing=12345')
time=0
while(True):
    time+=1
    nothing=res.text.split(" ")[-1]
    print(nothing)
    res=requests.get(url+nothing)
print(time)
print(res)
```

在中间找到一个`it.`,即`http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing=83051`内容为`that's it.`结合`cookies`，尝试打印网页的`cookies`，发现该网页`cookie`存在`value`信息，而其后的网页都不存在`cookies`，尝试拼接之前的`cookies`。

```python
import requests
url="http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing="
res = requests.get('http://www.pythonchallenge.com/pc/def/linkedlist.php?busynothing=12345')
time=0
mes=""
while(True):
    time+=1
    nothing=res.text.split(" ")[-1]
    print(nothing)
    if(nothing=='it.'):
        break
    res=requests.get(url+nothing)
    cookies=requests.utils.dict_from_cookiejar(res.cookies)
    mes=mes+res.cookies["info"]

print(mes)
#BZh91AY%26SY%94%3A%E2I%00%00%21%19%80P%81%11%00%AFg%9E%A0%20%00hE%3DM%B5%23%D0%D4%D1%E2%8D%06%A9%FA%26S%D4%D3%21%A1%EAi7h%9B%9A%2B%BF%60%22%C5WX%E1%ADL%80%E8V%3C%C6%A8%DBH%2632%18%A8x%01%08%21%8DS%0B%C8%AF%96KO%CA2%B0%F1%BD%1Du%A0%86%05%92s%B0%92%C4Bc%F1w%24S%85%09%09C%AE%24%90
print(time)
print(res)
```

发现为`bz2`加密头，采用第8关用到的脚本，出现编码错误，需要将`url`编码转为`byte`，查阅发现`urllib.parse`中的`unquote_to_bytes`函数可以实现。

```python
import bz2
import urllib.parse as prs
str=b"BZh91AY%26SY%94%3A%E2I%00%00%21%19%80P%81%11%00%AFg%9E%A0%20%00hE%3DM%B5%23%D0%D4%D1%E2%8D%06%A9%FA%26S%D4%D3%21%A1%EAi7h%9B%9A%2B%BF%60%22%C5WX%E1%ADL%80%E8V%3C%C6%A8%DBH%2632%18%A8x%01%08%21%8DS%0B%C8%AF%96KO%CA2%B0%F1%BD%1Du%A0%86%05%92s%B0%92%C4Bc%F1w%24S%85%09%09C%AE%24%90"
str= prs.unquote_to_bytes(str)
print(bz2.decompress(str))
# b'is it the 26th already? call his father and inform him that "the flowers are on their way". he\'ll understand.'
```

开始看不懂，后来发现这题一直在用前面的知识点，即结合13题的`phone`，`his father`应该是莫扎特的`father`，为`Leopold Mozart`

```python
import xmlrpc.client
xmlrpc = xmlrpc.client.ServerProxy('http://www.pythonchallenge.com/pc/phonebook.php')
print(xmlrpc.phone('Leopold'))
#555-VIOLIN
```

本来还想如何传递信息`the flowers are on their way`，好像没必要了，得到答案。

进入`http://www.pythonchallenge.com/pc/return/violin.html`，不是最终结果，提示`no! i mean yes! but ../stuff/violin.php.`改网页为`http://www.pythonchallenge.com/pc/stuff/violin.php`，有一张`leopold.jpg`，还是需要传话给他，如果是`post`请求也不知道`post`什么，还是回到`cookies`

```python
import requests
url="http://www.pythonchallenge.com/pc/stuff/violin.php"
res=requests.get(url,headers= {'cookie':'info=the flowers are on their way'})
res.text
```

得到`oh well, don\'t you dare to forget the balloons.`，猜测最终结果

```
http://www.pythonchallenge.com/pc/return/balloons.html
```

## 18

直接查看源码信息只有一张`img`，`title:can you tell the difference`，提示：`<!-- it is more obvious that what you might think -->`，两张图片的唯一不同就是亮度。唯一的信息传入点就是`url`，测试几个单词，发现`brightness.html`会返回图片，查看源码`<!-- maybe consider deltas.gz -->`，于是访问下载`deltas.gz`。解压出来是个2000多行的txt，里面应该含有一张图片，`89 50 4E 47`Png文件头。中间是一堆`11`，回来看这里好像有两张图片，每行中间都有一个空格，图片一左一右，右边图片好像信息多一点。思路一：打算先将两张图片都保存下来看看，然后再根据题意找不同。思路二：提取找两张图片十六进制串的不同信息。尝试输出img1，混乱，没什么信息。于是，需要找到两张图片的不同点，尝试自己直接找失败，输出第一个不同点诗歌`89 50`，即也存在`img`。自己找算法太麻烦，寻求库的帮助，在WP下发现存在`difflib`库中可以对比两个序列的不同，采用此方法进行复现。

```python
import fileinput
import binascii
import difflib
img1=""
img2=""
img3=""
d1=[]
d2=[]
finput=fileinput.input("delta.txt")
for line in finput:
    d1.append(line[:53]+"\n")
    d2.append(line[56:])
finput.close() 

compare = difflib.Differ().compare(d1,d2) 

for line in compare:
    data=line[2:].replace(' ','').replace('\n','').replace('+','').replace('-','')
    if line[0] == '+':
        img1+=data
    elif line[0] == '-':
        img2+=data
    else:
        img3+=data
        
f=open('test1.png',"ab")
pic=binascii.a2b_hex(img1.encode())
f.write(pic)
f.close()
f=open('test2.png',"ab")
pic=binascii.a2b_hex(img2.encode())
f.write(pic)
f.close()
f=open('test3.png',"ab")
pic=binascii.a2b_hex(img3.encode())
f.write(pic)
f.close()
```

采用`binascii`库实现16进制串转图片。

得到3张图片显示内容分别为`buffer`，`fly`,`../hex/bin.html`

访问`www.pythonchallenge.com/pc/hex/bin.html`，账号密码分别为`buffer`，`fly`成功进入第19关

```
http://www.pythonchallenge.com/pc/hex/bin.html
```

## 19

进入网页是一张印度地图，查看源码有段音频的base64,直接base64转wav

```python
import base64

with open("data.txt") as f:
    data=f.read()
data=data.replace('\n','')

encode_string = data
wav_file = open("temp.wav", "wb")
decode_string = base64.b64decode(encode_string)
wav_file.write(decode_string)
```

得到的音频文件有说sorry，尝试但发现sorry不是答案，回显`- "what are you apologizing for?"`，然后继续找信息也没找到什么。查看网上WP,发现根据图中海水和陆地这一提示将图片倒置

音频输出`you’re an idiot!`，得到结果，进入`http://www.pythonchallenge.com/pc/hex/idiot.html`得到下一个的入口。

```
http://www.pythonchallenge.com/pc/hex/idiot2.html
```

## 20

进入网站，查看源码没什么信息，就一张图片，上面写这PRIVATE PROPERTY BEYOND THIS FENCE，又有一句提示but inspecting it carefully is allowed.这道题分析了图片半天也看不出什么，最后还是参考了网上的解法，自己复现。

有个Content-Range参数，Content-Range=bytes 0-30202/2123456789。按照惯例，这么奇怪的参数应该就是突破口了，先尝试修改range为30203发现有提示`Why don't you respect my privacy?\n`，于是一直遍历

```python
import urllib.request
url="http://www.pythonchallenge.com/pc/hex/unreal.jpg"
request = urllib.request.Request(url)
request.add_header('Authorization', 'Basic YnV0dGVyOmZseQ==')
start=30202
while True:
    try:
        trange="bytes="+str(start)+"-"
        start+=1
        request.headers['Range'] = trange
        response = urllib.request.urlopen(request)
        print(response.read())
    except:
        pass
```

得到keywords  invader ，尝试http://www.pythonchallenge.com/pc/hex/invader.html，发现需要将range倒过来

```python
import urllib.request
url="http://www.pythonchallenge.com/pc/hex/unreal.jpg"
request = urllib.request.Request(url)
request.add_header('Authorization', 'Basic YnV0dGVyOmZseQ==')
start=2123456789
while True:
    try:
        trange="bytes="+str(start)+"-"
        start-=1
        request.headers['Range'] = trange
        response = urllib.request.urlopen(request)
        print(response.read())
    except:
        pass
```

得到两条message 分别为 

```
b'esrever ni emankcin wen ruoy si drowssap eht\n'
b'and it is hiding at 1152983631.\n
```

第一条消息转置后为

`*the password is your new nickname in reverse`，第二条消息有数字`1152983631`

```
import urllib.request
url="http://www.pythonchallenge.com/pc/hex/unreal.jpg"
request = urllib.request.Request(url)
request.add_header('Authorization', 'Basic YnV0dGVyOmZseQ==')
start=1152983631

trange="bytes="+str(start)+"-"

request.headers['Range'] = trange
response = urllib.request.urlopen(request)
print(response.read())

```

得到`PK头`的字符串，写入到文件`data.zip`，解压密码为invalid倒置，为redavni

得到readme.txt和package.pack,查看readme.txt发现已经进入到第21关

## 21

上网查阅一下pack文件，其实里面就是隐藏着压缩包。发现存在两种格式分别为bz2和zlib，采用python对于模块进行解压缩，并通过文件头来判断是哪种格式。注意还存在导致的zlib压缩格式，需要将data转置再解压缩。

```python
import zlib,bz2
file = open("package.pack",'rb').read()

def process(data):
    result = ""
    while True:
        if data.startswith(b'x\x9c'):
            data = zlib.decompress(data)
            result += ' '
        elif data.startswith(b'BZh'):
            data = bz2.decompress(data)
            result += '1'
        elif data.endswith(b'\x9cx'):
            data = data[::-1]
            result += '\n'
        else:
            print(result)
            return data

process(file)
```

得到answer为copper,即下一关url为

http://www.pythonchallenge.com/pc/hex/copper.html

## 22

进入网站，题目提示emulate表示模仿，查看源码发现存在提示<!-- or maybe white.gif would be more bright-->，那就访问white.gif看看，下载white的gif看看它是不是真的全黑。

直接用cv2去读发现读不出东西，那就说明这真的是一张gif还是得用pillow，

读取每一帧并且存下来，发现有133帧

```python
from PIL import Image
from PIL import ImageSequence
img = Image.open("white.gif")
i = 0
for frame in ImageSequence.Iterator(img):
    frame.save("white/frame%d.png" % i)
    i += 1
print(i)
```

保存每一帧并读取，发现并非全部像素都是黑色，每张图都有一个像素是【8,8,8】,且这个像素的x，y坐标都在100附近，猜测是通过位移来得到一个字母

```python
import cv2
import numpy as np

image = np.zeros([200,200,3],np.uint8)
cx, cy = 0, 100
for i in range(133):
    img=cv2.imread('white/frame{}.png'.format(i+1))
    for i in range(200):
        for j in range(200):
            for k in range(3):
                if(img[i][j][k]!=0):
                    upper,left=i,j
                    print(left,upper)
                    break
    dx = (left - 100)//2
    dy = (upper - 100)//2
    if cx:
        image[cx][cy]=[255,255,255]
    cx += dx
    cy += dy
    if dx == dy == 0:
        cx += 25
        cy = 100
plt.imshow(image)
```

采用代码来实现，虽然好像反了，但问题不大，发现有bonus字样，得到第23关url为http://www.pythonchallenge.com/pc/hex/bonus.html

## 23

进入网站，网页title为what is this module。应该是要用python的一个模块，查看源码有个TODO： do you owe someone an apology? now it is a good time to tell him that you are sorry. Please show good manners although it has nothing to do with this level.不是很懂，先放着。还有一句对该模块的提示，it can't find it. this is an undocumented module. 这个模块未被记录。之前有了解过this模块，直接import是一首python小诗。

```python
import this
'''
The Zen of Python, by Tim Peters

Beautiful is better than ugly.
Explicit is better than implicit.
Simple is better than complex.
Complex is better than complicated.
Flat is better than nested.
Sparse is better than dense.
Readability counts.
Special cases aren't special enough to break the rules.
Although practicality beats purity.
Errors should never pass silently.
Unless explicitly silenced.
In the face of ambiguity, refuse the temptation to guess.
There should be one-- and preferably only one --obvious way to do it.
Although that way may not be obvious at first unless you're Dutch.
Now is better than never.
Although never is often better than *right* now.
If the implementation is hard to explain, it's a bad idea.
If the implementation is easy to explain, it may be a good idea.
Namespaces are one honking great idea -- let's do more of those!
'''
```

在源码的最后还有一段小密文va gur snpr bs jung，猜测凯撒，跑一边，

```python
str="va gur snpr bs jung"
for change in range(26):
    res=""
    for s in str:
        if ord(s)+change>122:
            res+=chr(ord(s)-26+change)
        elif  'x'>=s>='a':
            res+=chr(ord(s)+change)
        else:
            res+=s
    print(res)
#in the face of what
```

得到有一个结果为in the face of what，再对照小诗中In the face of ambiguity，得到下一关为

http://www.pythonchallenge.com/pc/hex/ambiguity.html

## 24

进入题目是一张迷宫的图片，title是from top to bottom，查看源码也没看到什么有价值的信息，题目很明确，走迷宫。

先得到出入口的位置

```python
import cv2
import matplotlib.pyplot as plt
img=cv2.imread("maze.png")
print(img.shape)#(641, 641, 3)
plt.imshow(imag)

for i in range(641):
    if(img[0][i][0]==0):
        print("top:0 ",i)
    if(img[640][i][0]==0):
        print("bottom:640 ",i)
'''
bottom:640  1
top:0  639
'''
```

然后计算迷宫路径，开始通过CV计算，但是速度很慢，最后还算错了，最后参考教程https://www.cnblogs.com/nicole-zhang/p/15563941.html才有PIL来做

```python
from PIL import Image, ImageDraw

img = Image.open('maze.png').getdata()
width,heigth = img.size # 641 641

def RBG_notWhite(img):
    nw = set()
    width, height = img.size
    for x in range(width):
        for y in range(height):
            if img.getpixel((x,y)) != (255,255,255,255):
                nw.add((x,y))
    return nw

nw = RBG_notWhite(img) # 不是白色的点即 可以走的路径
start = (639,0)
end = (1,640)
# 有四个方向
direction = [(1, 0), (0, 1), (-1, 0), (0, -1)]
queue = [end]
nextPosList = {}

while True:
    pos = queue.pop()
    if pos == start:
        break
    for d in direction:
        nextPos = (pos[0]+d[0], pos[1]+d[1])
        if nextPos in nw and nextPos not in nextPosList:
            nextPosList[nextPos] = pos
            queue.append(nextPos)

newImg = Image.new(img.mode,img.size,"white")

color = []
while pos != end:
    p = img.getpixel(pos)
    color.append(p[0])
    newImg.putpixel(pos,p)
    pos = nextPosList[pos]
newImg.save("mazePath.png")


```

成功得到迷宫路径的图片

查看文件头，其实就是rar，于是写入

```python
r_list = color[1::2]
r_bytes = bytes(r_list)
with open("24.rar", "wb") as file:
    file.write(r_bytes)
```

得到压缩包，解压得到maze.jpg和mybroken.zip

得到下一关为http://www.pythonchallenge.com/pc/hex/lake.html

