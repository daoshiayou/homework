;去除字符串中的某个字符
;输入任意字符串string（字符个数至少15个），Enter 结束输入；提示输入字符
;输入任意字符ch，Enter结束输入，将字符串中ch去除
;输出变化后的字符串String2，按Enter程序退出
DATAS SEGMENT
    inputMsg DB 'Please enter a string of a length greater than 14:$'
    chMsg DB 'Please enter the character to delete$'
    outputMsg DB 'The deleted string is:$'
    rMsg DB 'Press Enter to exit$'
    DCH db ?
    BUF DB 50H
    	DB ? 
    	DB 50H DUP(0)
    
DATAS ENDS

STACKS SEGMENT
    DW 20H DUP(0);此处输入堆栈段代码
STACKS ENDS

CODES SEGMENT
    ASSUME CS:CODES,DS:DATAS,SS:STACKS
START:
    MOV AX,DATAS
    MOV DS,AX
    ;输出输入字符串
ERROR:
    LEA DX,inputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
	;接收输入的字符串
	LEA DX,BUF
	MOV AH,0AH
	INT 21H
	;输出回车
	CALL NEWLINE
	;检测字符串长度
	MOV AL,[BUF+1]
	CMP AL,0FH
	JB ERROR
	;输出提示输入字符
    LEA DX,chMsg
    MOV AH,09H
    INT 21H
    ;输出回车
	CALL NEWLINE
	;调用输入字符并处理Enter继续	DO
	MOV AH,01H
INPUT:
	INT 21H
	CMP AL,0DH
	JE CONT
	MOV [DCH],AL
	JMP INPUT
CONT:
	;输出输出提示信息
	LEA DX,outputMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
    ;调用子程序删除字符串	DO
    CALL DELETECH
    ;调用子程序调整字符串	DO
    CALL ADJUST
    ;输出处理后字符串
    LEA DX,BUF+2
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
    ;输出返回提示信息
    LEA DX,rMsg
    MOV AH,09H
    INT 21H
    ;输出回车
    CALL NEWLINE
	;处理Enter继续	DO
	MOV AH,01H
QUIT:
	INT 21H
	CMP AL,0DH
	JNE QUIT
    MOV AH,4CH
    INT 21H    
    
DELETECH PROC
	MOV AL,[BUF+1]
	CBW
	MOV SI,AX
	MOV BX,AX	;BX储存原字符串长度
	MOV BUF+2[SI],'$'
	MOV CX,AX
	XOR SI,SI
	MOV AH,AL
	MOV AL,[DCH]
LOP1:
	CMP AL,BUF+2[SI]
	JNE CONT1
	DEC AH
	MOV BUF+2[SI],0FFH
CONT1:
	ADD SI,TYPE BUF
	LOOP LOP1
	MOV [BUF+1],AH
	RET
DELETECH ENDP

ADJUST PROC
	MOV CX,BX
	XOR SI,SI
LOP2:
	CMP BUF+2[SI],0FFH
	JNE CONT2
	;后面元素全部前移
	PUSH CX
	PUSH SI
	PUSH BX
	MOV CX,BX
	SUB CX,SI
	MOV BX,SI
	ADD BX,TYPE BUF
LOP3:
	MOV AL,BUF+2[BX]
	MOV BUF+2[SI],AL
	ADD SI,TYPE BUF
	ADD BX,TYPE BUF
	LOOP LOP3
	POP BX
	POP SI
	POP CX
	SUB SI,TYPE BUF
CONT2:
	ADD SI,TYPE BUF
	LOOP LOP2
	RET
ADJUST ENDP

NEWLINE PROC
	MOV DL,0DH
	MOV AH,02H
	INT 21H
	MOV DL,0AH
	INT 21H
	RET
NEWLINE ENDP

CODES ENDS
    END START




