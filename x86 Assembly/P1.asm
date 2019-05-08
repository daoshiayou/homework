;提示输入数字；输入任意数字int1（1000以内），点击Enter结束输入；
;如果int1 是质数，则输出“int1 is a prime number”；
;如果int1 不是质数，则输出“int1 is not a prime number”； 
;点击Enter 程序退出。
DATAS SEGMENT
    inputMsg DB 'Please enter a integer under1000:$'
    pMsg DB 'int1 is a prime number$'
    nPMsg DB 'int1 is not a prime number$'
    rMsg DB 'Press Enter to quit$'
DATAS ENDS

STACKS SEGMENT
    DW   20H   DUP(0);此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;此处输入代码段代码
ERROR:
	XOR BX,BX
	LEA DX,inputMsg
	MOV AH,09H
	INT 21H
INPUT:
   	MOV AH,01H		;调用dos输入
    INT 21H
    CMP AL,0DH		;判断是否是换行
    JE JUDGE
    SUB AL,30H		;减30H后刚好是数字
    JL ERROR		;判断输入的是否是数字
    CMP AL,9
    JG START
    CBW				;字节转字
    XCHG AX,BX		;之前的数值和AX转换
    MOV CX,10		;之前的数值乘10
    MUL CX
    XCHG AX,BX		;乘10后存到BX
    ADD BX,AX		;加上之前输入的数字
    JMP INPUT
JUDGE:
	CMP BX,1000
	JAE ERROR
	CMP BX,3H
	JB SUCCESS
	MOV CX,BX
	AND CX,1H
	JCXZ FAIL		;除2		
	MOV AX,BX
	MOV CX,6
	MUL CX
	MOV CX,AX
	SHR CX,1H
	AND CX,1H
	JCXZ FAIL		;除3
	MOV CX,BX
	SHR CX,1H
	SUB CX,1H
	PUSH BX
	MOV BX,3H
JUD:
	POP DX
	MOV AX,DX
	PUSH DX
	XOR DX,DX
	INC BX
	DIV BX
	CMP DX,0
	JE FAIL
	LOOP JUD
	JMP SUCCESS
SUCCESS:
	LEA DX,pMsg
	MOV AH,09H
	INT 21H
	JMP RETURN
FAIL:
    LEA DX,nPMsg
	MOV AH,09H
	INT 21H
RETURN:
	MOV DL,0DH
	MOV AH,02H
	INT 21H
	MOV DL,0AH
	INT 21H 
	LEA DX,rMsg
	MOV AH,09H
	INT 21H
	MOV AH,01H		;调用dos输入
    INT 21H
    CMP AL,0DH		;判断是否是换行
    JNE ERROR
	MOV AH,4CH
    INT 21H
CODES ENDS
    END START







