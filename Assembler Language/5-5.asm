START:
Input:
MOV AH,1 ;输入字符
INT 21H
CMP AL,'0'
JLE Input
CMP AL,'9'
JG Input
SUB AL,'0'
CBW ;扩展AL为AX
MOV CX,AX ;CX为响铃次数
Bell:
MOV DL,07H
MOV AH,2
INT 21H
LOOP Bell ;LOOP CX-- >=0     

END START